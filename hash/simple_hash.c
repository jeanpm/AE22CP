#include <stdio.h>

#define CAPACIDADE 10

int h(long key)
{
	return key % CAPACIDADE;
}

int rh(int hash_ra)
{
	return (hash_ra + 1) % CAPACIDADE;
}

// Tratamento de colisões por reespalhamento
// Teste linear ou endereçamento aberto.
int inserir(long tabela_hash[], long ra)
{
	int hash_ra = h(ra);
	
	int n_ocupadas = 0;
	while ( tabela_hash[hash_ra] > 0  && n_ocupadas < CAPACIDADE)
	{
		hash_ra = rh(hash_ra);
		n_ocupadas++;
	}
	
	if (n_ocupadas < CAPACIDADE) {
		tabela_hash[hash_ra] = ra;
		return 1;
	}
		
	return -1;
}

int main()
{

	long tabela_hash[CAPACIDADE];
	
	for (int i = 0; i < CAPACIDADE; i++)
	{
		tabela_hash[i] = -1;
	}
	

	inserir(tabela_hash, 98765434);
	inserir(tabela_hash, 11111114);
	inserir(tabela_hash, 11111124);
	inserir(tabela_hash, 11111134);
	inserir(tabela_hash, 11111154);
	inserir(tabela_hash, 11111164);
	inserir(tabela_hash, 11111914);

	for (int i = 0; i < CAPACIDADE; i++)
	{
		printf("%d: %ld\n", i, tabela_hash[i]);
	}
}
