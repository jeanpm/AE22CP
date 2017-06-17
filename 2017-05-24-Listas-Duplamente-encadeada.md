---
layout: post
title: Listas duplamente encadeadas - Teórica
description: 
author: jean
category: listas
tags: listas
finished: false
---

# Instruções
Baixar os arquivos em [https://goo.gl/jxIq7t](https://goo.gl/jxIq7t)

  * list.h
  * dlist.c
  * testaLista.c
  
Implementar as funções em *dlist.c* que ainda não estejam implementadas. Em seguida, compilar e executar *testaLista.c*.

{% highlight cpp %}
	Item* ponteiroParaPosicao(Lista* l, int pos);
	Item* removerProximo(Lista* l, Item* anterior);	
	Item* removerDaPosicao(Lista* l, int pos);
	void reverterLista(Lista* lista);
	void freeLista(Lista* l);
	bool verificarPalindromo(Lista* l)
{% endhighlight %}

# Exercícios resolvidos 


##ex.1
{% highlight cpp %}
/* [ 1 ]
 Dada uma lista duplamente encadeada, percorrê-la e retornar o item na posição pos-1. 
 
 Caso pos < (l->tamanho)/2, então o percurso deve ser do início parra o fim
 Caso contrário, o percurso deve ser feito do fim para o início.
 
 Exemplo:
	pos = 3;
	ponteiroParaPosicao(L, pos);
	>> 0, 1, 2, 3, [4], 5, 6, 7; // Ponteiro inicial aponta para o início 
	0, 1, >> 2, 3, [4], 5, 6, 7; // Percorre da esquerda para direita até a posição anterior 
	 
	pos = 5;
	ponteiroParaPosicao(L, pos);
	0, 1, 2, 3, [4], 5, 6, 7 <<; // Ponteiro inicial aponta para o fim 
	0, 1, 2, 3, [4] <<, 5, 6, 7; // Percorre da direita para a esquerda até  posição anterior 
 
*/
Item* ponteiroParaPosicao(Lista* l, int pos)
{
	Item* curr = NULL;
	
	if (pos < l->tamanho/2) {
		curr = l->inicio;
		for (int i = 0; i < pos - 1; ++i)
			curr = curr->prox;
	} else {
		curr = l->fim;
		for (int i = l->tamanho-1; i > pos-1; --i)
			curr = curr->ant;
	}
	
	return curr;
}
{% endhighlight %}


##ex.2
{% highlight cpp %}
/* [ 2 ]
 Implementar o operador de remoção do próximo, o qual recebe um ponteiro para o item
 anterior ao item a ser removido.

 Exemplo:
	0, 1, 2, 3, 4, >> 5, 6, 7; // Neste exemplo i é um ponteiro para o item 5 
	0, 1, 2, 3, 4, 5, 7;       // Esta é a lista após a remoção do item i->proximo 
*/
void removerProximo(Lista* l, Item* i);
{
	assert(anterior->prox->prox != NULL);
	
	Item* removed = anterior->prox;
	removed->prox->ant = anterior;
	anterior->prox = removed->prox;
	
	l->tamanho--;
	
	return removed;
}

{% endhighlight %}


##ex.3
{% highlight cpp %}
/* [ 3 ]
 Dada uma lista duplamente encadeada, remover o item da posição indicada.
 
 Exemplo:
 	pos = 3;
	>> 0, 1, 2, [3], 4, 5, 6, 7; // Remover o item na posição 3
	0, 1, >> 2, [3], 4, 5, 6, 7; // Percorre da esquerda para direita até o anterior.
	0, 1, 2, 4, 5, 6, 7;         // Remove o próximo.
	
*/
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
{% endhighlight %}

##ex.4
{% highlight cpp %}
/* [ 4 ]
 Dada uma lista duplamente encadeada, reverter a ordem de seus itens, sem a
 utilização de uma nova lista.
 
 Exemplo:
	0, 1, 2, 3, 4, 5, 6, 7;
	7, 6, 5, 4, 3, 2, 1, 0; 
 
*/
void reverterLista(Lista* l)
{
	assert(lista->fim != NULL);
	
	Item* curr = lista->fim;
	
	// Se existe anterior, então a lista tem ao menos dois elementos.
	while(curr != lista->inicio)
	{
		Item* anterior = curr->ant;
		removerItem(lista, anterior);
		inserirFim(lista, anterior);
	}
}
{% endhighlight %}


# Exercícios novos

##ex.5
{% highlight cpp %}
/* [ 5 ]
 Dada uma lista duplamente encadeada, reverter a ordem dos itens que estiverem
 entre os ponteiros recebidos como parâmetro.
 
 Exemplo:
	0, 1, >> 2, 3, 4, >> 5, 6, 7;
	0, 1,   5, 4, 3, 2,  6, 7; 
*/
void reverterSegmentoDeLista(Lista* l, Item* inicio, Item* fim);
{
	assert(fim != NULL);
	
	Item* curr = fim;
	
	// Se existe anterior, então a lista tem ao menos dois elementos.
	while(curr != inicio)
	{
		Item* anterior = curr->ant;
		removerItem(lista, anterior);
		inserirFim(lista, anterior);
	}
}
{% endhighlight %}


##ex.6
{% highlight cpp %}

/*
 Dara uma lista duplamente encadeada, verificar se ela representa um palíndromo
 
 Definição:
 
 	Palíndromo é uma palavra, uma frase, ou lista qualquer que quando
 	percorrida da esquerda para direita, ou da direita para a esquerda 
 	produza a mesma sequência.
 Exemplo:
 	"Roma tem amor",
 	"Socorram-me, subi no ônibus em Marrocos",
 	"A mãe te ama". 
 
*/
bool verificaPalindromo(Lista* l);

Exemplo:	
	L = 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1
	true;
	L = 1, 2, 3, 4, 5, 5, 4, 3, 2, 1
	true;
	L = 1, 2, 3, 4, 5, 6, 7, 4, 3, 2, 1
	false;
	
{% endhighlight %}


##ex.7
{% highlight cpp %}

/*
 Dara uma lista duplamente encadeada e uma posição, inserir nesta posição outra
 lista encadeada.
 
 Exemplo:
 	A = 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	B = 9, 9, 9, 9
	pos = 3
	
 	inserirListaNaPosicao(Lista* A, Lista* B, int pos);
 	
 	A = 1, 1, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1
 
*/
void inserirListaNaPosicao(Lista* A, Lista* B, int pos);


{% endhighlight %}

#ex.8
{% highlight cpp %}

/*
 Dadas duas listas duplamente encadeadas e uma posição, implementar o crossin-over.
 
 Exemplo:
 	A = 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	B = 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
	pos = 3
	
 	crossover(Lista* A, Lista* B, int pos);
 	
 	A = 1, 1, 1, 9, 9, 9, 9, 9, 9, 9
 	B = 9, 9, 9, 1, 1, 1, 1, 1, 1, 1
 
*/
bool crossover(Lista* A, Lista* B, int pos);

{% endhighlight %}	     






 





 
