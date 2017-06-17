#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>


typedef struct item
{
	int valor;
	struct item* prox;
	struct item* ant;
}Item;

typedef struct lista
{
	Item* inicio;
	Item* fim;
	int tamanho;
}Lista;


//------------------------------------------------------------------------------
/*
 Aloca memória para uma estrutura representando uma lista e define valores
 iniciais para os itens da estrutura.
*/
Lista* novaLista();


/*
 Aloca memória para uma estrutura representando um item de lista e define valores
 iniciais para os itens da estrutura.
*/
Item* novoItem(int value);




//------------------------------------------------------------------------------
// Visto na aula do dia 17/05, para listas duplamente encadeadas
//------------------------------------------------------------------------------
void inserirInicio(Lista* l, Item* novo);

// Insere um novo item depois do item atual
void inserirProximo(Lista* l, Item* atual, Item* novo);

void inserirFim(Lista* l, Item* novo);

void inserirNaPosicao(Lista* l, Item* novo, int pos);
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
// Visto na aula do dia 22/05, para listas duplamente encadeadas e circulares
//------------------------------------------------------------------------------
Item* ponteiroParaPosicao(Lista* l, int pos);

Item* removerInicio(Lista* l);

// Remove da lista o item i->prox.
Item* removerProximo(Lista* l, Item* i);

Item* removerFim(Lista* l);
//int removerDaPosicao(Lista *l, int pos);

Item* removerDaPosicao(Lista* l, int pos);



//------------------------------------------------------------------------------
// Exercicios para aula 22/05

/*
 Remove o item i da lista. Diferente da função removerProximo, visto que esta
 recebe o próprio item a ser removido e não o anterior
 OBS: Somente possível em listas duplamente encadeadas

	ex.:> L = (1, 2, 3, 4, 5, 6, 7)
	    > removerItem(L, 4);
	    > L = (1, 2, 3, 5, 6, 7)

*/
void removerItem(Lista* lista, Item* i);




/*
 Reverte a ordem dos itens da lista

	ex.:> L = (1, 2, 3, 4, 5, 6, 7)
	    > reverterLista(L);
	    > L = (7, 6, 5, 4, 3, 2, 1)

*/
void reverterLista(Lista* l);

void printLista(Lista* l);

void freeLista(Lista* l);

Lista* novaLista()
{
	Lista* l = (Lista*) malloc(sizeof(Lista));
	l->inicio = NULL;
	l->fim    = NULL;
	l->tamanho = 0;

	return l;
}

Item* novoItem(int value)
{
	Item *i = (Item*) malloc(sizeof(Item));
	i->valor = value;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}

/*
Item* ponteiroParaPosicao(Lista* l, int pos)
{
	Item* curr = l->inicio;
	for (int i = 0; i < pos - 1; ++i)
		curr = curr->prox;
	return curr;
}
*/

/*
 Versão que verifica o melhor percurso, dentre:
	+ ir do inicio ao fim,
	+ ir do fim ao começo.
*/
Item* ponteiroParaPosicao(Lista* l, int pos)
{
	Item* curr = NULL;

	if (pos < l->tamanho/2) {
		curr = l->inicio;
		int i;
		for ( i = 0; i < pos - 1; ++i)
			curr = curr->prox;
	} else {
		curr = l->fim;
		int i;
		for (i = l->tamanho; i > pos; --i)
			curr = curr->ant;
	}

	return curr;
}

// =============================================================================

void inserirInicio(Lista* l, Item* novo)
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

void inserirProximo(Lista* l, Item* atual, Item* novo)
{
	assert(atual->prox != NULL);

	novo->prox = atual->prox;
	novo->ant = atual;

	atual->prox->ant = novo;
	atual->prox = novo;

	l->tamanho++;
}


void inserirFim(Lista* l, Item* novo)
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



void inserirNaPosicao(Lista* l, Item* novo, int pos)
{
	assert(pos >= 0 && pos <= l->tamanho);

	if (pos == 0)
		inserirInicio(l, novo);
	else if (pos == l->tamanho)
		inserirFim(l, novo);
	else {
		Item* curr = ponteiroParaPosicao(l, pos);
		inserirProximo(l, curr, novo);
	}
}

// =============================================================================


Item* removerInicio(Lista* l)
{
	assert(l->tamanho > 0);

	Item* removed = NULL;

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

Item* removerProximo(Lista* l, Item* anterior)
{
	assert(anterior->prox->prox != NULL);

	Item* removed = anterior->prox;
	removed->prox->ant = anterior;
	anterior->prox = removed->prox;

	l->tamanho--;

	return removed;
}


Item* removerFim(Lista* l)
{
	assert(l->tamanho > 0);

	Item* removed = NULL;

	if (l->tamanho == 1)
	{
		removed = l->fim;
		l->fim = NULL;
		l->inicio = NULL;
	} else {
		removed = l->fim;
		l->fim = removed->ant;

		l->fim->prox = NULL;
	}
	l->tamanho--;

	return removed;
}

void removerItem(Lista* lista, Item* i)
{
	if (i == lista->inicio)
		removerInicio(lista);
	else if (i == lista->fim)
		removerFim(lista);
	else {
		// Se não é início nem fim, o item possui antecessor e sucessor.
		// Então basta atualizar os ponteiros, removendo-o da lista.
		i->ant->prox = i->prox;
		i->prox->ant = i->ant;

		lista->tamanho--;
	}
}

Item*removerDaPosicao(Lista* l, int pos){
    int i;
    Item *remov_elemento,*andamento;
    if(l->tamanho<pos){
        printf("posicao invalido\n");
        return 0;
    }
    if(l->tamanho == 0)
        printf("Lista vazia");
        return ;

    if(pos == 1){ /* remoção do 1° elemento */
        remov_elemento = l->inicio;
        l->inicio = l->inicio->prox;
        if(l->inicio == NULL)
            l->fim = NULL;
        else
            l->inicio->ant == NULL;
    }
    else if(pos == l->tamanho){ /* remoção do último elemento */
        remov_elemento = l->fim;
        l->fim->ant->prox = NULL;
        l->fim = l->fim->ant;printf(("nao casa"));
    }
    else { /* remoção em outro lugar */

        andamento = l->inicio;
        for(i=1;i<pos;++i)
            andamento =andamento->prox;
        remov_elemento =andamento;
        andamento->ant->prox =andamento->prox;
        andamento->prox->ant = andamento->ant;
  }
  free(&remov_elemento->valor);
  free(remov_elemento);
  l->tamanho--;
  return 0;
}

Item* removerDaPosicaovesaoprof(Lista* l, int pos)
{
	assert(pos >= 0 && pos < l->tamanho);

	Item* removed = NULL;


	if (pos == 0) {
		removed = removerInicio(l);
	} else if (pos == l->tamanho-1) {
		removed = removerFim(l);
	} else {
		Item* curr = ponteiroParaPosicao(l, pos);
		removed = removerProximo(l, curr);
	}

	return removed;
}




// =============================================================================


void printLista(Lista* l)
{
	Item* curr = l->inicio;
	while(curr !=l-> fim)
	{
		fprintf(stderr, "%d\t", curr->valor);
		curr = curr->prox;
	}
	fprintf(stderr, "%d\t", curr->valor);
	fprintf(stderr, "\n");
}



void reverterLista(Lista* lista)
{
	assert(lista->fim != NULL);

	Item* curr = lista->fim;

	// Se existe anterior, então a lista tem ao menos dois elementos.
	while(curr != lista->inicio)
	{
		Item* anterior = curr->ant;
		removerItem(lista, anterior);
		inserirFim(lista, anterior);
	}
}
// =============================================================================

void freeLista(Lista* l)
{
	while (l->inicio != NULL)
		free(removerInicio(l));
}



void search_list(Lista *head, int value){
  // printf("Consultando o valor: [%d] na lista.\n", value);

  Item *current = malloc(sizeof(Item));
  current = head->inicio;
  int i = 1;

  // while(current->next != NULL) {
  //   if (current->val == value) {
  //     printf("Encontrado o elemento [%d] na posição [%d].\n", current->val, i);
  //   }
  //   current = current->next;
  //   i++;
  // }

  for (i = 0; i < head->tamanho;i++) {
    if (current->valor == value) {
      printf("Encontrado o elemento [%d] na posição [%d].\n", current->valor, i+1);
    }
    current = current->prox;
  }
}

void inserirListaFim(Lista* A, Lista* B)
{
	assert(B->inicio != NULL);

	if (A->tamanho == 0) {
		A->inicio = B->inicio;
		A->fim = B->fim;
		A->tamanho = B->tamanho;
	} else {
		A->fim->prox = B->inicio;
		B->inicio->ant = A->fim;

		A->fim = B->fim;

		A->tamanho += B->tamanho;
	}
}

void inserirListaAposAtual(Lista* A, Lista* B, Item* atual)
{
	assert(A->inicio != NULL && B->inicio != NULL);

	Item* A2 = atual->prox;

	atual->prox = B->inicio;
	B->inicio->ant = atual;

	B->fim->prox = A2;
	A2->ant = B->fim;

	A->tamanho += B->tamanho;
}

void inserirListaInicio(Lista* A, Lista* B)
{
	assert(B->inicio != NULL);

	if (A->tamanho == 0) {
		A->inicio = B->inicio;
		A->fim = B->fim;
		A->tamanho = B->tamanho;
	} else {
		A->inicio->ant = B->fim;
		B->fim->prox = A->inicio;

		A->inicio = B->inicio;

		A->tamanho += B->tamanho;
	}
}

void inserirListaNaPosicao(Lista* A, Lista* B, int pos)
{
	assert(pos >=0 && pos <= A->tamanho);
	assert(B->inicio != NULL);

	if (pos == 0)
		inserirListaInicio(A, B);
	else if (pos == A->tamanho)
		inserirListaFim(A, B);
	else {
		Item* atual = ponteiroParaPosicao(A, pos);
		inserirListaAposAtual(A, B, atual);
	}
}





int main(int argc, char** argv)
{
	Lista* l = novaLista();

	inserirInicio(l, novoItem(0));
	inserirFim(l, novoItem(1));inserirFim(l, novoItem(5));
    int i;
	//for (i = 2; i < 1000; ++i)
		//inserirNaPosicao(l, novoItem(i), rand() % l->tamanho);
    removerDaPosicao(l,5);
    search_list(l, 0);
    printLista(l);

	//while (l->tamanho > 0)
		//free(removerDaPosicao(l, rand() % l->tamanho));

	freeLista(l);
	free(l);
}



// motivo de usar a LISTA DINAMICA
// menor consumo de memoria
// mais rapido em algum casos
//



