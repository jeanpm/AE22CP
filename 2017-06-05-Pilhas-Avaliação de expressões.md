---
layout: post
title: Representações infixa, prefixa e posfixa
description: 
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

# Introdução

Considere a soma de A mais B, numa expressão `A+B`. Neste exemplo, `+` é um operador sendo aplicado aos operandos `A,B`. Este tipo de representação para a expressão de soma dos dois operandos é chamada **infixa**, pois o operador se posiciona entre os operandos.

Considerando-se o posicionamento do operador, no entando, existem duas representações alternativas: **prefixa** e **posfixa**.

  * +AB (prefixa)
  *  AB+ (posfixa)
  
## Input Format
Uma string contendo operandos (dígitos 0-9) e operandos (+,-,/,^,*) na forma posfixa. O operador `exponenciação` é indicado pelo caracter '^', e pode ser implementado pela função:

```
#include <math.h>

// Exponenciação, é representada por AB^ (posfixa) => A^B (infixa) 
double r = pow(A, B);
```

A string pode conter espaços, os quais devem ser ignorados. As seguintes funções podem ser utilizadas para verificar o tipo de um caracter char c.

```
#include <ctype.h>

int isblank(char); // Verdadeiro se o caractere é um espaço ou um tab
int isdigit(char); // Verdadeiro se o caractere é um dígito: 0,1,...,9
```

## Output Format
Um double representando o resultado deve ser impresso:

```
printf("%f", resultado);
```


## Motivação
Como poderá ser notado, notações prefixa e posfixa removem a ambiguidade de uma expressão, desta forma, parenteses não são mais necessários. 

## Notação préfixa
Para compreendermos a utilidade das notações prefixa e posfixa, consideremos as demais operações sobre listas de inteiros grandes:

```
	Lista* mult(Lista* A, Lista* B);
	Lista* div(Lista* A, Lista* B);	
```

Dada uma expressão de exemplo, definida como:

$$ (A + B/C) * D $$

Ela seria implementada pelas funções da seguinte forma:

```
	mult(add(A, div(B,C)),D);
``` 

O que utilizando a notação prefixa em termos de $$+,*,/$$, avalia-se a expressão acima, considerando-se as operações que serão efetuadas em primeiro lugar, ou seja, neste caso: 

  1. divisão $$\rightarrow /BC$$, 
  2. adição $$\rightarrow +A/BC$$, 
  3. multiplicação $$\rightarrow *+A/BCD$$.

$$*+A/BCD$$

Para comprovarmos se essa expressão se equivale à forma infixa, performe as operações assim que dois operandos estiverem disponíveis, iniciando a avaliação da esquerda para a direita.


Ao compararmos as duas representações para a expressão, o que é visivelmente notável?

$$ (A + B/C) * D $$

$$*+A/BCD$$

**RESP: Parenteses se tornam desnecessários!**

## Notação pósfixa

Tanto na notação préfixa quanto na pósfixa, é importante lembrar que os operadores com precedência devem ser avaliados/convertidos primeiro, a não ser que uma possível parentização altere a ordem de precedência.

No exemplo anterior $$(A+B/C) * D$$, a multiplicação é efetuado somente ao final, devido à parentização. A ausência de parênteses, nesse exemplo, nos permitiria outras interpretações: 

  $$ A + ((B/C) * D)$$
  
  $$ A + (B / (C*D))$$
  
A forma pósfixa é a contrapartida da prefixa, em que os operadores são posicionados após os operandos. Retornando ao exemplo original $$(A+B/C)*D$$, temos que a divisão $$B/C$$ deve ser convertida em primeiro lugar:

  $$(A + BC/) * D$$

Em seguida a adição entre parênteses

  $$(ABC/+) * D $$
  
Por fim, a multiplicação

  $$ ABC/+D*$$


## Utilidade

Dada a expressão em forma infixa, elabore um algoritmo que dê o resultado da expressão em apenas uma leitura da string:

	  (A + B/C) * D
	  
Dada a expressão em forma pósfixa, elabore um  algoritmo que dê o resultado da expressão em apenas uma leitura da string:

	  ABC/+D*
	  
## Conversão infixa/pósfixa

| **Forma infixa** | **Forma pósfixa** |
| A+ B | AB+ | 
|A+B-C |AB+C-|
| (A+B) * C | AB+C* |
| A+(B*C) | ABC*+|
|(A+B)*(C-D)| AB+CD-* |


	  
# Avaliação de expressão pósfixa

{% highlight cpp %}
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <stack>
#include <iostream>

using namespace std;


/*
 Dado um caractere representando um operador qualquer, retorna-se o 
 resultado da operação c(a,b)
*/
double operacao(char c, double a, double b)
{
	switch (c)
	{
	case '+' : return a + b;
	case '-' : return a - b;
	case '*' : return a * b;
	case '/' : return a / b;
	case '^' : return pow(a, b); // Exponenciação
	}
	return a;
}

/**
 Avalia uma expressão pósfixa. Nenhuma verificação sintática é feita 
 na expressão, portanto, expressões inválidas podem levar a
 comportamento inesperado da função.
*/
double evalpos(const char* e)
{
	// Estrutura de dados  pilha da STL de c++
	// Armazena valores `double`
	std::stack<double> p;
	
	int i = 0;
	
	char c = ' ';
	while (e[i] != '\0')
	{
		c = e[i++];
		
		if (isblank(c))
		{// Se o caractere é um espaço ou tab
			continue;
		} else if (isdigit(c)) 
		{// Se o caractere atual é um operando, um dígito (0-9)
			// Insere-se o mesmo na pilha
			p.push((double) c - '0');
		} else 
		{// Se e[i] não é um operando, ele deveria ser um operador. 
			// Neste caso, desempilha-se dois operandos da pilha.
			// Obs: o segundo será o primeiro operando
			double b = p.top(); p.pop();
			double a = p.top(); p.pop();	
			
			// Efetua-se a operação determinada por e[i]
			a = operacao(c, a, b);
			
			// Insere o resultado novamente na pilha.
			p.push(a);
		}
	}
	
	// O resultado estará no topo da pilha, retorne-o.
	double result = p.top(); p.pop();
	return result;
}

int main() {
    string expressao;
    cin >> expressao;
    
    printf("%f\n", evalpos(expressao.c_str()));
    
    return 0;
}
{% endhighlight cpp %}
