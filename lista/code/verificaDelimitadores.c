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
	switch (c) {
		case '(' : return true;
		case '[' : return true;
		case '{' : return true;
	}
	return false;
}

bool fechaEscopo(char c)
{
	switch (c) {
		case ')' : return true;
		case ']' : return true;
		case '}' : return true;
	}
	return false;
}

bool escopoCorreto(char a, char b)
{
	switch (a) {
		case '(' : return b == ')';
		case '[' : return b == ']';
		case '{' : return b == '}';
	}
	return false;
}

char obterCorrespondente(char c)
{
	switch (c)
	{
		case ')' : return '(';
		case '(' : return ')';
		case '[' : return ']';
		case ']' : return '[';
		case '{' : return '}';
		case '}' : return '{';
	}
	return '\0';
}

int verificaExpressao(const char* expressao, int esize)
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
				return i;
				
			Item* topo = pop(p);
			char ctopo = (char) topo->valor;
			
			if ( !escopoCorreto(ctopo, atual) )
				return i;
		}
	}
	
	if (p->tamanho > 0)
		return esize;

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
