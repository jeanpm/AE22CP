---
layout: post
title: Tabelas Hash e o problema da soma, x+y=k
description:  .
author: Jean P. Martins
category: tabelas hash
tags: hash, pair-sum
finished: false
---


# Conteúdo
* Do not remove this line (it will not be displayed)
{:toc}

> [Some illustrative examples on the use of Hash tables][1]

# Descrição

Dado um vetor `A`, de `n` inteiros, e um inteiro `k` qualquer.

```cpp
const int k = 15;
const int n = 1000;
int A[n];
```

Verifique se existem dois valores em `A` cuja soma seja `k`, ou seja, verifique se 

$$\exists\{x,y\}\in A : x+y = k$$.


# Solução sem o uso de tabelas hash

Para cada item `A[i]`, com `i=0,...,n-1`, verifique se o valor que falta até `k` também está no vetor. 

Obs.: Estamos procurando dois valores `x, y` cuja soma seja `k`. Considerando `x=A[i]`, precisamos encontrar `y=k-A[i]` no vetor, chamamos esse valor de complemento da soma. Em resumo `k-A[i]` é o complemento da soma para `A[i]`.

```cpp
bool verificaSoma(int* A, int n, int k)
{
	// Para cada elemento A[i]
	for (int i = 0; i < n; i++)
		// Verifique a existência de outro elemento A[j]=k-A[i]
		// Tal que A[i] + A[j] = k.
		for (int j = i + 1; j < n; j++)
			// Retorne true, caso encontrado
			if (A[i] + A[j] == k)
				return true;
	// Se não encontrado retorne false.
	return false;
}
``` 

# Solução com o uso de tabelas hash

Para cada elemento `A[i]`, verifica-se se o seu complemento (`k-A[i]`) já foi encontrado anteriormente. Caso negativo, adiciona-se o elemento `A[i]` na tabela hash, e continua-se. 

```cpp
int verificaSomaHashTable(int* A, int n, int k)
{
	map<int, bool> m;
	
	// Para cada elemento A[i]
	for (int i = 0; i < n; i++)
	{
		// Verifica se o complemento k - A[i] está na tabela.
		int complemento = abs(k - A[i]);
		if ( m[complemento] == false ) 
			m[ A[i] ] = true;
		else
		// Se verdadeiro, significa que o complemento foi
		// encontrado anteriormente, em uma das posições 
		//           A[0],A[1],...A[i-1].
		// Portanto, existe x, y, tais que x+y = k.
			return true;
	}
	
	return false;
}
```

# Comparação de desempenho

   **Tamanho**|  **Sem hash (s)**|   **Com hash (s)**|
   ----------:|  ------------:|   ------------:
        10 |           0.000000  |          0.000013|
       100|            0.000001|            0.000119|
      1000|            0.000142|            0.000463|
     10000|            0.063888|            0.005301|
    100000|           10.850567|            0.164559|
   1000000|          366.451135|            0.173054|

```cpp
#include <chrono>

// Usa-se chrono de c++ 11, portanto é necessário compilar com -std=c++11
int main()
{
	printf("%10s%20s%20s\n","Tamanho","Sem hash","Com hash");	
	for (int tamanho = 10; tamanho < 10e6; tamanho*=10)
	{	
		int* A = (int*) malloc(sizeof(int) * tamanho);	
		for (int i = 0; i < tamanho; i++) {
			A[i] = rand() % INT_MAX;
		}
	
		int i = rand() % tamanho;
		int j = rand() % tamanho;
	
		A[i] = 5;
		A[j] = 3;
	
		auto start  = chrono::high_resolution_clock::now();
		verificaSoma(A, tamanho, 8);
		auto finish = chrono::high_resolution_clock::now();
		chrono::duration<double> woHash = finish - start;
	
		start = chrono::high_resolution_clock::now();
		verificaSomaHashTable(A, tamanho, 8);
		finish = chrono::high_resolution_clock::now();	
		chrono::duration<double> wHash = finish - start;
		
		printf("%10d%20lf%20lf\n", 
			tamanho, woHash.count(), wHash.count());
		
		free(A);
	}
}
```

[1]: http://dx.doi.org/10.1590/0101-7438.2015.035.02.0423 
