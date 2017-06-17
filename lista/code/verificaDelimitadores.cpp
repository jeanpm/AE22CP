#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <stack>
#include "list.h"


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

char verificaExpressao(const char* expressao, int esize)
{
	std::stack<char> p;
	
	for (int i = 0; i < esize; ++i)
	{
		char atual = expressao[i];
		if ( abreEscopo(atual) ) 
		{
			p.push(atual);
		} else if ( fechaEscopo(atual) )
		{
			if (p.size() == 0) 
			{
				printf("Encontrado '%c' antes de um '%c'\n", 
					atual, obterCorrespondente(atual)
				);
				return i;
			}
				
			char ctopo = p.top();
			
			if ( !escopoCorreto(ctopo, atual) )
			{
				printf("Delimitador '%c' encontrado, mas esperado '%c'\n",
					atual, obterCorrespondente(ctopo));
				return i;
			}
		}
	}
	
	if (!p.empty()) {
		printf("Delimitadores abertos, mas não fechados:\n");
		while (!p.empty())
		{
			printf("%c ", p.top());
			p.pop();
		}
		printf("\n");
		return esize;
	}

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
