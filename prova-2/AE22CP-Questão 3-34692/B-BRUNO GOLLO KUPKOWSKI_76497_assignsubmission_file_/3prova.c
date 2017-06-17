#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "list.h"


Lista* add(Lista*A, Lista *B)
{
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l->inicio = NULL;
	l->fim    = NULL;
	l->tamanho = 0;

	return l;
}

Item* tolist( char* string)
{
    Item *i = (Item*) malloc(sizeof(Item));
	i->valor = string;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}

void printLista (Lista *l)
{
if (l->inicio != NULL)
{
Item* curr = l->inicio;
while(curr != l->fim)
{
fprintf(stderr, "%d", curr->valor);
curr = curr->prox;
}
fprintf(stderr, "%d\n", curr->valor);
}
}


int main()
{
    add(922337, 2147);
    //Lista*A = tolist(x);
    //Lista*B = tolista(y);
    printLista(x="9223372", y="2147");

    return 0;
}

