#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct _Item Item;
typedef struct _Lista Lista;

struct _Item
{
	int valor;
	struct _Item* prox;
	struct _Item* ant;
};


struct _Lista
{
	Item* inicio;
	Item* fim;
	int tamanho;
};

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

void printLista(Lista* l)
{
	if(l->inicio != NULL)
    {
        Item* curr=l->inicio;
        while(curr != l->fim)
        {
            fprintf(stderr, "%d", curr->valor);
            curr= curr->prox;
        }
        fprintf(stderr, "%d\n", curr->valor);
    }
}

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

void freeLista(Lista* l)
{
	while (l->inicio != NULL)
		free(removerInicio(l));
}

Lista* toList(const char* string)
{
    Lista* l = novaLista();
    int i=0;
    while(string[i]!='\0')
    {
        int a = (int) (string[i] - '0');
        Item* b = novoItem(a);
        inserirInicio(l,b);
        i++;
    }
    return l;
}

Lista* add(Lista* A, Lista* B)
{
    Lista* C= novaLista();
    Item* curr = A->fim;
    Item* curr2 = B->fim;
    while(curr != A->inicio || curr2 != B->inicio)
    {
        Item* curra= novoItem(curr->valor+curr2->valor);
        if(curra->valor>9)
        {
            curr->ant->valor=curr->ant->valor+(curra->valor/10);
            curra->valor=curra->valor%10;
        }
        inserirInicio(C,curra);
        curr = curr->ant;
        curr2 = curr2->ant;
    }
    if(curr = A->inicio)
    {
        Item* curra= novoItem(curr->valor+curr2->valor);
        if(curra->valor>9)
        {
            curr2->ant->valor=curr2->ant->valor+(curra->valor/10);
            curra->valor=curra->valor%10;
        }
        inserirInicio(C,curra);
        curr2 = curr2->ant;
        while (curr2 != B->inicio)
        {
            Item* curra= novoItem(curr2->valor);
            if(curra->valor>9)
            {
                curr2->ant->valor=curr2->ant->valor+(curra->valor/10);
                curra->valor=curra->valor%10;
            }
            inserirInicio(C,curra);
            curr2 = curr2->ant;
        }
        inserirInicio(C,B->inicio);
    }
    if(curr2 = B->inicio)
    {
        Item* curra= novoItem(curr->valor+curr2->valor);
        if(curra->valor>9)
        {
            curr2->ant->valor=curr2->ant->valor+(curra->valor/10);
            curra->valor=curra->valor%10;
        }
        inserirInicio(C,curra);
        curr = curr->ant;
        while (curr != A->inicio)
        {
            Item* curra= novoItem(curr->valor);
            if(curra->valor>9)
            {
                curr->ant->valor=curr->ant->valor+(curra->valor/10);
                curra->valor=curra->valor%10;
            }
            inserirInicio(C,curra);
            curr = curr->ant;
        }
        inserirInicio(C,A->inicio);
    }
    return C;
}

int main(void)
{
    const char* x= "9223372036854778079223372036854775807";
    const char* y= "2147483";

    Lista* A = toList(x);
    Lista* B = toList(y);
    
    printLista(A);
    printLista(B);

//    printLista(add(A,B));

    freeLista(A);
    freeLista(B);

    free(A);
    free(B);

    //B) Como não sabemos o espaço que será ocupado na memória pela lista final ou pelos seus items
    //é melhor utilizar uma alocação de memória dinâmica e reduzir os custos do algorítmo.
}
