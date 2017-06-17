#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct item{
    int valor;
    struct item *prox;
    struct item *anterior;
}item;

typedef struct listaD{
    int quant;
    item *inicio;
    item *fim;
}listaD;


listaD* crialista(){
    listaD *l = (listaD*)malloc(sizeof(listaD));

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

void inseririnicioLD(listaD *l,item *i){
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

void inserirfimLD(listaD *l,item *i){
    if(l->quant==0)
        inseririnicioLD(l,i);
    else{
        l->fim->prox=i;
        i->anterior=l->fim;
        l->fim=i;
        l->quant++;
    }
}

void inserirproximo(listaD *l,item *atual,item *novo){
    novo->prox = atual->prox;
    novo->anterior = atual;
    atual->prox->anterior=novo;
    atual->prox = novo;
    l->quant++;
}

item* ponteiroparaposicao(listaD *l,int posi){
    item *aux;
    int i;
    if(posi>(l->quant/2)){
        aux=l->fim;

        for(i=l->quant-1;i>=posi;i--)
            aux=aux->anterior;
        return aux;
    }
    aux=l->inicio;
    for(i=0;i<posi-1;i++)
        aux=aux->prox;
    return aux;
}

void inserirnaposicaoLD(listaD *l,int posi,item *i){
    if(posi==0)
        inseririnicioLD(l,i);
    else if(posi>=l->quant)
        inserirfimLD(l,i);
    else{
        item *atual = ponteiroparaposicao(l,posi);
        inserirproximo(l,atual,i);
    }
}

void insereordenadoLD(listaD *l,item *temp){

    if(l->inicio == NULL || l->inicio->valor >= temp->valor)
        return inseririnicioLD(l,temp);

    item *aux = l->inicio;

    while(aux->prox!=NULL && aux->prox->valor < temp->valor)
    {
        aux = aux->prox;
    }

    if(aux->prox==NULL)
        return inserirfimLD(l,temp);

    item *novo = novoitem(temp->valor);
    novo->prox = aux->prox;
    aux->prox->anterior = novo;
    novo->anterior=aux;
    aux->prox = novo;
    l->quant++;

}

//lembrar de dar free na main apos usar as funções de remoção
item* removeinicioLD(listaD *l){
    item *aux = l->inicio;
    l->inicio = l->inicio->prox;
    aux->prox->anterior = l->inicio;
    l->quant--;
    return aux;
}

item* removefimLD(listaD *l){
    item *aux = l->fim;
    aux->anterior->prox = aux->prox;
    l->fim=aux->anterior;
    l->quant--;

    return aux;
}

item* removerproximo(listaD *l,item *atual){
    if(atual->prox == NULL)
        removefimLD(l);
    else{
    item *aux = atual->prox;
    aux->prox->anterior = atual;
    atual->prox = aux->prox;
    l->quant--;
    return aux;
    }
}

item* removenaposicaoLD(listaD *l,int posi){
    if(posi==0)
        removeinicioLD(l);
    else if(posi>=l->quant-1)
        removefimLD(l);
    else{
        item *atual = ponteiroparaposicao(l,posi);
        removerproximo(l,atual);
    }
}


//insere uma lista no inicio da outra
void inserirlistainicio(listaD *A,listaD *B){
    //assert(B->inicio != NULL); //termina a execução do programa, não so da função
    if(B->inicio!=NULL){
        if(A->inicio == NULL)
        {
            A->inicio = B->inicio;
            A->fim = B->fim;
            A->quant = B->quant;
        }
        else{
            B->fim->prox = A->inicio;
            A->inicio->anterior = B->fim;
            A->inicio = B->inicio;
            A->quant+=B->quant;
        }
    }
}

void inserirlistafim(listaD *A,listaD *B){
    //assert(B->inicio != NULL);
    if(B->inicio != NULL){
        if(A->inicio == NULL)
            inserirlistainicio(A,B);
        else{
            A->fim->prox = B->inicio;
            B->inicio->anterior = A->fim;
            A->fim = B->fim;
            A->quant+=B->quant;
        }
    }
}


//insere uma lista apos o atual
void inserirlistaproximo(listaD *A,listaD *B,item *atual){
    //assert(A->inicio!=NULL || B->inicio!=NULL);
    if(A->inicio !=NULL && B->inicio!=NULL){
        B->inicio->anterior=atual;
        B->fim->prox=atual->prox;
        atual->prox->anterior=B->fim;
        atual->prox=B->inicio;

        A->quant+=B->quant;
    }
}

//insere uma lista em uma determinada posição da outra lista
void inserirlistaposicao(listaD *A,listaD *B,int posi){
    if(posi==0)
        inserirlistainicio(A,B);
    else if(posi>=A->quant)
        inserirlistafim(A,B);
    else{
        item *atual = ponteiroparaposicao(A,posi);
        inserirlistaproximo(A,B,atual);
    }
}



listaD* tolist(char *string)
{
    listaD *l = crialista();
    int i=0;

    while(string[i]!='\0')
    {
        int a = (int)(string[i]-'0');
        item *novo = novoitem(a);
        inserirfimLD(l,novo);
        i++;
    }
    return l;

}

listaD* add(listaD *A,listaD *B)
{
    item *aux1 = A->fim;
    item *aux2 = B->fim;

    listaD *l3 = crialista();
    item *soma;

    while(aux1!=A->inicio || aux2!=B->inicio)
    {
        if(aux1->valor+aux2->valor>=10)
        {
            soma = novoitem(0);
            inserirfimLD(l3,soma);
        }
        else
            soma = novoitem(aux1->valor+aux2->valor);
    }

    return l3;

}

void imprimelistaD(listaD *l)
{
  item *aux=l->inicio;

  while(aux!=NULL)
  {
    printf("%d",aux->valor);
    aux=aux->prox;
  }
  printf("\n");
}

int main(void)
{
    listaD *A = crialista();
    char *str = "999";
    int i=0;

    A = tolist(str);

    imprimelistaD(A);


    printf("\n");


}
