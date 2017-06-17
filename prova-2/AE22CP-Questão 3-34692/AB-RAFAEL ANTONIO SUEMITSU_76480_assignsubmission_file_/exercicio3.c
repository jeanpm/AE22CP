#include <stdio.h>
#include <stdlib.h>
typedef struct item{
	int valor;
	struct item *ant;
	struct item *prox;
}item;

typedef struct lista{
	int quant;
	struct item *inicio;
	struct item *fim;
}lista;

lista *novalista(lista *l){
	l=malloc(sizeof(lista));
	l->quant=0;
	l->inicio=NULL;
	l->fim=NULL;
	return l;
}
	
item *novoitem(int valor){
	item *i=malloc(sizeof(item));
	i->prox=NULL;
	i->ant=NULL;
	i->valor=valor;
	return i;
}

void ininicio(lista *l, item *i){
	if(l->quant==0){
		l->inicio=i;
		l->fim=i;
	}	
	else{
		item *aux=l->inicio;
		l->inicio=i;
		l->inicio->ant=NULL;
		l->inicio->prox=aux;
	}
	l->quant++;
}

void inprox(lista *l, item *atual, item *i){
	if(atual->prox!=NULL){
	i->ant=atual;
	i->prox=atual->prox;
	atual->prox=i;
	i->prox->ant=i;
	}
	else{
		i->ant=atual;
		i->prox=NULL;
		atual->prox=i;
	}
	l->quant++;
}	
void transforma(char x[], lista *l){
	int i=0;
	while(x[i]!='\0'){
		int a= (int) (x[i]- '0');
		item *b=novoitem(a);
		item *atual=b;
		
		//[!] Bastaria inserir sempre no fim da lista
		/*
		if(i==0) ininicio(l, b);
		else{
			inprox(l, atual, b);	
		}*/
		//[!] Inserir sempre no incio reverte a ordem
		ininicio(l, b);
		i++;
	}
}
void imprimeL(lista *l){
	item *aux;
	aux=l->inicio;
	for(int i=0; i<l->quant; i++){
		printf("%d\n", aux->valor);
		aux=aux->prox;
	}
}
lista *resultante(lista *a, lista *b){
	lista *x=novalista(x);
	lista *y=novalista(y);
	x=a;
	y=b;
	x->fim->prox=y->inicio;
	y->inicio->ant=x->fim;
	return x;
	
}
int main(){
	lista *num=novalista(num);
	char a[]="123456789";
	transforma(a, num);
	imprimeL(num);

	
}
/*exercicio b
	Pela vantagem de usar somente a memória necessaria, na lista estatica usaria um vetor muito grande pois neste exercicio é esperado uma string muito grande de numeros entao o tamanho inicial do vetor teria que ser muito grande.*/ 
	
