---
layout: post
title: Listas duplamente encadeadas - Prática
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

# Exercícios 


##ex.1
{% highlight cpp %}
/* [ 1 ]
 Dada uma lista duplamente encadeada, percorrê-la e retornar o item na posição pos-1. 
 
 Caso pos < (l->tamanho)/2, então o percurso deve ser do início parra o fim
 Caso contrário, o percurso deve ser feito do fim para o início.
*/
Item* ponteiroParaPosicao(Lista* l, int pos);

Exemplo:
	pos = 3;
	ponteiroParaPosicao(L, pos);
	>> 0, 1, 2, 3, [4], 5, 6, 7; /* Ponteiro inicial aponta para o início */
	0, 1, >> 2, 3, [4], 5, 6, 7; /* Percorre da esquerda para direita até a posição anterior */
	 
	pos = 5;
	ponteiroParaPosicao(L, pos);
	0, 1, 2, 3, [4], 5, 6, 7 <<; /* Ponteiro inicial aponta para o fim */
	0, 1, 2, 3, [4] <<, 5, 6, 7; /* Percorre da direita para a esquerda até  posição anterior */
{% endhighlight %}


##ex.2
{% highlight cpp %}
/* [ 2 ]
 Implementar o operador de remoção do próximo, o qual recebe um ponteiro para o item
 anterior ao item a ser removido.
*/
void removerProximo(Lista* l, Item* i);

Exemplo:
	0, 1, 2, 3, 4, >> 5, 6, 7; /* Neste exemplo i é um ponteiro para o item 5 */
	0, 1, 2, 3, 4, 5, 7;       /* Esta é a lista após a remoção do item i->proximo */

{% endhighlight %}

##ex.3
{% highlight cpp %}
/* [ 3 ]
 Dada uma lista duplamente encadeada, reverter a ordem de seus itens, sem a
 utilização de uma nova lista.
*/
void reverterLista(Lista* l);

Exemplo:
	0, 1, 2, 3, 4, 5, 6, 7;
	7, 6, 5, 4, 3, 2, 1, 0; 

{% endhighlight %}

##ex.4
{% highlight cpp %}
/* [ 5 ]
 Liberar memória de todos os itens armazenados na lista.
*/
void freeLista(Lista* l);
{% endhighlight %}

##ex.5
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



	     






 
