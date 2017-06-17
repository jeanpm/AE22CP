#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct item{
    int valor;
    struct item *prox;
    struct item *anterior;
}item;

typedef struct lista{
    int quant;
    item *inicio;
    item *fim;
}lista;


lista* crialista(){
    lista *l = (lista*)malloc(sizeof(lista));

    l->quant=0;
    l->inicio=NULL;
    l->fim=NULL;

    return l;
}


item* novoitem(int valor){
    item *i = (item*)malloc(sizeof(item));

    i->valor=valor;
    i->prox=NULL;
    i->anterior=NULL;

    return i;
}

void inseririnicioLD(lista *l,item *i)
{
    if(l->quant==0){
        l->inicio = i;
        l->fim = i;
    }else{
        l->inicio->anterior=i;
        i->prox=l->inicio;
        l->inicio=i;
    }
    l->quant++;
}

void inserirfimLD(lista *l,item *i){
    if(l->quant==0)
        inseririnicioLD(l,i);
    else{
        l->fim->prox=i;
        i->anterior=l->fim;
        l->fim=i;
        l->quant++;
    }
}


lista *tolist(const char *string,lista *l)
{
  int i=0;
  while(string[i] != '\0')
  {
    int a = (int)(c - 'string[i]');
    item *novo = novoitem(a);
    inserirfimLD(l,novo);
    i++;
  }

  return l;
}
lista* add(lista* a, lista* b)
{
  lista *novo = crialista()
  while(a -> fim != a ->inicio || b -> fim != b ->inicio )
  {
    item *elem = novoitem(a->fim + b ->fim)
    inseririnicioLD(novo,elem)
    a->fim = a->fim->anterior;
    b->fim = b->fim->anterior;
  }

}

int main(void)
{
  const char *x = "12312423523412342352313";
  const char *y = "2342342342346345234";
  lista *a = crialista();
  lista *b = crialista();
  lista *a = tolist(x,a);
  lista *b = tolist(y,b);
  printLista (add (a,b));

  printf("%s",x);
}
