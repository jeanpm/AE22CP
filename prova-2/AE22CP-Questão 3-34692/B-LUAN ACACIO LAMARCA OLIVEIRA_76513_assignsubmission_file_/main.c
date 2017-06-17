//
//  main.c
//  exe3
//
//  Created by Luan Lamarca on 31/05/17.
//  Copyright © 2017 Luan Lamarca. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct NoTag
{
    int chave;
    char info[30];
    struct NoTag *prox;
    struct NoTag *ant;
}no;

typedef struct
{
    no *inicio;
    no *fim;
    int nelem;
}LDDE;

void definir(LDDE *L)
{
    L->inicio = NULL;
    L->fim = NULL;
    L->nelem = 0;
}
void inserirPrimeiro(LDDE *L, no *novo)
{
    novo->prox = L->inicio;
    novo->ant = NULL;
    L->inicio = novo;
    L->fim = novo;
    L->nelem++;
}
void inserirPosicao(LDDE *L, int posicao, no *elemento)
{
    no *p;
    int cont = 1;
    p = L->inicio;
    if(L->nelem == 0 || posicao==1)
    {
        inserirPrimeiro(L, elemento);
    }
    else if(posicao > (L->nelem + 1))
    {
        printf("\nNao e possivel incluir nesta posicao.\n");
    }
    else
    {
        while(cont != posicao - 1)
        {
            cont++;
            p = p->prox;
            if(cont == 1)
            {
                p = L->inicio;
            }
        }
        if(cont == posicao - 1)
        {
            if(posicao == L->nelem + 1)
            {
                elemento->prox = NULL;
                elemento->ant = p;
                p->prox = elemento;
                L->fim = elemento;
                L->nelem++;
            }
            else
            {
                elemento->prox = p->prox;
                elemento->ant = p;
                p->prox = elemento;
                L->nelem++;
            }
        }
        
    }
    
}
LDDE* tolist(const char* string)
{
    int i;
    for(i=0;i!=strcmp(<#const char *__s1#>, <#const char *__s2#>);i++)
    {
        
    }
}


int main(void)
{
    const char* x="9223372";
    const char* y="2147483";
    printf("\n");
    return 0;
}
