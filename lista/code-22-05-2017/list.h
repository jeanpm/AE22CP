
typedef struct _Item Item;
typedef struct _Lista Lista;

struct _Item
{
	int valor;
	struct _Item* prox;
	struct _Item* ant;
};


struct _Lista
{
	Item* inicio;
	Item* fim;
	int tamanho;
};

//------------------------------------------------------------------------------
/*
 Aloca memória para uma estrutura representando uma lista e define valores 
 iniciais para os itens da estrutura.
*/
Lista* novaLista();


/*
 Aloca memória para uma estrutura representando um item de lista e define valores 
 iniciais para os itens da estrutura.
*/
Item* novoItem(int value);




//------------------------------------------------------------------------------
// Visto na aula do dia 17/05, para listas duplamente encadeadas
//------------------------------------------------------------------------------
void inserirInicio(Lista* l, Item* novo);

// Insere um novo item depois do item atual 
void inserirProximo(Lista* l, Item* atual, Item* novo);

void inserirFim(Lista* l, Item* novo);

void inserirNaPosicao(Lista* l, Item* novo, int pos);
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
// Visto na aula do dia 22/05, para listas duplamente encadeadas e circulares
//------------------------------------------------------------------------------
Item* ponteiroParaPosicao(Lista* l, int pos);

Item* removerInicio(Lista* l);

// Remove da lista o item i->prox. 
Item* removerProximo(Lista* l, Item* i);

Item* removerFim(Lista* l);

Item* removerDaPosicao(Lista* l, int pos);



//------------------------------------------------------------------------------
// Exercicios para aula 22/05

/* 
 Remove o item i da lista. Diferente da função removerProximo, visto que esta
 recebe o próprio item a ser removido e não o anterior
 OBS: Somente possível em listas duplamente encadeadas
 
	ex.:> L = (1, 2, 3, 4, 5, 6, 7)	
	    > removerItem(L, 4);	     
	    > L = (1, 2, 3, 5, 6, 7)
 
*/
void removerItem(Lista* lista, Item* i);


/*
 Reverte a ordem dos itens da lista

	ex.:> L = (1, 2, 3, 4, 5, 6, 7)	
	    > reverterLista(L);	     
	    > L = (7, 6, 5, 4, 3, 2, 1) 
 
*/
void reverterLista(Lista* l);

void printLista(Lista* l);

void freeLista(Lista* l);

bool verificarPalindromo(Lista* l);





