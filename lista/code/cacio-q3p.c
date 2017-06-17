// questão 3 versão sem carry
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <time.h>

typedef struct dig								//estrutura do tipo de dados
{
	int num;
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
LD* paralista(char* s, LD* l);
LD* novaLista(LD* l);
dig* novoItem(int value);
void printLista(LD* l);
LD* SomaListas(LD *A, LD *B);
void inserir(LD* l, dig* novo);
//**************************************************
//MAIN
//**************************************************
int main(void)
{
	char* y = "9999999999482736";
	char* x = "2031123";

	LD* A = novalista(A);
	LD* B = novalista(B);
	LD* D;
  
	paralista(x,A);
	paralista(y,B);

	printLista(A);
	printf("\n");
	printLista(B);

	printf("Após somar: \n");
	D = SomaListas(A,B);
	printf("Retornou da soma\n");
	printLista(D);

	/* code */
	return 0;
}


//*************************************
//FUNÇOES
//*************************************
LD* novalista(LD* l)
{
	l = malloc(sizeof(LD));
	l->inicio = NULL;
	l->fim    = NULL;
	l->qt = 0;
	
	return l;
}

dig* novoItem(int value)
{
	dig *i = malloc(sizeof(dig));
	i->num = value;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}

LD* paralista(char* s, LD *l)
{
	dig* aux;
	//Primeiro elemento da lista
	aux = novoItem((int) s[0]-'0');
	l->inicio = aux;
	l->fim = l->inicio;
	l->qt++;
	
	int i=1;

	while(s[i] != '\0')
	{

		aux = novoItem((int) s[i]-'0');
		l->fim->prox = aux;
		aux->ant = l->fim;
		l->fim = aux;
		l->qt++;
		i++;
	}

}
void printLista(LD* l)
{
	dig* curr = l->inicio;
	int c=0;
	while(curr != l->fim)
	{
		c++;
		printf("%d\t", curr->num); 
		curr = curr->prox;
		if(c%9==0)
		{
			printf("\n");
		}
	}
	printf("%d\t\n", curr->num);
	//printf("\n");
}

//'Somar' duas listas 
LD* SomaListas(LD *A, LD *B)
{
	dig *numA, *numB, *aux;
	numA = A->fim;
	numB = B->fim;
	int a, carry=0;

	LD* C = novalista(C);
	
	//registro de controle de estados
	char rc='0';	


	while(numB != NULL && numA != NULL )
	{
		a = (numA->num + numB->num + carry)%10;

		if((numA->num + numB->num + carry) /10)
		{
			carry = 1;
		} 
		else 
		{
			carry = 0;
		}
		
		aux = novoItem(a);
		inserir(C,aux);
		               
		numB = numB->ant;
		numA = numA->ant;
	}
	
	if (numB == NULL)
	{
		rc = 'b';
	}
	else 
	{
		rc = 'a';
	}

	//Se B chegou ao fim e sobrou elementos em A e um carry, devemos copiar os elementos para 'C' propagando carry  em C
	if(rc == 'b')
	{
		while (numA != NULL && carry == 1  )
		{
			a = (numA->num + carry) %10;

			if((numA->num + carry) /10)
			{
				carry = 1;
			} 
			else 
			{
				carry = 0;
			}
			
			aux = novoItem(a);
			inserir(C,aux);
			
			numA = numA->ant;
		}
		
		//Se ainda assim sobrou carry. devemos criar uma novo elemento
		if(carry==1)
		{
			//dig* aux;
			
			aux = novoItem(1);
			aux->prox = C->inicio;
			C->inicio->ant = aux;
			C->inicio= aux;
			C->qt++;
		}
	} 

	//Se A chegou ao fim e sobrou elementos em B, devemos copiar os elementos para C propagando carry, se houver
	if(rc == 'a')
	{
		while(numB!=NULL)
		{
			a = (numB->num + carry) %10;

			if((numB->num + carry) /10)
			{
				carry = 1;
			} 
			else 
			{
				carry = 0;
		}

		//dig* aux;
		aux = novoItem(a);
		aux->prox = C->inicio;
		C->inicio->ant = aux;
		C->inicio= aux;
		C->qt++;

		numB = numB->ant;
		
		}
		//Se ainda assim sobrou carry. devemos criar uma novo elemento
		if(carry==1)
		{
			//dig* aux;
			
			aux = novoItem(1);
			aux->prox = C->inicio;
			C->inicio->ant = aux;
			C->inicio= aux;
			C->qt++;
		}
	} 
	return C;
}


// =============================================================================

void inserir(LD* l, dig* novo)
{
	// Se lista vazia
	if (l->inicio == NULL) 
	{
		l->inicio = novo;
		l->fim = l->inicio;
	} 

	else 
	{
		l->inicio->ant = novo;
		novo->prox = l->inicio;
		l->inicio = novo;
	}
	l->qt++;
}

