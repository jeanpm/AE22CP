#include <stdio.h>

#define SIZE 10

int h(long key)
{
	return key % SIZE;
}

int rh(int hash_value)
{
	return (hash_value + 1) % SIZE;
}


void inserir(long hashTable[], long key)
{

	int hash_value = h(key);
	
	while (hashTable[hash_value] > 0)
		hash_value = rh(hash_value);
			
	hashTable[hash_value] = key;
}

int main()
{
	
	char* hashTable[SIZE];
	for (int i = 0; i < SIZE; i++)
		hashTable[i] = -1;
	
	
	inserir(hashTable, 9999999999);
	inserir(hashTable, 1000000);
	inserir(hashTable, 9000000);
	inserir(hashTable, 123123211);
	
	for (int i = 0; i < SIZE; i++)
		printf("%d: %ld\n", i, hashTable[i]);
	
}

