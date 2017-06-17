# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>

typedef struct Item
{
int valor;
struct Item* prox;
struct Item* ant;
}Item;

typedef struct Lista
{
Item* inicio;
Item* fim;
int tamanho;
}Lista;

void ImprimiLista(Lista *L[], int i)
{
    if(L[i]->inicio != NULL)
    {
        Item *A = L[i]->inicio;
        while(A != L[i]->fim)
        {
            printf("%d, ", A->valor);
            A = A->prox;
        }
        printf("%d", A->valor);
    }
}

Item* ponteiroParaPosicao(Lista* l, int pos) // CHECK
{
Item *curr = NULL;
int i;
if(pos < (l->tamanho/2))
    {
        curr = l->inicio;
        for(i=0 ; i < (pos-1) ; i++)
        {
            curr = curr->prox;
        }
    }
    else
    {
        curr = l->fim;
        for(i = l->tamanho ; i>pos ; i--)
        {
            curr = curr->ant;
        }
    }
    return(curr);
}

Item* novoItem(int value) // CHECK
{
Item *i = malloc(sizeof(Item));
i->valor = value;
i->prox  = NULL;
i->ant  = NULL;
return i;
}

void inserirInicio(Lista *l, Item *novo) // CHECK
{
if (l->inicio == NULL)
{
l->inicio = novo;
l->fim = l->inicio;
}
else
{
l->inicio->ant = novo;
novo->prox = l->inicio;
l->inicio = novo;
}
l->tamanho++;
}

void inserirFim(Lista* l, Item* novo) // CHECK
{
if (l->fim == NULL)
    {
inserirInicio(l, novo);
}
else
    {
l->fim->prox = novo;
novo->ant = l->fim;
l->fim = novo;
l->fim->prox = NULL;
l->tamanho++;
}
}

void inserirProximo(Lista* l, Item* atual, Item* novo) // CHECK
{
assert(atual->prox != NULL);
Item* aux;

novo->prox = atual->prox;
aux = atual->prox;
novo->ant = atual;

aux->ant = novo;
atual->prox = novo;

l->tamanho++;
}

void inserirNaPosicao(Lista* l, Item* novo, int pos) // CHECK
{
assert(pos >= 0 && pos <= l->tamanho);
if (pos == 0)
    {
        inserirInicio(l, novo);
    }
else if(pos == l->tamanho)
    {
        inserirFim(l, novo);
    }
else
    {
Item* curr = ponteiroParaPosicao(l, pos);
inserirProximo(l, curr, novo);
}
}

Lista* tolist(const char* String) // CHECK
{
    Lista *L = malloc(sizeof(Lista));
    L->inicio = NULL;
    L->fim = NULL;
    L->tamanho = 0;

    int i, a;
    Item *aux;
    for(i=0 ; String[i] != '\0' ; i++)
    {
        a = (int)(String[i] - '0'); // mudando char para int 
        aux = novoItem(a);
        inserirNaPosicao(L, aux, i);
    }
    return L;
}

Lista* add(Lista *A, Lista *B) // CHECK
{
    Lista *L = malloc(sizeof(Lista));
    L->inicio = NULL;
    L->fim = NULL;
    L->tamanho = 0;
    Item *itemA = A->fim;
    Item *itemB = B->fim;
    Item *aux;
    int quantidade = 0;
    int soma;
    while(itemA != NULL || itemB != NULL) // È || e não && ~~~~~~~~~~~~~~ CHECK
    {
        if(itemA == NULL)
        {
            while(itemB != NULL)
            {
                soma = itemB->valor + quantidade;
                quantidade = 0;
                if(soma >= 10)
                {
                    soma = soma - 10;
                    quantidade = 1;
                }
                aux = novoItem(soma);
                inserirInicio(L, aux);
                itemB = itemB->ant;
            }
            if(quantidade != 0)
            {
                aux = novoItem(quantidade);
                inserirInicio(L, aux);
            }
            return L;
        }
        else if(itemB == NULL)
        {
            while(itemA != NULL)
            {
                soma = itemA->valor + quantidade;
                quantidade = 0;
                if(soma >= 10)
                {
                    soma = soma - 10;
                    quantidade = 1;
                }
                aux = novoItem(soma);
                inserirInicio(L, aux);
                itemA = itemA->ant;
            }
            if(quantidade != 0)
            {
                aux = novoItem(quantidade);
                inserirInicio(L, aux);
            }
            return L;
        }
        soma = itemA->valor + itemB->valor + quantidade;
        quantidade = 0;
        if(soma >= 10)
        {
            soma = soma - 10;
            quantidade = 1;
        }
        aux = novoItem(soma);
        inserirInicio(L, aux);
        itemA = itemA->ant;
        itemB = itemB->ant;
    } // chave do while ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    if(quantidade != 0)
    {
        aux = novoItem(quantidade);
        inserirInicio(L, aux);
    }
    return L;
}

Lista* novaLista() // CHECK
{
Lista *l = (Lista*) malloc(sizeof(Lista));
l->inicio = NULL;
l->fim = NULL;
l->tamanho = 0;
return l;
}

Lista* Mult(Lista *A, Lista *B)
{
    Lista *L = malloc(sizeof(Lista));
    L->inicio = NULL;
    L->fim = NULL;
    L->tamanho = 0;

    Item *aux;
    Item *itemA = A->fim;
    Item *itemB = B->fim;
    int menor, i;

    //B sempre é o menor LISTA
    //A sempre a maior LISTA

    if(A->tamanho <= B->tamanho)
    {
        menor = A->tamanho;
        itemA = B->fim;
        itemB = A->fim;
    }
    else
    {
        menor = B->tamanho;
    }

    Lista *Tabela[menor];

    for(i=0; i<menor ; i++)
    {
        Tabela[i] = novaLista();
    }

    int j=0, multi, quantidade=0, tmp;
    while(itemB != NULL)
    {
        multi = itemA->valor * itemB->valor + quantidade;
        quantidade = 0;
        if(multi >= 10)
        {
            tmp = multi;
            multi = multi % 10;
            quantidade = (tmp - multi) / 10;
        }
        aux = novoItem(multi);
        inserirInicio(Tabela[j], aux);
        if(itemA->ant == NULL)   // PRECISA ARRUMAR ... QUANDO MUDA A LISTA PRECISA ADICIONAR UM 0 NO FINAL //CHECK
        {
            if(quantidade != 0)
            {
                aux = novoItem(quantidade);
                inserirInicio(Tabela[j], aux);
                quantidade = 0;
            }
            itemB = itemB->ant;
            j++;
            if(A->tamanho <= B->tamanho)
            {
                itemA = B->fim;
            }
            else
            {
                itemA = A->fim;
            }
        }
        else
        {
            itemA = itemA->ant;
        }
    }
    int count;
    for(i=1 ; i<menor ; i++)  // GAMBIARRA ?
    {
        count = 0;
        while(count < i)
        {
            aux = novoItem(0);
            inserirFim(Tabela[i], aux);
            count++;
        }
    }

    /*
    for(i=0 ; i<menor ; i++)
    {
        printf("%d: ", i);
        ImprimiLista(Tabela, i);
        printf("\n");
    } */

    if(menor == 1)
    {
        return Tabela[0];
    }
    else if(menor == 2)
    {
        return add(Tabela[0], Tabela[1]);
    }
    else
    {
        for(i=1 ; i<menor ; i++)
        {
            L = add(Tabela[0], Tabela[i]);
            Tabela[0] = L;
        }
        return L;
    }
}

void PrintaLista(Lista *l)
{
    Item *aux = l->inicio;
    while(aux != NULL)
    {
        printf("%d",aux->valor);
        aux = aux->prox;
    }
}

int main(void)
{
    char x[200];
    char y[200];

    scanf("%s", x);
    scanf("%s", y);

    Lista *L1, *L2, *L3;
    L1 = tolist(x);
    L2 = tolist(y);

    //printf("Lista L1: ");
   // PrintaLista(L1);
    //printf("\nLista L2: ");
    //PrintaLista(L2);
    //printf("\n\n\n");
    L3 = Mult(L1, L2);
    PrintaLista(L3);
}

