#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "list.h"





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
	return i;
}


Item* ponteiroParaPosicao(Lista* l, int pos)
{
	Item* curr = l->inicio;
	for (int i = 0; i < pos - 1; ++i)
		curr = curr->prox;
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
		novo->prox = l->inicio;
		l->inicio = novo;
	}
	l->tamanho++;
}

void inserirProximo(Lista* l, Item* atual, Item* novo)
{
	assert(atual->prox != NULL);

	novo->prox = atual->prox;
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
		l->fim = novo;
		l->fim->prox = NULL;
	
		l->tamanho++;
	}
}



void inserirNaPosicao(Lista* l, Item* novo, int pos)
{	
	assert(pos >= 0 && pos <= l->tamanho);

	if (pos == 0)
		inserirInicio(l, novo);
	else if (pos == l->tamanho)
		inserirFim(l, novo);
	else {
		Item* curr = ponteiroParaPosicao(l, pos);
		inserirProximo(l, curr, novo);
	}	
}

// =============================================================================


Item* removerInicio(Lista* l)
{
	assert(l->tamanho > 0);
	
	Item* removed = NULL;
	
	if (l->tamanho == 1)
	{
		removed = l->inicio;
		l->inicio = NULL;
		l->fim = NULL;
	} else {
		removed = l->inicio;
		l->inicio = removed->prox;
	}
	l->tamanho--;
	
	
	return removed;
}

Item* removerProximo(Lista* l, Item* anterior)
{
	assert(anterior->prox->prox != NULL);
	
	Item* removed = anterior->prox;
	anterior->prox = removed->prox;
	
	l->tamanho--;
	
	return removed;
}

Item* removerFim(Lista* l)
{
	assert(l->tamanho > 0);
	
	Item* removed = NULL;
	
	if (l->tamanho == 1)
	{
		removed = l->fim;
		l->fim = NULL;
		l->inicio = NULL;		
	} else {
		removed = l->fim;
		l->fim = ponteiroParaPosicao(l, l->tamanho-1);
		l->fim->prox = NULL;
	}
	l->tamanho--;
	
	return removed;
}


Item* removerDaPosicao(Lista* l, int pos)
{
	assert(pos >= 0 && pos < l->tamanho);	
	
	Item* removed = NULL;
	
			
	if (pos == 0) {
		removed = removerInicio(l);		
	} else if (pos == l->tamanho-1) {
		removed = removerFim(l);	
	} else {
		Item* curr = ponteiroParaPosicao(l, pos);
		removed = removerProximo(l, curr);
	}
	
	return removed;
}

// =============================================================================


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


// TODO: não funcionando
void reverterLista(Lista* lista)
{
	assert(lista->fim != NULL);
	
	assert(lista->tamanho > 2);
	
	Item* atual = lista->fim;
	int atual_posicao = lista->tamanho - 1;
	
	// Se existe anterior, então a lista tem ao menos dois elementos.
	while(atual != lista->inicio)
	{
		Item* ptr_atual_ant = ponteiroParaPosicao(lista, atual_posicao - 2);
		Item* atual_ant = removerProximo(lista, ptr_atual_ant);
		inserirFim(lista, atual_ant);
		atual_posicao--;
	}
}

// =============================================================================

void freeLista(Lista* l)
{
	while (l->inicio != NULL)
		free(removerDaPosicao(l, 0));
}

