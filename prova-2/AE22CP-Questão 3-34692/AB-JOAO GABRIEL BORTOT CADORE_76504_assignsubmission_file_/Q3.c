#include <stdio.h>
#include <stdlib.h>
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

void printLista(Lista* l)
{
    Item* curr = l->inicio;
    while (curr != l->fim)
    {
        fprintf(stderr, "%d\t", curr->valor);
        curr = curr->prox;
    }
    fprintf(stderr, "%d\t", curr->valor);
    fprintf(stderr, "\n");
}

// Lista *add(Lista* A, Lista* B)
// {
//     assert(B->inicio != NULL);

//     return C;
// }

Lista *tolist(Lista *A, const char* string)
{
    Item *aux = A->inicio;
    Lista B = novaLista();
    int a,i=0;
    while(string[i] != '\0')
    {
        a = (int) (string[i] - '0');
        aux->valor = a;
        inserirFim(B,aux);
        i++;
    }
    return B;
}

int main()
{


    Lista* A = novaLista();
    char str[] = "27836182736187231";

    tolist(A,str);
    printLista(tolist(A,str));

}

// //questao teorica b)
// Nas operaçoes basicas muitas vezes é necessario incrementar ou decrementar
// valores nas unidades anteriores (o numero fica invertido), assim precisa ter o
// ponteiro para os numeros anteriores para emprestar uma unidade ou dar uma unidade;


