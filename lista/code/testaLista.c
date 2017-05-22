#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "list.h"

int main(int argc, char** argv)
{
	Lista* l = novaLista();
	
	inserirInicio(l, novoItem(0));
	inserirFim(l, novoItem(1));
	
	for (int i = 2; i < 1000; ++i)
		inserirNaPosicao(l, novoItem(i), rand() % l->tamanho);

	printLista(l);
	
	while (l->tamanho > 0)
		free(removerDaPosicao(l, rand() % l->tamanho));
	
	freeLista(l);
	free(l);
}
