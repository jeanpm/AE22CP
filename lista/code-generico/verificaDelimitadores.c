#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "list.h"

typedef Lista Pilha;

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

bool abreEscopo(char c)
{
	return c == '(';
}

bool fechaEscopo(char c)
{
	return c == ')';
}

bool escopoCorreto(char a, char b)
{
	return (a == '(') && (b == ')');
}

char obterCorrespondente(char c)
{
	switch (c)
	{
		case ')' : return '(';
		case '(' : return ')';
	}
}

char verificaExpressao(const char* expressao, int esize)
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
			{
				printf("Encontrado '%c' antes de um '%c'\n", 
					atual, obterCorrespondente(atual)
				);
				return i;
			}
				
			Item* topo = pop(p);
			char ctopo = (char) topo->valor;
			
			if ( !escopoCorreto(ctopo, atual) )
			{
				printf("Delimitador '%c' esperado, mas encontrado '%c'\n",
					obterCorrespondente(atual), atual);
				return i;
			}
		}
	}
	
	if (p->tamanho > 0) {
		printf("Delimitadores abertos, mas não fechados:\n");
		while (p->inicio != NULL)
		{
			char topo = (char) pop(p)->valor;
			printf("%c ", topo);
		}
		printf("\n");
		return esize;
	}

	freeLista(p);
	free(p);
	
	return esize+1;
}

int main(int argc, char** argv)
{
	
	assert(argc == 2);
//	const char* exp = "7 - ((X *((X+ Y)/ (J-3)) + Y)/(4-2.5))";
	const char* exp = argv[1];
	int esize = strlen(exp);

	printf("%s\t tamanho=%d\n", exp, esize);
	printf("%s\n", 
		verificaExpressao(exp, esize) > esize ? "true":"false"
		);
}
