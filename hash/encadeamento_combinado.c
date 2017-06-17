#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct _item
{
	long matricula;
	int  prox;
	char nome[100];
} Aluno;


void imprimirTabelaHash(Aluno* thash, int capacidade)
{
	for (int i = 0; i < capacidade; i++) {
		printf("%d\t%d\t%ld\t%s\n", i, thash[i].prox, thash[i].matricula, thash[i].nome);
	}
}


int h(long matricula, int capacidade)
{
	return matricula % capacidade;
}


int rh(long h_matricula, int capacidade)
{
	return (h_matricula+1) % capacidade;
}


int pos_livre(Aluno* thash, int cap)
{
	for (int i = cap -1; i >= 0; i--)
		if (thash[i].matricula < 0) return i;
	
	return -1;
}

int inserir(Aluno* thash, int cap, long matricula, char nome[100])
{
	int hvalue = h(matricula, cap);
	int max_iterations = cap;
//	int h = hashNome(nome, cap);
	
	// Se o loop iterar por número de vezes igual à capacidade da tabela
	// Então não foi encontrado espaço vazio.
	
	int j = hvalue;
	
	if (thash[j].matricula >= 0) 
	{
		while (thash[hvalue].prox >= 0 && max_iterations-- > 0)
			hvalue = thash[hvalue].prox;
		j = pos_livre(thash, cap);
		thash[hvalue].prox = j;
	}
	
	
	if (j >= 0 && max_iterations > 0) 
	{
		thash[j].matricula = matricula;
		strcpy(thash[j].nome, nome);
	} 
	
	return j;
}




int main()
{
	int capacidade; // Capacidade da tabela hash
	int n; 	// Número de alunos a serem inseridos.
	
	// C++: Leitura de dois inteiros 
	cin >> capacidade >> n;

	// Aloca um vetor de 'Aluno', contendo 'capacidade' posições.
	Aluno* thash = (Aluno*) malloc(sizeof(Aluno) * capacidade);
	for (int i = 0; i < capacidade; i++) {
		thash[i].matricula = -1;
		thash[i].prox = -1;
	}

	long matricula;
	char nome[100];
	
	for (int i = 0; i < n; i++) 
	{
		// C++: Leitura de um long e uma string (sem espaços)
		cin >> matricula >> nome;
		
		// Inserir um novo elemento na tabela hash 'thash'
		int r = inserir(thash, capacidade, matricula, nome);
		imprimirTabelaHash(thash, capacidade);
		printf("\n\n\n\n\n\n");
		if (r < 0) printf("Capacidade excedida ao inserir %ld\n", matricula);
		
	}
	imprimirTabelaHash(thash, capacidade);
	free(thash);
}

