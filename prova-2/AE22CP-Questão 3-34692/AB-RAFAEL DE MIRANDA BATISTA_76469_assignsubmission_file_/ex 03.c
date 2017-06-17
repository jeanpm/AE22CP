/*b) EXISTEM VARIAS MOTIVAÇOES PARA USAR A LISTA DINAMICA. A PRIMEIRA SE DEVE AO FATO DE ELA SE ADEQUAR AO NUMERO
DE ITENS QUE VC PRECISA, NAO PRECISANDO DECLARAR UM NUMERO GRANDE DEMAIS E USAR MEMORIA DESNECESSARIA OU DECLARAR
UM NUMERO PEQUENO E FALTAR DEPOIS, SENDO INTERESSANTE E CONVENIENTE PARA O PROGRAMADOR*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Elemento
{
    int vChave;
    char vInfo[30];
    struct Elemento *pProximo;
    struct Elemento *pAnterior;

} tsElemento;

typedef struct
{
    tsElemento *pInicio;
    tsElemento *pFim;
    int vTamanho;

} tsLDDE;

void CriaLDDE(tsLDDE *pLista) // Cria uma lista vazia
{
    pLista->pInicio = NULL;
    pLista->pFim = NULL;
    pLista->vTamanho = 0;
}

void DestroiLDDE(tsLDDE *pLista) // Destroi uma lista
{
    tsElemento *pElemento;

    pElemento = pLista->pInicio;

    do
    {
        pLista->pInicio = pElemento->pProximo;
        free(pElemento);
        pElemento = NULL;
        pElemento = pLista->pInicio;
    } while (pElemento != NULL);
}

tsElemento *CriaElemento(int vChave, char vInfo[]){

	tsElemento *pElemento = malloc(sizeof(tsElemento));

	pElemento->vChave = vChave;
	strcpy(pElemento->vInfo, vInfo);

	return pElemento;
}

void Insere(tsLDDE *pLista, int vPosicao, tsElemento *pNovo)
{
    tsElemento *pAtual;
    int cElementos = 1;

    if ((vPosicao > pLista->vTamanho) || (vPosicao < 0)) // Quando for inserir numa posicao que nao exista (maior que o tamanho da lista ou menor que zero)
    {
        free(pNovo);
        pNovo = NULL;
        printf("\nNao eh possivel inserir nesta posicao.\n");

    } else if ((pLista->vTamanho == 0) || (vPosicao == 0)) // Quando for inserir o/no primeiro elemento
    {
        pNovo->pProximo = pLista->pInicio; //
        pNovo->pAnterior = NULL;

        pLista->pInicio = pNovo;  //

        if (pLista->pInicio->pProximo != NULL)
        {
            pLista->pInicio->pProximo->pAnterior = pNovo;//
        } else
        {
            pLista->pFim = pNovo;
        }

        pLista->vTamanho++;                // funcao InserePrimeiro

    } else if (vPosicao == pLista->vTamanho)
    {
        pNovo->pProximo = NULL;
        pNovo->pAnterior = pLista->pFim;

        pLista->pFim = pNovo;

        if (pLista->pFim->pAnterior != NULL)
        {
            pLista->pFim->pAnterior->pProximo = pNovo;//
        } else
        {
            pLista->pInicio = pNovo;
        }

        pLista->vTamanho++;                // funcao InsereUltimo

    } else
    {
        pAtual = pLista->pInicio;

        while(cElementos < vPosicao)
        {
            pAtual = pAtual->pProximo;
            cElementos++;
        }

        pNovo->pAnterior = pAtual;
        pNovo->pProximo = pAtual->pProximo;

        pAtual->pProximo = pNovo;
        pAtual->pProximo->pAnterior = pNovo;

        pLista->vTamanho++;
    }
}

void Remove(tsLDDE *pLista, int vPosicao)
{
    tsElemento *pAnterior;
    tsElemento *pAtual;
    int cElementos = 1;

    if((vPosicao >= pLista->vTamanho) || (vPosicao < 0) || (pLista->vTamanho == 0)) // Quando for remover uma posicao inexistente (maior que o tamanho da lista ou menor que zero ou lista vazia)
    {
        printf("\nPosicao inexistente, nao eh possivel remover.\n");

    } else if(vPosicao == 0) // Quando for remover o primeiro elemento
    {
        pLista->pInicio = pAnterior->pProximo;
        pLista->pInicio->pAnterior = NULL;
        pAnterior->pProximo->pAnterior = NULL;

        free(pAnterior);
        pAnterior = NULL;
        pLista->vTamanho--;

    } else if (vPosicao == pLista->vTamanho)
    {
        pAnterior = pLista->pFim;
        pAnterior->pAnterior = pLista->pFim->pProximo;
        pLista->pFim = pLista->pFim->pAnterior;
        free(pAnterior);
        pAnterior = NULL;
        pLista->vTamanho--;
    }
    {
        while(cElementos < vPosicao)
        {
            pAnterior = pAnterior->pProximo;
            cElementos++;
        }

        pAtual = pAnterior->pProximo;
        pAnterior->pProximo = pAtual->pProximo;
        free(pAtual);
        pAtual = NULL;
        pLista->vTamanho--;

    }
}

void ImprimeLD(tsLDDE *vLista)
{
    if(vLista->vTamanho == 0)
    {
        printf("\nA lista nao contem nenhum elemento.");
    } else
    {
        tsElemento *pAux;
        //printf("\nInicio - Chave: %d, Info: %s", vLista->pInicio->vChave, vLista->pInicio->vInfo);
        //printf("\nFim    - Chave: %d, Info: %s\n", vLista->pFim->vChave, vLista->pFim->vInfo);
        pAux = vLista->pInicio;
        while(pAux != NULL)
        {
           // printf("%d", pAux->vChave);
            printf("%s", pAux->vInfo);
            pAux = pAux->pProximo;
        }
    }
}

tsLDDE add(tsLDDE *vLista1,tsLDDE *vLista2)
{
    tsLDDE vLista3;

    tsElemento *pAux;
    pAux = vLista1->pFim;

    while(pAux != vLista1->pInicio)
    {
        printf("%d", pAux->vChave);
        pAux = pAux->pAnterior;
    }
}

int main(void)
{
    tsLDDE vLista1, vLista2;
    CriaLDDE(&vLista1);
    CriaLDDE(&vLista2);

    Insere(&vLista1, 0, CriaElemento(1, "4"));
    Insere(&vLista1, 1, CriaElemento(2, "1"));
    Insere(&vLista1, 2, CriaElemento(3, "9"));
    Insere(&vLista1, 3, CriaElemento(4, "4"));
    Insere(&vLista1, 4, CriaElemento(5, "2"));
    Insere(&vLista1, 5, CriaElemento(6, "6"));
    Insere(&vLista1, 6, CriaElemento(7, "2"));
    Insere(&vLista1, 7, CriaElemento(8, "3"));
    Insere(&vLista1, 8, CriaElemento(9, "8"));
    Insere(&vLista1, 9, CriaElemento(10, "0"));

    Insere(&vLista2, 0, CriaElemento(1, "5"));
    Insere(&vLista2, 1, CriaElemento(2, "2"));
    Insere(&vLista2, 2, CriaElemento(3, "1"));
    Insere(&vLista2, 3, CriaElemento(4, "8"));
    Insere(&vLista2, 4, CriaElemento(5, "8"));
    Insere(&vLista2, 5, CriaElemento(6, "8"));
    Insere(&vLista2, 6, CriaElemento(7, "2"));
    Insere(&vLista2, 7, CriaElemento(8, "7"));
    Insere(&vLista2, 8, CriaElemento(9, "3"));

    //printf("\n*******Inserir*******\n");
    printf("\nLista 1:\n\n");
    ImprimeLD(&vLista1);

    printf("\n\nLista 2:\n\n");
    ImprimeLD(&vLista2);

    printf ("\n");

    add(&vLista1, &vLista2);
}
