#include <stack>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


typedef struct
{
	long key;
	int  next;
} Item;


int hash(long key, int size)
{
	return key % size;
}


void printTable(Item* t, int table_size)
{
	for (int j = 0; j < table_size; ++j)
	{
		printf("%ld\t%d\n", t[j].key, t[j].next);
	}
	printf("\n\n");
}

int avail(Item* t)
{
}

int main()
{
	const int table_size = 10;
	
	Item* t = (Item*) malloc(sizeof(Item) * table_size);
	
	stack<int> livre;
	
	for (int j = 0; j < table_size; ++j)
	{
		t[j].key   = -1;
		t[j].next  = -1;
		livre.push(j);
	}
	
	int keys[8] = {14, 29,34, 28, 42,39, 84,38};
	int k = 0;
	
	for (int k = 0; k < 8; ++k) 
	{	
		int i = hash(keys[k], table_size);
	
		// Se já havia alguém na posição i, então houve conflito.	
		if (t[i].key >= 0) 
		{		
			while (t[i].next >= 0) 
				i = t[i].next;
	
			int prox_pos = table_size - 1;
			for (; t[prox_pos].key >= 0; --prox_pos);
			
			t[i].next = prox_pos;
			t[prox_pos].key = keys[k];
		} else {
			t[i].key = keys[k];
		}
		printTable(t, table_size);
	}
	
		
}
