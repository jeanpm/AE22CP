---
layout: post
title: Validação de expressões parentizadas
description:  Introduz a estrutura de dados Pilha, a qual consiste de operações push, pop e top, implementadas sobre uma lista duplamente encadeada. O problema da validação de parênteses é utilizado didaticamente.
author: Jean P. Martins
category: pilhas dinâmicas
tags: pilhas
finished: false
---


> Achamos que, no estágio de desenvolvimento de um estudante para o qual este texto foi elaborado, é mais importante discutir vários exemplos em detalhes do que uma ampla variedade de tópicos superficialmente. 
> [Estruturas de dados usando C (Tenenbaum et al.)][1]

# Conteúdo
* Do not remove this line (it will not be displayed)
{:toc}

# A Pilha

A estrutura de dados Pilha recebe este nome em analogia ao processo de empilhamento. De acordo com o dicionário web [Michaelis](http://michaelis.uol.com.br/busca?r=0&f=0&t=0&palavra=empilhar), empilhar tem o seguinte significado:

*em·pi·lhar*
Dispor em pilha ou ficar amontoado em pilha; amontoar(-se): 

  * Empilhou os pratos que havia acabado de enxugar. 
  * “[…] erguia o que estava pelo chão e empilhava as cadeiras sobre as mesinhas de mármore” (AA2). 
  * “Entrou no seu escritório e foi sentar-se à secretária. Defronte dele, com uma gravidade oficial, empilhavam-se grandes livros de escrituração mercantil” (AA2).

De acordo com esta definição, empilhar significa inserir um objeto em cima de outro. Desempilhar, portanto, se refere a remoção do objeto no topo da pilha. 

Dada a analogia, define-se que uma estrutura de dados pilha é caracterizada pelo fato de que novos elementos somente podem ser inseridos em seu topo. A remoção de elementos da pilha, similarmente, somente pode acontecer para elementos no topo. O acesso ao elemento no topo da pilha, sem a remoção do mesmo, é muitas vezes necessário, desta forma um operador se faz necessário. Essas operações são tradicionalmente definidas como:
  
{% highlight cpp %}
/*
 Aloca memória para uma nova pilha
*/
Pilha* novaPilha();

/*
 Insere um novo item no topo da pilha 
*/
void  push(Pilha* p, Item* i); 

/*
 Remove o item do topo da pilha 
*/
Item* pop (Pilha* p); 

/*
 Retorna o elemento do topo da pilha, sem removê-lo da mesma.
*/
Item* top(Pilha* p);
{% endhighlight %}

## Exemplo de inserção

A pilha p está inicialmente vazia, logo top(p) retornaria NULL. À medida que novos itens são inseridos na pilha, o topo é atualizado e passa a apontar para o item recem inserido.
 
|	Inicio	| push(p,9);  |	push(p,1);   |  push(p,3);|
|--------------:|------------:|-------------:|-----------:|
|		|	      |		     |   >>	3 |	
|  		|	      |	    >>  1    |		1 |
|  >>NULL       | 	>> 9  |   	9    |	9         |


## Exemplo de remoção

|	Inicio	|    pop(p);  |	   pop(p);   |  pop(p);   |
|--------------:|------------:|-------------:|-----------:|
| >> 3	|   	  |      |    |	
|  1    |  >> 1	  |      |    |
|  9    |     9	  | >> 9 | >> NULL    |


Considerando-se a funcionalidade desses operadores, percebe-se que o último item a ser inserido numa pilha será, necessariamente, o primeiro a ser removido. Essa característica é geralmente nomeada como *last-in, first-out* (último a entrar, primeiro a sair), abreviada como LIFO.

Deste modo, em um dado momento, somente o topo da pilha é observável, ou seja, um item que esteja abaixo do topo somente se tornará visível a partir do momento que todos os seus superiores sejam desempilhados. Essa ideia é facilmente compreendida por analogia a um monte de cartas.

<center>
<img src="https://raw.githubusercontent.com/gajus/swing/master/.README/card-stack.gif" width="150"></center>


# Exercícios

## ex.1: Validação de parentética
>>[página 91, Estruturas de dados usando C, Tenenbaun][1]

Agora que defimos uma pilha e indicamos as operações que podem ser executadas sobre ela, vejamos como podemos usar a pilha na solução de problemas. Examine uma expressão matemática que inclui vários conjuntos de parênteses agrupados. Por exemplo:

	7 - ((X *((X+ Y)/ (J-3)) + Y)/(4-2.5))
 
Queremos garantir que os parênteses estejam corretamente agrupados, ou seja, desejamos verificar se:

1. Existe um número igual de parênteses esquerdos e direitos.
2. Todo parêntese da direita está precedido por um parêntese da esquerda.

{% highlight cpp %}
/*
 Funções auxiliares para identificar o caractere sendo lido.
 
 [!] É necessário implementá-las para que o exemplo funcione.
*/
bool abreEscopo(char c);
bool fechaEscopo(char c);
bool escopoCorreto(char a, char b);

/*
 Recebe uma expressão em forma de string e seu tamanho e verifica sua validade
 quanto aos parênteses abertos e fechados.
 
 Retorna a posição em que o erro foi detectado, ou 'esize +1' caso a expressão
 seja válida. 
*/
int verificaExpressao(const char* expressao, int esize)
{
	Pilha* p = novaPilha();
	
	for (int i = 0; i < esize; ++i)
	{
		char atual = expressao[i];
		if ( abreEscopo(atual) ) 
		{
			Item* abertura = novoItem(atual);
			push(p, abertura);
		} else if ( fechaEscopo(atual) )
		{
			if (p->tamanho == 0)
				return i;
				
			Item* topo = pop(p);
			char ctopo = (char) topo->valor;
			
			if ( !escopoCorreto(ctopo, atual) )
				return i;
		}
	}
	
	if (p->tamanho > 0)
		return esize;

	freeLista(p);
	free(p);
	
	return esize+1;
}

{% endhighlight %}

## ex.2: Validar delimitadores de escopo em expressão
Adapte o código do validador para que funcione com expressões mais complexas, contendo os demais delimitadores
$$(, ), [, ] , \{, \}$$

## ex.3: Verificar palíndromo
(Tanenbaum, página 97)[1]

Escreva um algoritmo para determinar se uma string de caracteres de entrada é da forma:

$$x C y$$

onde $$x,y$$ são strings e $$y$$ é o inverso de $$x$$. O caractere $$C$$ delimita o fim de $$x$$. Somente um caractere da string pode ser lido de cada vez.


{% highlight cpp %}
#include <stack>
#include <assert.h>
#include <stdio.h>

bool isPalindrome(char* p)
{
	std::stack<char> s;
	
	int i = 0;	
	
	while (p[i] != 'C' && p[i] != '\0')
		s.push(p[i++]);
	
	if (p[i] != '\0') i++;
	
	while (p[i] != '\0')
	{	
		if (s.empty() || (s.top() != p[i++]))
			return false;
		s.pop();
	}
	
	if (!s.empty()) return false;
		
	return true;
}

int main (int argc, char** argv)
{
	assert(argc == 2);
	
	char* p = argv[1];
	printf("%s\n", isPalindrome(p) ? "true" : "false");	
}
{% endhighlight %}

## ex.4: Verificar concatenação de palíndromos
[Tanenbaum, página 97]

Escreva um algoritmo para determinar se uma string de caracteres de entrada é da forma:

$$a D b D c D \dots D z$$

onde cada string $$a, b, c,\dots,z$$, é da forma da string definida no exercício anterior, isto é, $$a = xCy$$

## ex.5: Underflow
Que conjunto de critérios é necessário e suficiente para que uma sequência de operações `push` e `pop` sobre uma única pilha (inicialmente vazia) deixe a pilha vazia e não provoque *underflow*?




# Pilha sobre listas ligadas

Considere a implementação dos operadores de manipulação de uma estrutura Pilha em termos de listas simples e duplamente encadeadas.
typedef Lista Pilha;

{% highlight cpp %}
#include "list.h"

Pilha* novaPilha()
{
	return novaLista();
}

Item* pop(Pilha* p)
{
	return removerInicio(p);
}

Item* top(Pilha* p)
{
	return p->inicio;
}

void push(Pilha* p, Item* i)
{
	inserirInicio(p, i);
}
{% endhighlight %}

[1]: http://www.san.uri.br/~ober/arquivos/disciplinas/estruturaII_SI/(ebook)Estruturas%20de%20Dados%20Usando%20C%20(Tenenbaum).pdf
 
