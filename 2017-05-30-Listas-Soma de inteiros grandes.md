---
layout: post
title: Representar inteiros grandes utilizando listas
description: Exercitar a utilização de listas duplamente encadeadas, para a representação de inteiros de tamanho arbitário. A operação de adição é ilustrada.
author: jean
category: listas dinâmicas
tags: exercicios-listas
finished: false
---

# Conteúdo
* Do not remove this line (it will not be displayed)
{:toc}


# Representação de inteiros grandes por listas

Em geral, linguagens de programação possuem um tipo de dados inteiro (**int**) que suporta operações básicas como: adição, subtração, multiplicação e divisão. Na prática, no entanto, essas operações são limitadas a valores inteiros menores que um certo limite (`INT_MAX`). Deste modo, para aplicações específicas, em que valores maiores que `INT_MAX` precisem ser manipulados, o tipo int se torna inadequado. 

Uma forma alternativa de se representar inteiros maiores que `INT_MAX`, seria utilizar uma estrutura de dados lista, na qual cada item da lista armazene um único dígito (`0-9`) do inteiro em questão.

## Objetivo
Utilizar listas duplamente encadeadas dinâmicas para implementar a adição de inteiros grandes positivos! **(Peso: 3,0)**
  
## Descrição

Considere que os inteiros grandes (positivos) estão incialmente em uma string cada. Exemplo:

{% highlight cpp %}
	const char* x ="92233720368547758079223372036854775807";
	const char* y ="2147483";
{% endhighlight %}	

Cada string deve ser, então, transformada em uma lista de inteiros por uma função `tolist`, a ser implementada.
 {% highlight cpp %} 
	Lista* tolist(const char* string); // Implementar
{% endhighlight %}	

Observe que, para converter um caractere numérico qualquer c=‘1’ para respectivo inteiro a=1, deve-se utilizar o seguinte código.

{% highlight cpp %}
	int a = (int) (c - ‘0’); 
{% endhighlight %}

Como exemplo, após a função `tolist`, a string `y` se tornaria uma lista de inteiros.

$$2 \leftrightarrow 1 \leftrightarrow 4 \leftrightarrow 7 \leftrightarrow 4 \leftrightarrow 8 \leftrightarrow 3 $$


## Adição de inteiros em listas
Dadas duas listas dinâmicas duplamente encadeadas A e B, representando números inteiros grandes, adicioná-las e imprimir a lista resultante.
{% highlight cpp %}
	const char* x ="9999";
	const char* y ="22";
	
	Lista* A = tolist(x); // 9 <-> 9 <-> 9 <-> 9
	Lista* B = tolist(y); //             2 <-> 2
	
	Lista* C = add(A, B); // 1 <-> 0 <-> 0 <-> 2 <-> 1
	
	printList( C );       // "10021"
{% endhighlight %}

## Listas dinâmicas versus estáticas 
Indique uma motivação para o uso de listas dinâmicas, e não estáticas, na resolução do problema acima? **(Peso: 1,0)**


# Implementação - cpp

{% highlight cpp %}
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
Lista* tolist(const char* x)
{
	int xlen = strlen(x);

	Lista* xlista = novaLista();
	for (int i = 0; i < xlen; i++)
	{
		int digito = (int) x[i] - '0';
		inserirFim(xlista, novoItem(digito));
	}
	return xlista;
}

/* Função auxiliar
   Adiciona a + b + carry.
   Inicialmente carry é zero.
   Como a some é de dígitos, somente a parte (x % 10) é retornada.
   A parte que sobra vai como carry para outra iteração.
   Exemplo:
   	a = 9;
	b = 9;
	carry = 0;

	sum   = (9 + 9 + 0) % 10; // sum == (18 % 10); sum == 8;
	carry = (9 + 9 + 0) / 10; // sum == (18 / 10); sum == 1;
*/
int addDigit(int a, int b, int* carry)
{
	int sum = (a + b + (*carry)) % 10;
	*carry  = (a + b + (*carry)) / 10;

	return sum;
}


/*

Condições:
	A lista A pode ser maior que a lista B, ou vice-versa;
Funcionamento:
	soma-se o item atual de A, o item atual de B e o carry, enquanto houver elementos em ambas.
Exceção:
	1. Se A > B, os elementos que restarem de A serão somados apenas com o carry.
	2. Se ao fim de A, o carry ainda for > 0, ele é inserido na lista resultante.
*/
Lista* add(Lista* A, Lista* B)
{
	// Para identificar a maior lista.
	Lista* maior = (A->tamanho >= B->tamanho ? A : B);
	Lista* menor = (A->tamanho < B->tamanho ? A : B);

	Lista* result = novaLista();

	int carry = 0;

	Item* acurr = maior->fim;
	Item* bcurr = menor->fim;

	/*
	 1.Caso: (enquanto bcurr != NULL)
	 Soma-se os itens de ambas as listas ao carry, de trás para frente
	 	    ___
	 	999 999
	 	    111

	 2.Caso: (enquanto bcurr == NULL)
	 Soma-se os itens restantes da lista maior ao carry, é similar a considerar que os itens 
	 inexistentes em B são zero.
	 	___   
	 	999 999
	 	000 111
	*/
	int avalue = 0;
	int bvalue = 0;
	while (acurr != NULL)
	{	
		avalue = acurr->valor;
		bvalue = (bcurr != NULL) ? bcurr->valor : 0;
		
		int sum = addDigit(avalue, bvalue, &carry);
		inserirInicio(result, novoItem(sum));
		
		acurr = acurr->ant;
		bcurr = (bcurr != NULL) ? bcurr->ant : NULL;
	}
	
	if (carry > 0)
		inserirInicio(result, novoItem(carry));

	return result;
}

int main(int argc, char** argv)
{
	assert(argc == 3);

	//const char* x ="99989";
     	//const char* y ="1";
     	
     	/*
     	Para testar a corretude da soma de listas, testar com strings que caibam
     	num long.
     	*/
	long al = atol(argv[1]);
	long bl = atol(argv[2]);

	const char* x = argv[1];
     	const char* y = argv[2];

	Lista* A = tolist(x);
	Lista* B = tolist(y);
	printLista(A);
	printLista(B);

	Lista* r = add(A, B);
	
	// As duas ultimas linhas impressas devem ser iguais, a menos que a 
	// string recebida em argv[1]+argv[2] não caibam num long.
	printf("%ld\n", al + bl);
	printLista(r);

}
{% endhighlight %}
 





 
