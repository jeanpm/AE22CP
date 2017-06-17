#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#include "list.h"

int teste(Lista* A, Lista* B)
{
	A = B;
}


typedef struct
{
	int value;
} Int;

void printDouble(Type* t)
{
//	Int* i = (Int*) t;
	double* i = (double*) t;
	printf("%.1f ", *i); 	
}


typedef struct
{
	int a;
	int b;
} Fracao;

void printFracao(Type* t)
{
	Fracao* i = (Fracao*) t;
	printf("%d/%d ", i->a, i->b); 	
}

void insereNaLista(Lista* A, Lista* B)
{
	int lsize = 5;
	for (int i = 0; i < lsize; ++i)
	{
//		Fracao* a = (Fracao*) malloc(sizeof(Fracao));//{1,5};
//		Fracao* b = (Fracao*) malloc(sizeof(Fracao));//{8, 2};
//		a->a = 1; a->b = 5;
//		b->a = 8; b->b = 2;
		double a = 10.5;
		double b = 2.3;
		inserirInicio(A, novoItem(&a));
		inserirInicio(B, novoItem(&b));
	}
	printLista(A, printDouble);
	printLista(B, printDouble);
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	assert(argc == 2);
	int pos = atoi(argv[1]);

	Lista* A = novaLista();
	Lista* B = novaLista();
	
	insereNaLista(A, B);

	void (*printval)(Type* t) = &printDouble;
	printLista(A, printval);
	printLista(B, printval);

	inserirListaNaPosicao(A, B, pos);
	
//	crossoverNpontos(A, B, 3);

	printLista(A, printval);
	printLista(B, printval);
	
	freeLista(A);
//	freeLista(B);
	
	free(A);
	free(B);
}

/*
1	1	1	1	1
8	8	8	8	8

2

1	1	8	8	8
8	8	1	1	1


3

1	1	8	1	1
8	8	1	8	8


2, 3 

1	1	8	1	1
8	8	1	8	8



*/
