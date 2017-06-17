#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "list.h"

// https://goo.gl/WJX0Ik

int main(int argc, char** argv)
{
	assert(argc == 2);
	int pos = atoi(argv[1]);

	Lista* A = novaLista();
	Lista* B = novaLista();

	int lsize = 8;
	for (int i = 0; i < lsize; ++i)
	{
		inserirInicio(A, novoItem(1));
		inserirInicio(B, novoItem(8));
	}
	
	printLista(A);
	printLista(B);
	
//s	inserirListaNaPosicao(A, B, pos);
	
	
	crossoverNpontos(A, B, 3);
	
	
	printLista(A);
	printLista(B);
	
	freeLista(A);
//	freeLista(B);
	
	free(A);
	free(B);
}
