#include <stdio.h>
#include <stdlib.h>
#include "lista/list.h"

#define CAPACIDADE 10


typedef struct
{
	Lista* tabela_hash[CAPACIDADE];
	long n_elementos;
} Set;


Set* novoSet()
{
	Set* s = (Set*) malloc(sizeof(Set));
	s->n_elementos = 0;
	
	for (int i = 0; i < CAPACIDADE; i++)
		s->tabela_hash[i] = novaLista();
		
	return s;
}



int h(long key)
{
	return key % CAPACIDADE;
}


// Tratamento de colisões por encadeamento.
// Elementos com chaves repetidas não são inseridos.
int inserir(Set* s, long ra)
{
	int hash_ra = h(ra);
	
	Item* curr = s->tabela_hash[hash_ra]->inicio; 
	
	while (curr != NULL) {
		if (curr->valor == ra) return -1;
		curr = curr->prox;		
	}
	
	inserirInicio(s->tabela_hash[hash_ra], novoItem(ra));
	s->n_elementos++;
		
	return 1;
}



Set* uniao(Set* a, Set* b)
{	
	Set* u = novoSet();
	for (int i = 0; i < CAPACIDADE; i++)
	{
		Item* curr = a->tabela_hash[i]->inicio;
		while (curr != NULL) {
			inserir(u, curr->valor);
			curr = curr->prox;
		}
		curr = b->tabela_hash[i]->inicio;
		while (curr != NULL) {
			inserir(u, curr->valor);
			curr = curr->prox;
		}
	}
	return u;
}


void printSet(Set* s)
{
	printf("{");
	for (int i = 0; i < CAPACIDADE; i++)
	{		
		if (s->tabela_hash[i]->inicio != NULL)
		{
			Item* curr = s->tabela_hash[i]->inicio;		
			while(curr != NULL)
			{
				fprintf(stdout, "%ld, ", curr->valor); 
				curr = curr->prox;
			}
		}
	}
	printf("}\n");
}

int main()
{

	Set* s = novoSet();

	inserir(s, 9999999);
	inserir(s, 1111111);
	inserir(s, 9999999);
	inserir(s, 9999999);
	inserir(s, 9385723);
	inserir(s, 9234123);
	
	Set* w = novoSet();

	inserir(w, 9999999);
	inserir(w, 1111111);
	inserir(w, 9999999);
	inserir(w, 9999999);
	
	printSet(s);
	printSet(w);
	
	Set* u = uniao(s,w);
	printSet(u);
	
}
