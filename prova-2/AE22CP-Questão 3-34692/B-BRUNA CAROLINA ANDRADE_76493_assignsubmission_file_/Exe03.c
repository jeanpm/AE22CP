
//B) A lista duplamente encadeada é mais eficiente
// quando se trata de duas listas com valores grandes,
// podendo fazer a manipulação dos valores com mais segurança

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

listaD *DivideMeioLD(listaD *L1)
{
    item *rapido, *lento;
    rapido = L1->inicio;
    lento = rapido;
    while(rapido->prox != NULL)
    {
        rapido = rapido->prox;
        if(rapido->prox != NULL)
        {
            rapido = rapido->prox;
            lento = lento->prox;
        }

    }
    listaD *L2 = crialista(L2);
    //crialista(L2);
    L2->inicio = lento->prox;
    lento->prox = NULL;
    return L2;
}

listaD* mergeLD(listaD *L1,listaD *L2)
{
    item *aux1, *aux2, *tmp;
    listaD *novaLista = crialista(novaLista);
    int posi = 0;

    aux1 = L1->inicio;
    aux2 = L2->inicio;

    while(aux1 != NULL && aux2 != NULL)
    {
        if(aux2->valor < aux1->valor)
        {
            tmp = aux2->prox;
            inserirnaposicaoLD(novaLista,posi,aux2);
            aux2 = tmp;
        }else{
            tmp = aux1->prox;
            inserirnaposicaoLD(novaLista,posi,aux1);
            aux1 = tmp;
        }
        posi++;
    }
    while(aux1 != NULL)
    {
        tmp = aux1->prox;
        inserirnaposicaoLD(novaLista,posi,aux1);
        aux1 = tmp;
        posi++;
    }
    while(aux2 != NULL)
    {
        tmp = aux2->prox;
        inserirnaposicaoLD(novaLista,posi,aux2);
        aux2 = tmp;
        posi++;
    }
    return novaLista;
}

void mergeSortLD(listaD *L1)
{
    listaD *L2;
    if(L1->quant > 1)
    {
        L2 = DivideMeioLD(L1);
        mergeSortLD(L1);
        mergeSortLD(L2);
        L1=mergeLD(L1,L2);
    }
}

void imprimelistaD(listaD *l)
{
  item *aux=l->inicio;

  while(aux!=NULL)
  {
    printf("%d\n",aux->valor);
    aux=aux->prox;
  }
}

int main(void)
{
    listaD *A = crialista();
    item *a = novoitem(1);
    inseririnicioLD(A,a);
    item *b = novoitem(2);
    inserirfimLD(A,b);
    item *c = novoitem(4);
    inserirfimLD(A,c);
    item *d = novoitem(3);
    inserirnaposicaoLD(A,2,d);
    printf("Lista A:\n");
    imprimelistaD(A);

    listaD *B = crialista();
    item *e = novoitem(30);
    item *f = novoitem(24);
    item *g = novoitem(37);
    item *h = novoitem(1);
    item *i = novoitem(36);
    insereordenadoLD(B,e);
    insereordenadoLD(B,f);
    insereordenadoLD(B,g);
    insereordenadoLD(B,h);
    insereordenadoLD(B,i);
    printf("Lista B:\n");
    imprimelistaD(B);

    /*printf("\nLista B no inicio da lista A:\n");
    inserirlistaposicao(A,B,2);
    imprimelistaD(A);*/

    /*printf("\nUsando o mergesort: \n");
    mergeSortLD(A);
    imprimelistaD(A);*/
    /*
    printf("\nREMOVENDO\n");
    item *removido = removenaposicaoLD(l,2);
    //item *removido = removeinicioLD(l);
    //item *removido = removefimLD(l);
    imprimelistaD(l);

    printf("Item removido: %d\n",removido->valor);
    */

}
