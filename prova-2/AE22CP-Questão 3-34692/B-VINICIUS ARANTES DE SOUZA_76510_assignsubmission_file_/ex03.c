#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct Lista{
    int quantidade;
    struct item* inicio;
    struct item* fim;
}Lista;

typedef struct Item{
    int valor;
    struct item* prox;
    struct item* ant;
}Item;


Lista* novaLista()
{
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l->inicio = NULL;
	l->fim    = NULL;
	l->quantidade = 0;
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

Lista* add(Lista* A, Lista* B);
{
    assert(B->inicio!=NULL);
    if(A->tamanho==0)
    {
        A->inicio=B->inicio;
        A->fim=B->fim;
        A->tamanho=B->tamanho;
    }
    else
    {
        B->fim->prox=A->inicio;
        A->inicio->ant=B->fim;
        A->inicio=B->inicio;
        A->tamanho=A->tamanho+B->tamanho;
    }
}

Lista* tolist(const char* string)
{
    int a=(int)(c-'0');
}

void printLista(Lista* l)
{
	Item* curr = l->inicio;
	while(curr != l->fim)
	{
		fprintf(stderr, "%d\t", curr->valor);
		curr = curr->prox;
	}
	fprintf(stderr, "\n");
}

int main()
{
    const char* x = "78945613246579845613245648465";
    const char* y = "13498465";

    Lista* A = tolist(x);
    Lista* B = tolist(y);
    printLista(add(A,B));


    return 0;
}
