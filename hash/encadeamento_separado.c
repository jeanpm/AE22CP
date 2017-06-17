#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef struct _item
{
	long matricula;
	char nome[100];
	struct _item* prox;
	struct _item* ant;
} Aluno;


typedef struct
{
	Aluno* inicio;
	Aluno* fim;
	int tamanho;
} Lista;



Lista* novaLista()
{
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l->inicio = NULL;
	l->fim    = NULL;
	l->tamanho = 0;
	
	return l;
}

Aluno* novoAluno(long matricula, char* nome)
{
	Aluno *i = (Aluno*) malloc(sizeof(Aluno));
	i->matricula = matricula;
	strcpy(i->nome, nome);
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}


// =============================================================================

void inserirInicio(Lista* l, Aluno* novo)
{
	// Se lista vazia
	if (l->inicio == NULL) {
		l->inicio = novo;
		l->fim = l->inicio;
	} else {
		l->inicio->ant = novo;
		novo->prox = l->inicio;
		l->inicio = novo;
	}
	l->tamanho++;
}


void inserirFim(Lista* l, Aluno* novo)
{
	// Se lista vazia
	if (l->fim == NULL) {
		inserirInicio(l, novo);
	} else {
		l->fim->prox = novo;
		novo->ant = l->fim;
		l->fim = novo;
		l->fim->prox = NULL;
	
		l->tamanho++;
	}
}

Aluno* removerInicio(Lista* l)
{
	assert(l->tamanho > 0);
	
	Aluno* removed = NULL;
	
	if (l->tamanho == 1)
	{
		removed = l->inicio;
		l->inicio = NULL;
		l->fim = NULL;
	} else {
		removed = l->inicio;
		l->inicio = removed->prox;
		
		l->inicio->ant = NULL;
	}
	l->tamanho--;
	
	
	return removed;
}

// =============================================================================


void printLista(Lista* l)
{
	if (l->inicio != NULL)
	{
		Aluno* curr = l->inicio;
		while(curr != l->fim)
		{
			fprintf(stdout, "%s, ", curr->nome); 
			curr = curr->prox;
		}
		fprintf(stdout, "%s\n", curr->nome); 
	}
}



// =============================================================================

void freeLista(Lista* l)
{
	while (l->inicio != NULL)
		free(removerInicio(l));
}

void freeTable(Lista** thash, int capacidade)
{
	for (int i = 0; i < capacidade; i++) {
		freeLista(thash[i]);
		free(thash[i]);
	}
	free(thash);
}

long djb2(char nome[100])
{
	long hash = 5381;
	for (int i = 0; nome[i] != '\0'; i++)
		hash = ((hash << 5) + hash) + (int) nome[i];
	return abs(hash);
}	

long sbdm(char nome[100])
{
	long hash = 0;
        int c;

        while ((c = *nome++))
            hash = c + (hash << 6) + (hash << 16) - hash;

        return abs(hash);
}	


long h(long matricula)
{
	return matricula;
}

long h_string(char nome[100])
{
	int c = 0;
	
	int n_len = strlen(nome);
	for (int i = 0; nome[i] != '\0'; i++)
		c = c +  (n_len - i) * (int) nome[i];
	
	return c;
}

int inserir(Lista** thash, int cap, long matricula, char nome[100])
{
	Aluno* tmp = novoAluno(matricula, nome);
	int hvalue;
	
//	hvalue = h(matricula) % cap;
//	hvalue = h_string(nome) % cap;
//	hvalue = djb2(nome) % cap;	
	hvalue = sbdm(nome) % cap;
	
	inserirFim(thash[hvalue], tmp);
	return hvalue;
}

void imprimirTabelaHash(Lista** thash, int capacidade)
{
	double avg_len = 0.0;
	int non_zero = 0;
	for (int i = 0; i < capacidade; i++) {
		printf("%d:", i);
		
		if (thash[i]->tamanho > 0)
		{
			printLista(thash[i]);
			avg_len += thash[i]->tamanho;
			++non_zero;
		} else
			printf("\n");
	}
	printf("avg length = %f\n", avg_len / non_zero);
}


int main()
{
	int capacidade; // Capacidade da tabela hash
	int n; 	// Número de alunos a serem inseridos.
	
	// C++: Leitura de dois inteiros 
	cin >> capacidade >> n;

	// Aloca um vetor de 'Aluno', contendo 'capacidade' posições.
	Lista** thash = (Lista**) malloc(sizeof(Lista*) * capacidade);
	for (int i = 0; i < capacidade; i++) 
		thash[i] = novaLista();

	long matricula;
	char nome[100];
	
	for (int i = 0; i < n; i++) 
	{
		// C++: Leitura de um long e uma string (sem espaços)
		cin >> matricula >> nome;
		
		// Inserir um novo elemento na tabela hash 'thash'
		inserir(thash, capacidade, matricula, nome);
	}
	imprimirTabelaHash(thash, capacidade);
	freeTable(thash, capacidade);
}

