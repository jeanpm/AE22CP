
/*
Em geral, toda linguagem de programação possui um tipo de dados inteiro (int), 
que suporta operações básicas como: adição, subtração, multiplicação e divisão. 
Em grande parte dos computadores atuais, no entanto, essas operações são definidas
somente para valores inteiros menores ou iguais a 2.147.483.647 (INT_MAX). Deste modo, 
para aplicações específicas, em que valores maiores que INT_MAX precisem ser 
manipulados, o tipo int se torna inadequado. 

Uma forma alternativa de se representar inteiros maiores que INT_MAX, seria 
utilizar uma estrutura de dados lista, na qual cada item da lista armazene um 
único dígito (0-9) do inteiro em questão.

Utilize listas duplamente encadeadas para implementar a adição de inteiros grandes positivos!

	Lista* add(Lista* A, Lista* B);

Especificações:

Entrada:
	Considere que os inteiros grandes (positivos) estão incialmente armazenados
	em uma string cada.
	
	Ex.: 
		const char* x ="92233720368547758079223372036854775807"
	     	const char* y ="2147483"

	Essas strings devem ser transformadas em listas por uma função.

	Lista* tolist(char* string);

Objetivo:

	Utilizar listas duplamente encadeadas como estrutura de dados para armazenar, manipular	       inteiros grandes. 


Exemplo: 

	92233720368547758079223372036854775807
	+				     1
		
	92233720368547758079223372036854775808

*/
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iostream>

using namespace std;

void tolist(const char* x, list<int>& xlista)
{
	for (int i = 0; x[i] != '\0'; i++)
		xlista.push_back((int) x[i] - '0');
}

/* Adiciona a + b + carry.
   Inicialmente carry é zero.
   Como a some é de dígitos, somente a parte (x % 10) é retornada.
   A parte que sobra vai como carry para outra iteração.
   Exemplo:
   	a = 9;
	b = 9;
	carry = 0;

	sum   = (9 + 9 + 0) % 10; // sum == (18 % 10); sum == 8;
	carry = (9 + 9 + 0) / 10; // sum == (18 / 10); sum == 1;
*/
int addDigit(int a, int b, int* carry)
{
	int sum = (a + b + (*carry)) % 10;
	*carry  = (a + b + (*carry)) / 10;

	return sum;
}


/*

Condições:
	A lista A pode ser maior que a lista B, ou vice-versa;
Funcionamento:
	soma-se o item atual de A, o item atual de B e o carry, enquanto houver elementos em ambas.
Exceção:
	1. Se A > B, os elementos que restarem de A serão somados apenas com o carry.
	2. Se ao fim de A, o carry ainda for > 0, ele é inserido na lista resultante.
*/
list<int> add(list<int>& A, list<int>& B)
{
	// Para identificar a maior lista.
	if (A.size() < B.size()) A.swap(B);
	
	list<int> result;

	int carry = 0;

	list<int>::reverse_iterator acurr = A.rbegin();
	list<int>::reverse_iterator bcurr = B.rbegin();

	/*
	 1.Caso:
	 Soma-se os itens de ambas as listas ao carry, de trás para frente
	 	    ___
	 	999 999
	 	    111

	 2.Caso:
	 Soma-se os itens restantes da lista maior ao carry, é similar a considerar que os itens 
	 inexistentes em B são zero.
	 	___   
	 	999 999
	 	000 111
	*/
	int avalue = 0;
	int bvalue = 0;
	while (acurr != A.rend())
	{	
		avalue = *acurr;
		bvalue = (bcurr != B.rend()) ? *bcurr : 0;
		
		int sum = addDigit(avalue, bvalue, &carry);
		
		result.push_front(sum);
		
		acurr++;
		bcurr = (bcurr != B.rend()) ? bcurr++ : bcurr;
	}
	
	if (carry > 0) result.push_front(carry);

	return result;
}

int main(int argc, char** argv)
{
	assert(argc == 3);

	//const char* x ="99989";
     	//const char* y ="1";
	long al = atol(argv[1]);
	long bl = atol(argv[2]);

	const char* x = argv[1];
     	const char* y = argv[2];

	list<int> A;
	tolist(x, A);
	
	list<int> B;
	tolist(y, B);
	
	
	for (std::list<int>::iterator it=A.begin(); it != A.end(); ++it)
	    std::cout <<  *it;
        std::cout << '\n';
	
		for (std::list<int>::iterator it=B.begin(); it != B.end(); ++it)
	    std::cout << *it;
        std::cout << '\n';
	

	list<int> r = add(A, B);
	
		for (std::list<int>::iterator it=r.begin(); it != r.end(); ++it)
	    std::cout <<  *it;
        std::cout << '\n';
	
	printf("%ld\n", al + bl);


}
