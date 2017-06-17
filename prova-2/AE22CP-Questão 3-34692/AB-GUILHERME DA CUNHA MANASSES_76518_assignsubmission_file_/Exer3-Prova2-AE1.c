#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct Item
{
	int numero; //numero de 0 a 9
	struct Item* prox;
	struct Item* ant;
}Item;

typedef struct Lista
{
	Item* inicio;
	Item* fim;
	int tamanho;
}Lista;

Lista* novaLista()
{
	Lista* l = malloc(sizeof(Lista));
	l->inicio = NULL;
	l->fim = NULL;
	l->tamanho = 0;

	return l;
}

Item* novoItem(int value)
{
	Item *i = malloc(sizeof(Item));
	i->numero = value;
	i->prox  = NULL;
	i->ant  = NULL;
	return i;
}

void inserirInicio(Lista* l, Item* novo)
{
	// Se lista vazia
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

void inserirFim(Lista* l, Item* novo)
{
	// Se lista vazia
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

void printLista(Lista* l)
{
    if(l->inicio == NULL)
    {
        printf("Essa lista eh vazia...");
    }
	Item* printado = l->inicio;
	while(printado != l->fim)
	{
		printf("%d", printado->numero);
		printado = printado->prox;
	}
	printf("%d", printado->numero);
	printf("\n");
}

Lista* add(Lista* A , Lista* B)
{
    Lista* l = novaLista();
    Item* aux;
    Item* aux2;
    int Soma;
    int resto;

    if(A->tamanho < B->tamanho)
    {
        aux2 = B->fim;
        aux = A->fim;
        while(aux->ant != NULL)
        {
            resto = 0;
            Soma = aux2->numero + aux->numero;
            if(Soma > 9)
            {
                //[!]       
                //resto = Soma - 9;
                Soma = Soma % 10;
                //[!]
                
                //[!]
                //aux2->ant->numero = aux2->numero + resto;
		aux2->ant->numero += 1;
		//[!]
		
		//[!] Deixe o if só atualizar Soma
                //Soma = 0;
                //inserirInicio(l , novoItem(Soma));
            }
            inserirInicio(l , novoItem(Soma));
            aux2 = aux2->ant;
            aux = aux->ant;
        }
    }
    else
    {
        aux2 = A->fim;
        aux = B->fim;
        while(aux->ant != NULL)
        {
            resto = 0;
            Soma = aux2->numero + aux->numero;
            if(Soma > 9)
            {
                //[!]       
                //resto = Soma - 9;
                Soma = Soma % 10;
                //[!]
                
                //[!]
                //aux2->ant->numero = aux2->numero + resto;
		aux2->ant->numero += 1;
		//[!]
		
		//[!] Deixe o if só atualizar Soma
                //Soma = 0;
                //inserirInicio(l , novoItem(Soma));
            }
            inserirInicio(l , novoItem(Soma));
            aux2 = aux2->ant;
            aux = aux->ant;
        }
    }
    return l;
}

Lista* ToList(const char* string)
{
    Lista* l = novaLista();
    int i;

    for(i=0 ; string[i] != '\0' ; i++)
    {
        char c = string[i];
        int a = (int) (c - '0');
        Item* Nx = novoItem(a);
        inserirFim(l , Nx);
    }

    return(l);
}

int main(int argc, char** argv)
{
    const char* x = argv[1];
    const char* y = argv[2];
    Lista* PrimeiroNumero = novaLista();
    Lista* SegundoNumero = novaLista();
    Lista* SomaLista = novaLista();

    PrimeiroNumero = ToList(x);
    printLista(PrimeiroNumero);

    SegundoNumero = ToList(y);
    printLista(SegundoNumero);

    SomaLista = add(PrimeiroNumero , SegundoNumero);
    printLista(SomaLista);

}

/*RESPOSTA DA LETRA B
Uma motivação para se usar as listas dinamicas (especificamente a duplamente encadeada) se da ao fato de que
nessa estrutura temos facil acesso aos conteudos finais , sem precisar percorrer a lista inteira para efetuar
a soma item a item , ou seja , economizando tempo e processamento;
*/
