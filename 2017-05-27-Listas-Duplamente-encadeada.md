---
layout: post
title: Listas duplamente encadeadas - Exercícios
description: 
author: jean
category: listas
tags: listas
finished: false
---

# Informação

  1. As salas de aplicação das provas serão as mesmas (105, 106)
  2. Início as 13h30, para tempo adicional


# Conteúdo da aula
  1. Revisão e resolução dos exercícios da aula anterior
  2. Início de pilhas sobre estruturas ligadas. 

# Exercícios resolvidos 

##ex.1
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
 

 Ao final desta função A e B apontam para os mesmos itens em uma lista. Assim,
 somente uma dessas listas deve ser usada para liberar a memória dos itens. 
*/
/*
 Insere a lista B no inicio da lista A. 
*/
void inserirListaInicio(Lista* A, Lista* B)
{
	assert(B->inicio != NULL);
	
	if (A->tamanho == 0) {
		A->inicio = B->inicio;
		A->fim = B->fim;
		A->tamanho = B->tamanho;
	} else {	
		A->inicio->ant = B->fim;
		B->fim->prox = A->inicio;

		A->inicio = B->inicio;
	
		A->tamanho += B->tamanho;
	}
}

/*
 Insere a lista B no fim da lista A. 
*/
void inserirListaFim(Lista* A, Lista* B)
{
	assert(B->inicio != NULL);
	
	if (A->tamanho == 0) {
		A->inicio = B->inicio;
		A->fim = B->fim;
		A->tamanho = B->tamanho;
	} else {

		A->fim->prox = B->inicio;
		B->inicio->ant = A->fim;
	
		A->fim = B->fim;
	
		A->tamanho += B->tamanho;
	}

}

/*
 Insere a lista B após o item 'atual' da lista A.
*/
void inserirListaAposAtual(Lista* A, Lista* B, Item* atual)
{
	assert(A->inicio != NULL && B->inicio != NULL);
	
	Item* A2 = atual->prox;
		
	atual->prox = B->inicio;
	B->inicio->ant = atual;
	
	B->fim->prox = A2;
	A2->ant = B->fim;
		
	A->tamanho += B->tamanho;
}



/*
 Insere a lista B em A, na posição especificada. Ao final desta função A e B
 apontam para os mesmos itens em uma lista. Assim, somente uma dessas listas
 deve ser usada para liberar a memória dos itens. 
*/
void inserirListaNaPosicao(Lista* A, Lista* B, int pos)
{
	assert(pos >=0 && pos <= A->tamanho);
	assert(B->inicio != NULL);

	if (pos == 0) {
		// Insere a lista B no inicio de A.
		inserirListaInicio(A, B);
	} else if (pos == A->tamanho) {
		// Insere a lista B no fim de A.
		inserirListaFim(A, B);
	} else {
		// Insere a lista B na posição 'pos' de A.
		Item* atual = ponteiroParaPosicao(A, pos);
		inserirListaAposAtual(A, B, atual);
	}
}
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
 	
 [!] Por simplicidade, esta implementação desconsidera o fato de pontos iguais
 poderem ser gerados por rand().
 
*/
void crossover(Lista* A, Lista* B, int pos)
{
	assert(pos > 0 && pos < A->tamanho -1);

	// primeiro ponto de crossover
	Item* pontoA = ponteiroParaPosicao(A, pos);
	Item* pontoB = ponteiroParaPosicao(B, pos);

	Item* pontoAprox = pontoA->prox;
	Item* pontoBprox = pontoB->prox;
	
	pontoA->prox = pontoBprox;
	pontoB->prox = pontoAprox;
	
	pontoBprox->ant = pontoA;
	pontoAprox->ant = pontoB;
	
	Item* aFim = A->fim;
	A->fim = B->fim;
	B->fim = aFim;
}


void crossoverNpontos(Lista* A, Lista* B, int n)
{
	for (int i = 0; i < n; ++i)
	{
		// posição aleatória de 1 a tamanho -1 - i
		int randompos = 1 + rand() % (A->tamanho - 2);
		fprintf(stderr, "%d\n", randompos);
			
		crossover(A, B, randompos);
		
		printLista(A);
		printLista(B);
	}
}
{% endhighlight %}





 





 
