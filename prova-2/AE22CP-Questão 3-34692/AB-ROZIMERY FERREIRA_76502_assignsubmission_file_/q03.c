#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct item
{
    int digito;
    struct item *proximo;
    struct item *anterior;
} item;

typedef struct Lista
{
    int qtde;
    struct item *inicio;
    struct item *fim;
} Lista;

Lista* novaLista()
{
    Lista *l =(Lista*)malloc(sizeof(Lista));
    l->qtde = 0;
    l->inicio=NULL;
    l->fim=NULL;

    return l;
}

item* novoItem(int valor)
{
    item *i =(item*)malloc(sizeof(item));
    i->proximo=NULL;
    i->anterior=NULL;
    i->digito= valor;

    return i;
}
item* ponteiroParaPosicao(Lista *l, int pos)
{
    int i;
    item *aux = l->inicio;
    for(i=0; i<pos-1; i++)
    {
        aux=aux->proximo;
    }
    return aux;
}
void inserirInicio(Lista *l, item *i)
{
    if(l->inicio == NULL)
    {
        l->inicio=i;
        l->fim=i;
    }
    else
    {
        l->inicio->anterior=i;
        i->proximo=l->inicio;
        l->inicio;
    }
    l->qtde++;
}

void inserirFim(Lista *l, item *i)
{
    if(l->fim == NULL)
    {
        inserirInicio(l,i);
    }
    else
    {
        l->fim->proximo=i;
        i->anterior=l->fim;
        l->fim=i;
        l->qtde++;
    }
}

void inserirProximo(Lista *l, item *atual, item *i)
{
    i->anterior=atual;
    i->proximo=atual->proximo;
    atual->proximo->anterior=i;
    atual->proximo=i;
    l->qtde++;
}

void inserirNaPosicao(Lista *l, int pos, item *i)
{
    if(pos==0)
    {
        inserirInicio(l,i);
    }
    else if(pos == l->qtde)
    {
        inserirFim(l,i);
    }
    else
    {
        item *atual = ponteiroParaPosicao(l,pos);
        inserirProximo(l, atual, i);
    }
}
void imprimirLista(Lista* l)
{
	item *aux = l->inicio;
	while(aux != NULL)
	{
		printf("%d\t", aux->digito);
		aux = aux->proximo;
	}
	printf("\n");
}
Lista *tolist(char *inteiro)
{
    int i=0, a;
    Lista *l = novaLista();
    while(inteiro[i] != '\0')
    {
        int a = (int)(inteiro[i] - '0');
        inserirNaPosicao(l, i, novoItem(a));
        i++;
    }

    return l;

}
/*
Lista* add(Lista *A, Lista *B)
{
    Lista *r = novaLista();

    r = A + B;

    return r;
}
*/
int main(void)
{
    char (*x)[] = "129084390248092348093183098109381";
    char (*y)[] = "2147483";

    Lista *A = tolist(x);
    Lista *B = tolist(y);
    printf("\n=== Lista A ===\n");
    imprimirLista(A);
    printf("\n=== Lista B ===\n");
    imprimirLista(B);

    printf("\n=== A + B === \n");
  //  imprimirLista(add(A, B));

}

/*letra b

Ao utilziar a lista dinamica temos mais facilidade para transformar a string numérica em uma lista,
tornando a função mais eficaz

*/
