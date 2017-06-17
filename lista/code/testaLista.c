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

int main(int argc, char** argv)
{
	srand(time(NULL));
	assert(argc == 2);
	int pos = atoi(argv[1]);

	Lista* A = novaLista();
	Lista* B = novaLista();

	int lsize = 5;
	for (int i = 0; i < lsize; ++i)
	{
		inserirInicio(A, novoItem(1));
		inserirInicio(B, novoItem(8));
	}

	Lista* t = novaLista();
printLista(t);
	
	printLista(A);
	printLista(B);

	inserirListaNaPosicao(A, B, pos);
	
//	crossoverNpontos(A, B, 3);

	printf("Tamanho de A: %d\n", A->tamanho);	
	printf("Tamanho de B: %d\n", B->tamanho);

	teste(A,B);
	printf("Tamanho de A: %d\n", A->tamanho);	
	printf("Tamanho de B: %d\n", B->tamanho);
	
	printLista(A);
	printLista(B);
	
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
