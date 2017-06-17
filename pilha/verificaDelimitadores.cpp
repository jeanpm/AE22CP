#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <stack>

using namespace std;

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
	stack<char> p;
	//Pilha* p = novaPilha();
	
	for (int i = 0; i < esize; ++i)
	{
		char atual = expressao[i];
		if ( abreEscopo(atual) ) 
		{
			p.push(atual);
		} else if ( fechaEscopo(atual) )
		{
			if (p.empty())
				return i;
			
			char ctopo = p.top();
			p.pop();
			
			if ( !escopoCorreto(ctopo, atual) )
				return i;
		}
	}
	
	if (p.size() > 0)
		return esize;
	
	return esize+1;
}
int main(int argc, char** argv)
{
	
	assert(argc == 2);
//	const char* exp = "7 - ((X *((X+ Y)/ (J-3)) + Y)/(4-2.5))";
	printf("%s\n", argv[0]);
	const char* exp = argv[1];
	int esize = strlen(exp);

	printf("%s\t tamanho=%d\n", exp, esize);
	printf("%s\n", 
		verificaExpressao(exp, esize) > esize ? "true":"false"
		);
}
