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
	i->ant  = NULL;
	return i;
}

/*
Item* ponteiroParaPosicao(Lista* l, int pos)
{
	Item* curr = l->inicio;
	for (int i = 0; i < pos - 1; ++i)
		curr = curr->prox;
	return curr;
}
*/

/* 
 Versão que verifica o melhor percurso, dentre: 
	+ ir do inicio ao fim,
	+ ir do fim ao começo.
*/
Item* ponteiroParaPosicao(Lista* l, int pos)
{
	// IMPLEMENTAR	
	fprintf(stderr, "ponteiroParaPosicao(Lista* l, int pos) - não implementada\n");
	exit(-1);

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
	assert(atual->prox != NULL);

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
		
		l->inicio->ant = NULL;
	}
	l->tamanho--;
	
	
	return removed;
}

Item* removerProximo(Lista* l, Item* anterior)
{
	assert(anterior->prox->prox != NULL);
	
	Item* removed = anterior->prox;
	removed->prox->ant = anterior;
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
		l->fim = removed->ant;
		
		l->fim->prox = NULL;
	}
	l->tamanho--;
	
	return removed;
}

void removerItem(Lista* lista, Item* i)
{
	if (i == lista->inicio)
		removerInicio(lista);
	else if (i == lista->fim)
		removerFim(lista);
	else {
		// Se não é início nem fim, o item possui antecessor e sucessor.
		// Então basta atualizar os ponteiros, removendo-o da lista.
		i->ant->prox = i->prox;
		i->prox->ant = i->ant;
		
		lista->tamanho--;
	} 
}

Item* removerDaPosicao(Lista* l, int pos)
{
	// IMPLEMENTAR
	fprintf(stderr, "removerDaPosicao(Lista* l, int pos) - não implementada\n");
	exit(-1);
	return NULL;
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



void reverterLista(Lista* lista)
{
	// IMPLEMENTAR
	fprintf(stderr, "reverterLista(Lista* lista) - não implementada\n");
}

// =============================================================================

void freeLista(Lista* l)
{
	// IMPLEMENTAR
	fprintf(stderr, "freeLista(Lista* l) - não implementada\n");
}

