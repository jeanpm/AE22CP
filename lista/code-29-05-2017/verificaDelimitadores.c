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

int verificaExpressao(const char* expressao, int esize)
{
	fprintf(stderr, "int verificaExpressao(const char* expressao, int esize); - Não implementada\n);
	exit(-1);
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
