/*
  Avalia uma expressão em forma infixa. 
  A expressão de entrada não é sintaticamente verificada.
 */

#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <stack>
#include <iostream>

using namespace std;


/*
 Dado um caractere representando um operador qualquer, retorna-se o 
 resultado da operação c(a,b)
*/
double operacao(char c, double a, double b)
{
	switch (c)
	{
	case '+' : return a + b;
	case '-' : return a - b;
	case '*' : return a * b;
	case '/' : return a / b;
	case '^' : return pow(a, b); // Exponenciação
	}
	return a;
}

/**
 Avalia uma expressão pósfixa. Nenhuma verificação sintática é feita 
 na expressão, portanto, expressões inválidas podem levar a
 comportamento inesperado da função.
*/
double evalpos(const char* e)
{
	// Estrutura de dados  pilha da STL de c++
	// Armazena valores `double`
	std::stack<double> p;
	
	int i = 0;
	
	char c = ' ';
	while (e[i] != '\0')
	{
		c = e[i++];
		
		if (isblank(c))
		{// Se o caractere é um espaço ou tab
			continue;
		} else if (isdigit(c)) 
		{// Se o caractere atual é um operando, um dígito (0-9)
			// Insere-se o mesmo na pilha
			p.push((double) c - '0');
		} else 
		{// Se e[i] não é um operando, ele deveria ser um operador. 
			// Neste caso, desempilha-se dois operandos da pilha.
			// Obs: o segundo será o primeiro operando
			double b = p.top(); p.pop();
			double a = p.top(); p.pop();	
			
			// Efetua-se a operação determinada por e[i]
			a = operacao(c, a, b);
			
			// Insere o resultado novamente na pilha.
			p.push(a);
		}
	}
	
	// O resultado estará no topo da pilha, retorne-o.
	double result = p.top(); p.pop();
	return result;
}

int main(int argc, char** argv)
{
	assert(argc == 2);	
	const char* exp = argv[1];	
	string x;
	cin >> x;
	
		cout << "-" << x << "-" << endl;
	const char* e = x.c_str();
	
	printf("%c-%s\n", exp[1], isspace((char)exp[1]) ? "true" : "false"); 	
	printf("%c-%s\n", e[1], isspace((char)e[1]) ? "true" : "false"); 	
	printf("%f\n", evalpos(exp));
}
