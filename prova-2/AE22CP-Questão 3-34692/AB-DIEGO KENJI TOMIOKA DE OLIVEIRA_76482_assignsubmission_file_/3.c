#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Item
{
    int valor;
    struct Item *prox;
    struct Item *ant;

}Item;

typedef struct Lista
{
    int tamanho;
    struct Item *inicio;
    struct Item *fim;
}Lista;

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


Item* ponteiroParaPosicao(Lista* l, int pos)
{
	Item* curr = NULL;
	int i;

	if (pos < l->tamanho/2) {
		curr = l->inicio;
		for (i = 0; i < pos - 1; ++i)
			curr = curr->prox;
	} else {
		curr = l->fim;
		for (i = l->tamanho; i > pos; --i)
			curr = curr->ant;
	}

	return curr;
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

void inserirProximo(Lista* l, Item* atual, Item* novo)
{

	novo->prox = atual->prox;
	novo->ant = atual;

	atual->prox->ant = novo;
	atual->prox = novo;

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

void printLista(Lista* l)
{
	Item* curr = l->inicio;
	while(curr != NULL)
	{
		fprintf(stderr, "%d\t", curr->valor);
		curr = curr->prox;
	}
	fprintf(stderr, "\n");
}

Lista *tolist (char x[])
{
    Lista *l=novaLista(l);
    int i=0,a;
    while(x[i]!='\0')
    {
        a=(int)(x[i]-'0');
        inserirFim(l,novoItem(a));
        i++;
    }

    return l;
}

Lista *add (Lista *a, Lista *b)
{
    Lista *l=novaLista();
    Item *aux=a->inicio;
    Item *aux2=b->inicio;

    while(aux!=NULL)
    {
        inserirFim(l,novoItem(aux->valor));
        aux=aux->prox;
    }

    while(aux2!=NULL)
    {
        inserirFim(l,novoItem(aux2->valor));
        aux2=aux2->prox;
    }


    return l;
}


int main()
{
    char x[100];
    char y[100];
    int i=0;
    strcpy(x,"21030");
    strcpy(y,"2192");

    Lista *a=novaLista();
    Lista *b=novaLista();
    a=tolist(x);
    b=tolist(y);
    printLista(add(a,b));


    return 0;
}
