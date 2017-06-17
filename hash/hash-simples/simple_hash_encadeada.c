#include <stdio.h>

#include "lista/list.h"

#define SIZE 10

int h(long key)
{
	return key % SIZE;
}

int rh(int hash_value)
{
	return (hash_value + 1) % SIZE;
}


void inserir(Lista* hashTable[], long key)
{

	int hash_value = h(key);

	Item* i = novoItem(key);
	inserirFim(hashTable[hash_value], i);
}

int main()
{
	
	Lista* hashTable[SIZE];
	for (int i = 0; i < SIZE; i++)
		hashTable[i] = novaLista();
	
	
	inserir(hashTable, 9999999);
	inserir(hashTable, 1000000);
	inserir(hashTable, 9000000);
	inserir(hashTable, 1231231);
	
	for (int i = 0; i < SIZE; i++) {
		printf("%d: ", i);
		printLista(hashTable[i]);
	}
//		printf("%d: %ld\n", i, hashTable[i]);
	
}

