
/*
Em geral, toda linguagem de programação possui um tipo de dados inteiro (int), 
que suporta operações básicas como: adição, subtração, multiplicação e divisão. 
Em grande parte dos computadores atuais, no entanto, essas operações são definidas
somente para valores inteiros menores ou iguais a 2.147.483.647 (INT_MAX). Deste modo, 
para aplicações específicas, em que valores maiores que INT_MAX precisem ser 
manipulados, o tipo int se torna inadequado. 

Uma forma alternativa de se representar inteiros maiores que INT_MAX, seria 
utilizar uma estrutura de dados lista, na qual cada item da lista armazene um 
único dígito (0-9) do inteiro em questão.

Utilize listas duplamente encadeadas para implementar a adição de inteiros grandes positivos!

	Lista* add(Lista* A, Lista* B);

Especificações:

Entrada:
	Considere que os inteiros grandes (positivos) estão incialmente armazenados
	em uma string cada.
	
	Ex.: 
		const char* x ="92233720368547758079223372036854775807"
	     	const char* y ="2147483"

	Essas strings devem ser transformadas em listas por uma função.

	Lista* tolist(char* string);

Objetivo:

	Utilizar listas duplamente encadeadas como estrutura de dados para armazenar, manipular	       inteiros grandes. 


Exemplo: 

	92233720368547758079223372036854775807
	+				     1
		
	92233720368547758079223372036854775808

*/
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>



//typedef struct _Item Item;
//typedef struct _Lista Lista;

typedef struct _item
{
	int valor;
	struct _item* prox;
	struct _item* ant;
} Item;


typedef struct _list
{
	Item* inicio;
	Item* fim;
	int tamanho;
} Lista;



Lista* novaLista()
{
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l->inicio = NULL;
	l->fim    = NULL;
	l->tamanho = 0;
	
	return l;
}

Item* novoItem(int value)
{
	Item *i = (Item*) malloc(sizeof(Item));
	i->valor = value;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}


// =============================================================================

void inserirInicio(Lista* l, Item* novo)
{
	// Se lista vazia
	if (l->inicio == NULL) {
		l->inicio = novo;
		l->fim = l->inicio;
	} else {
		l->inicio->ant = novo;
		novo->prox = l->inicio;
		l->inicio = novo;
	}
	l->tamanho++;
}


void inserirFim(Lista* l, Item* novo)
{
	// Se lista vazia
	if (l->fim == NULL) {
		inserirInicio(l, novo);
	} else {
		l->fim->prox = novo;
		novo->ant = l->fim;
		l->fim = novo;
		l->fim->prox = NULL;
	
		l->tamanho++;
	}
}

Item* removerInicio(Lista* l)
{
	assert(l->tamanho > 0);
	
	Item* removed = NULL;
	
	if (l->tamanho == 1)
	{
		removed = l->inicio;
		l->inicio = NULL;
		l->fim = NULL;
	} else {
		removed = l->inicio;
		l->inicio = removed->prox;
		
		l->inicio->ant = NULL;
	}
	l->tamanho--;
	
	
	return removed;
}

// =============================================================================


void printLista(Lista* l)
{
	if (l->inicio != NULL)
	{
		Item* curr = l->inicio;
		while(curr != l->fim)
		{
			fprintf(stdout, "%d", curr->valor); 
			curr = curr->prox;
		}
		fprintf(stdout, "%d", curr->valor); 
		fprintf(stdout, "\n");
	}
}



// =============================================================================

void freeLista(Lista* l)
{
	while (l->inicio != NULL)
		free(removerInicio(l));
}




Lista* tolist(const char* x)
{
	int xlen = strlen(x);

	Lista* xlista = novaLista();
	for (int i = 0; i < xlen; i++)
	{
		int digito = (int) x[i] - '0';
		inserirFim(xlista, novoItem(digito));
	}
	return xlista;
}

/* Adiciona a + b + carry.
   Inicialmente carry é zero.
   Como a some é de dígitos, somente a parte (x % 10) é retornada.
   A parte que sobra vai como carry para outra iteração.
   Exemplo:
   	a = 9;
	b = 9;
	carry = 0;

	sum   = (9 + 9 + 0) % 10; // sum == (18 % 10); sum == 8;
	carry = (9 + 9 + 0) / 10; // sum == (18 / 10); sum == 1;
*/
int addDigit(int a, int b, int* carry)
{
	int sum = (a + b + (*carry)) % 10;
	*carry  = (a + b + (*carry)) / 10;

	return sum;
}

/*

Condições:
	A lista A pode ser maior que a lista B, ou vice-versa;
Funcionamento:
	soma-se o item atual de A, o item atual de B e o carry, enquanto houver elementos em ambas.
Exceção:
	1. Se A > B, os elementos que restarem de A serão somados apenas com o carry.
	2. Se ao fim de A, o carry ainda for > 0, ele é inserido na lista resultante.
*/
Lista* add(Lista* A, Lista* B)
{
	// Para identificar a maior lista.
	Lista* maior = (A->tamanho >= B->tamanho ? A : B);
	Lista* menor = (A->tamanho < B->tamanho ? A : B);

	Lista* result = novaLista();

	int carry = 0;

	Item* acurr = maior->fim;
	Item* bcurr = menor->fim;

	int avalue = 0;
	int bvalue = 0;
	while (acurr != NULL)
	{	
		avalue = acurr->valor;
		bvalue = (bcurr != NULL) ? bcurr->valor : 0;
		
		int sum = addDigit(avalue, bvalue, &carry);
		inserirInicio(result, novoItem(sum));
		
		acurr = acurr->ant;
		bcurr = (bcurr != NULL) ? bcurr->ant : NULL;
	}
	
	if (carry > 0)
		inserirInicio(result, novoItem(carry));

	return result;
}

Lista* mult(Lista* A, Lista* B)
{
	// Para identificar a maior lista.
	Lista* maior = (A->tamanho >= B->tamanho ? A : B);
	Lista* menor = (A->tamanho < B->tamanho ? A : B);

	Lista* result = novaLista();
	for (int i =0; i < A->tamanho + B->tamanho; i++)
		inserirInicio(result, novoItem(0));	

	Item* acurr = maior->fim;
	Item* bcurr = menor->fim;
	
	Item* cnext = result->fim;
	Item* ccurr = cnext;

	int avalue = 0;
	int bvalue = 0;
	
	int carry = 0;
	while (bcurr != NULL)
	{	
		bvalue = bcurr->valor;
		acurr  = maior->fim;
		ccurr  = cnext;
		carry  = 0;
		
		while (acurr != NULL)
		{		
			avalue = acurr->valor;
		
			// Multiplicação atual, soma-se ao resultado anterior
			// mais o possível carry. 
			int mult = avalue * bvalue + ccurr->valor + carry;
			ccurr->valor = mult % 10;
			carry = mult / 10;
		
			acurr = acurr->ant;
			ccurr = ccurr->ant;
		}
		
		if (carry > 0) 
			ccurr->valor += carry;
		
		bcurr = bcurr->ant;
		cnext = cnext->ant; 
	}
	
	if (result->inicio->valor == 0)
		removerInicio(result);	

	return result;
}

int main(int argc, char** argv)
{
	char* strA = (char *)malloc(512000 * sizeof(char));
    	char* strB = (char *)malloc(512000 * sizeof(char));
    	scanf("%s %s", strA, strB);

//	long al = atol(strA);
//	long bl = atol(strB);

	const char* x = strA;
     	const char* y = strB;

	Lista* A = tolist(x);
	Lista* B = tolist(y);

	Lista* r = mult(A, B);
//	printf("%ld\n", al * bl);
	printLista(r);
}
