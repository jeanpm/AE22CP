#include <stdio.h>

#include "lista/list.h"

#define CAPACIDADE 10




int h(long key)
{
	return key % CAPACIDADE;
}


// Tratamento de colisões por encadeamento.
// Elementos com chaves repetidas não são inseridos.
int inserir(Lista* tabela_hash[], long ra)
{
	int hash_ra = h(ra);
	
	Item* curr = tabela_hash[hash_ra]->inicio; 
	
	while (curr != NULL) {
		if (curr->valor == ra) return -1;
		curr = curr->prox;		
	}
	
	inserirInicio(tabela_hash[hash_ra], novoItem(ra));
		
	return 1;
}

int main()
{

	Lista* tabela_hash[CAPACIDADE];
	
	for (int i = 0; i < CAPACIDADE; i++)
	{
		tabela_hash[i] = novaLista();
	}
	

	inserir(tabela_hash, 9999999);
	inserir(tabela_hash, 1111111);
	inserir(tabela_hash, 9999999);
	inserir(tabela_hash, 9999999);
	

	for (int i = 0; i < CAPACIDADE; i++)
	{
		printf("%d:", i);
		printLista(tabela_hash[i]);
	}
}
