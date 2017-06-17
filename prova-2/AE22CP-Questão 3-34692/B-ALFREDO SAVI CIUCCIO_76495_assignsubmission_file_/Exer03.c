#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item
{
	char valor;
	struct Item* prox;
	struct Item* ant;
}Item;

typedef struct Lista
{
	Item* inicio;
	Item* fim;
	int tamanho;
}Lista;

Lista* add(Lista *A, Lista *B)
{

}

Lista* tolist(const char* String)
{
    Lista *L = malloc(sizeof(Lista));
    L->inicio = NULL;
    L->fim = NULL;
    L->tamanho = 0;

    int i;
    for(i=0 ; String[i] != '\0' ; i++)
    {
    }
}

Item* novoItem(char value)
{
	Item *i = (Item*) malloc(sizeof(Item));
	i->valor = value;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}

int main(void)
{
    const char *x = "23789423894732984723893290472";
    const char *y = "392084";

}

// B)
/* Com a lista dinamica vocÊ tem acesso mais facil do ponteiro anterior, pois quando você vai somar 9+9 você precisa passar o numero 1 para o ponteiro anterior. */
