#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

#include <map>
#include <iostream>

using namespace std;

bool verificaSoma(int* A, int n, int k)
{
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (A[i] + A[j] == k)
				return true;
			 
	return false;
}

int verificaSomaHashTable(int* A, int n, int k)
{
	map<int, bool> m;
	
	for (int i = 0; i < n; i++)
	{
		int complemento = abs(k - A[i]);
		if ( m[complemento] == false )
			m[ A[i] ] = true;
		else
			return true;
	}
	
	return false;
}

#include <chrono>

// Usa-se chrono de c++ 11, portanto é necessário compilar com -std=c++11
int main()
{

	printf("%10s%20s%20s\n","Tamanho","Sem hash","Com hash");
	
	for (int tamanho = 10; tamanho < 10e6; tamanho*=10)
	{	
		int* A = (int*) malloc(sizeof(int) * tamanho);
	
		for (int i = 0; i < tamanho; i++)
		{
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
