#include <stdio.h>
#include <limits.h>
#include <assert.h>

typedef struct lista{

    int quant;
    struct elem *inicio;
    struct elem *fim;

}lista;


typedef struct elem{

    int num;
    struct elem *prox;
    struct elem *ant;
}elem;

lista* novaLista()
{
	lista* l = (lista*) malloc(sizeof(lista));
	l->inicio = NULL;
	l->fim    = NULL;
	l->quant = 0;

	return l;
}

elem* novoItem(int value)
{
	elem *i = (elem*) malloc(sizeof(elem));
	i->num = value;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}
void inserirInicio(lista* l, elem* novo)
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
	l->quant++;
}
void add(lista* A, lista* B)
{
    assert(B->inicio != NULL);
	if(A->quant == 0)
    {
        A->inicio = B->inicio;
		A->fim = B->fim;
		A->quant = B->quant;
    }
    else{
        A->fim->prox=B->inicio;
        B->inicio->ant=A->fim;

        A->fim=B->fim;
        A->quant+=B->quant;
        }
}
void printLista(lista* l)
{
	elem* curr = l->inicio;
	while(curr != l->fim)
	{
		fprintf(stderr, "%d\t", curr->num);
		curr = curr->prox;
	}
	fprintf(stderr, "%d\t", curr->num);
	fprintf(stderr, "\n");
}
//



int main(int argc, char** argv)
{

	int pos = 3;

	lista* A = novaLista();
	lista* B = novaLista();

	int lsize = 5;
	int i;
	for (i = 0; i < lsize; ++i)
	{
		inserirInicio(A, novoItem(1));
		inserirInicio(B, novoItem(8));
	}

	printLista(A);
	printLista(B);
	//adicionar;
	add(A,B);
	printf("\n");
	printLista(A);

	return 0;
}
