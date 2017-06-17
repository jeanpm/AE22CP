#include <stdio.h>
#include <stdlib.h>

typedef struct caracter
{
    int num;
    
    // [!] É uma lista de caracteres e não 'numero'
    /*
    struct numero *ant;
    struct numero *prox;
    */
    struct caracter *ant;
    struct caracter *prox;
    
}caracter;

typedef struct
{
    int tamanho;
    caracter *inicio;
    caracter *fim;
}lista;

void iniciarlist(lista *l)
{
    // [!] Converter o ponteiro para o tipo (lista*)
    l= (lista*) malloc(sizeof(lista));
    
    // [!] Você recebeu 'l' e não 'lista'
    /*
    lista->inicio=NULL;
    lista->fim-NULL;
    lista->tamanho=0;
    */
    
    l->inicio=NULL;
    l->fim-NULL;
    l->tamanho=0;
}

//void inserirlist(char c)
// Correções serão precedidas por [!]

// [!] receber a lista como parâmetro
void inserirlist(lista* lista, char c)
{
    // [!] converter o resultado de malloc para (caracter*)
    // caracter *C =malloc(sizeof(caracter));
    caracter *C = (caracter*) malloc(sizeof(caracter));
    
    int a=(int)(c-'0');
    C->num=a;
    C->ant=NULL;
    C->prox=NULL;
    if(lista->tamanho==0)
    {
        lista->fim=C;
        lista->inicio=C;
        lista->tamanho++;
    }
    else
    {
        lista->fim->prox=C;
        C->ant=lista->fim;
        lista->fim=C;
        C->prox=NULL;
        lista->tamanho++;
    }

}

lista* tolist(const char *str)
{
    lista* l;
    int i;
    iniciarlist(l);
    while(str[i]!='\0')
    {
        inserirlist(l, str[i]);
        i++;
    }
}

int main(void)
{
    const char *x="92233720368547758079223372036854775807";
    const char *y="2147483";
    lista* A= tolist(x);
    lista* B= tolist(y);
    
    // [!] Você não definiu printList
    //printlist(A);
    
    while (A->inicio != NULL) {
    	printf("%d,", A->inicio->num);
    	A->inicio = A->inicio->prox;
    }
}
