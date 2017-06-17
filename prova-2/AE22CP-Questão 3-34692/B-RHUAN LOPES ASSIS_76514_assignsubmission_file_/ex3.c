#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
typedef struct item{
    char c[30];
    struct item* prox;
    struct item* ant;
}item;

typedef struct lista{
    int quant;
    struct item* bgn;
    struct item* end;
}lista;
lista* crialde()
{
	lista* l = (lista*) malloc(sizeof(lista));
	l->bgn = NULL;
	l->end = NULL;
	l->quant = 0;

	return l;
}
void inserirListaFim(lista* a, lista* b)
{
	assert(b->bgn != NULL);

	if (a->quant == 0) {
		a->bgn = b->bgn;
		a->end = b->end;
		a->quant = b->quant;
	} else {
		a->end->prox = b->bgn;
		b->bgn->ant = a->end;

		a->end = b->end;

		a->quant += b->quant;
	}
}
void inserirbgn(lista* l, item* novo)
{
	// Se lista vazia
	if (l->bgn == NULL) {
		l->bgn = novo;
		l->end = l->bgn;
	} else {
		l->bgn->ant = novo;
		novo->prox = l->bgn;
		l->bgn = novo;
	}
	l->quant++;
}
item* criaitem(char v[])
{
	item *i = (item*) malloc(sizeof(item));
	i->c = v;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}
int main()
{
    lista l, l1;
    crialde(&l);
    crialde(&l1);
    item i = criaitem("098765678")
    item i2 = criaitem("13456757876543")
    inserirbgn(&l,i);
    inserirbgn(&l,i2);
    inserirListaFim(&l,&l1);
}
