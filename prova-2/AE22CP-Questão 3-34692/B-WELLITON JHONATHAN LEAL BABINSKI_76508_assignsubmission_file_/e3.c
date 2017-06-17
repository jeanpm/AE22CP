#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct NoTag{
    int num0;
    char num1;
    struct NoTag *prox;
    struct NoTag *ant;
}no;

typedef struct{
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

void removerDepois(LDDE *L, no **q)
{
    no *p;
    p = (*q)->prox;
    (*q)->prox = p->prox;
    free(p);
    p = NULL;
    L->nelem--;
}



void imprimirLista(LDDE *L)
{
    if(L->nelem == 0)
    {
        printf("\nNao ha elementos na lista.");
    }
    else{
        no *p;
        p = L->inicio;
        while(p != NULL)
        {
            printf("Chave: %d", p->chave);
            printf("\tInfo: %s\n", p->info);
            p = p->prox;
        }
    }
}

int main(void)
{
    int res;
    LDDE L, L2;
    definir(&L);
    definir(&L2);
    no *n, *p;
	
	char* z = "98378974389573894758937834" ;
	char* y = "938478934";

	
}
