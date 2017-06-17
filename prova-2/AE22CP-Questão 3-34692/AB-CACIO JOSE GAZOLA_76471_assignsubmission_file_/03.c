// questão 3
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <time.h>

typedef struct dig								//estrutura do tipo de dados
{
	char num;
	struct dig *prox;
	struct dig *ant;

}dig;

typedef struct    									//Lista com dados do tipo comida.
{
	int qt;
	dig *inicio;
	dig *fim;
}LD;

//**************************************************
//EScopo das funções 
//**************************************************
LD* paralista(const char* s);
Lista* novaLista();
dig* novoItem(int value);
void printLista(Lista* l);
LD* SomaListas(LD *A, LD *B);
//**************************************************
//MAIN
//**************************************************
int main(void)
{
	const char* x = "1236574839482736";
	const char* y = "2031123";

	LD* A;
	LD* B;

	crialista(A);
	crialista(B);

	paralista(x,&A);
	paralista(y,&B);

	printf("%s \n", SomaListas(A,B));


	/* code */
	return 0;
}


//*************************************
//FUNÇOES
//*************************************

Lista* crialista(LD *l)
{
	LD* l = (Lista*) malloc(sizeof(LD));
	l->inicio = NULL;
	l->fim    = NULL;
	l->tamanho = 0;
	
	return l;
}

dig* novoItem(int value)
{
	dig *i = (dig*) malloc(sizeof(Item));
	i->num = value;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}

LD* paralista(const char* s, LD *l)
{
	if (l->inicio == NULL) 
	{
		l->inicio = s[0];
		l->fim = l->inicio;
		l->tamanho++;
	}

	int i=1;

	while(s[i] != NULL)
	{
		l->inicio->ant = s[i];
		s[i]->prox = l->inicio;
		l->inicio = s[i];
		l->tamanho++;
	}

}

void printLista(LD* l)
{
	dig* curr = l->inicio;
	while(curr != l->fim)
	{
		fprintf(stderr, "%d\t", curr->num); 
		curr = curr->prox;
	}
	fprintf(stderr, "%d\t\n", curr->num);
	//printf("\n");
}

//'Somar' duas listas 
LD* SomaListas(LD *A, LD *B)
{
	dig* numA, numB;
	numA = A->fim;
	numB = B->fim;

	while(numA != A->inicio || numB != B->inicio)
	{
		int a = (int) (numA - '0');
		int b = (int) (numB - '0');

		a = a+b;

		numA = (char) (a + '0');

		numB = numB->ant;
		numA = numA->ant;
	}
	return A;
}