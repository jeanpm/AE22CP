---
layout: post
title: Tabelas Hash, ou tabelas de espalhamento
description:  .
author: Jean P. Martins
category: tabelas hash
tags: hash
finished: false
---


# Conteúdo
* Do not remove this line (it will not be displayed)
{:toc}

> [Estruturas de dados usando C (Tenenbaum, Sec.7.4, pg. 595 - 603; 620 - 628)][1]

# Motivação



**Utilizar como exemplo a lista de alunos e os respectivos números de matrícula**

Descrever de forma intuitiva o tempo de manipulação das estruturas de dados conhecidas até então. A partir daí demonstrar os pontos fracos da armazenagem de informação em listas:
  * Tempo de acesso a elemento internos da lista
  
Operação | Lista | Vetor
Acesso a nós externos | O(1) | O(1)
Acesso a nós internos | O(n/2) | O(1)
  
Comparação com estrutura de vetor (array), em que o índice da informação permite acesso direto à mesma `a[i]` acessa o elemento indicado por `i`.
  * `i` funciona como um índice de acesso à informação
  * Em listas este acesso direto não é fácil de ser implementado. 
  

# Exemplo: Alunos e matrículas como chaves

![Exemplo matriculas]({{site.url}}/assets/examplo-matriculas.png)


# Função de espalhamento

Uma função que transforma uma chave em um índice de acesso é chamada *função de espalhamento* (função hash) $$h$$. Portanto, se $$h$$ é uma função de espalhamento e *key* é uma chave de acesso à informação armazenada, $$h(key)$$ representa o índice no qual um registro com a chave *key* deve ser colocado, ou está armazenado.

# Conflito de espalhamento

Suponha que duas chaves $$k_1, k_2$$ sejam tais que $$h(k_1) = h(k_2)$$. Nesta situação, a tentativa de inserção ou acesso aos registros com chaves $$k_1$$ e $$k_2$$ será feita na mesma posição da tabela, ou seja, dado que a função de espalhamento retornou o mesmo índice de acesso a amobos registros, houve *conflito de espalhamento*.

**Exemplo**

Suponha que quiséssemos inserir um novo número k=0596397 na tabela, usando a função hash

	h(k) = k mod 1000,

Portanto, h(0596397) = 397, no entanto, a posição 397 já está ocupada por outro registro de chave k=4957397, h(4957397) = 397.

Nestas situações, diz-se que houve **conflito de espalhamento**. Ainda sim, o novo número precisa ser adicionado à tabela, onde será inserido? Existem basicamente duas formas de se tratar *conflitos de espalhamento*.

## Reespalhamento por endereçamento aberto

  * Utiliza-se uma **função de espalhamento secundária** sobre a chave de espalhamento do item. 
  * Essa função é aplicada até que uma posição disponível seja obtida. 
  * O método mais simples para a solução de colisões por reespalhamento é chamado **teste linear** ou **endereçamento aberto**, o qual adiciona o registro que gerou o conflito na próxima  posição livre da tabela.
  
```cpp
struct Registro {
	k;     // Chave que identifica este registro, igual a nullkey se vazio
	info;  // Informação armazenada
} tabela[MAXSIZE];

int h(key) {
	return key % MAXSIZE; 
}

// pos = h(key)
int rh(int pos) {
	return (pos + 1) % MAXSIZE; 
}

// Procura um elemento de chave 'key' na tabela, se não encontrado o insere.
int inserir(key, info) {
	int i = h(key);	
	// Se a chave na posição i é diferente de key, então i está ocupada	
	while (tabela[i].k != key && tabela[i].k != nullkey)
		i = rh(i);  // Reespalhamento
	
	if (tabela[i].k == nullkey) {
		tabela[i].k = key;
		tabela[i].info = info;
	}	
	return i;
}
```


Em outras palavras, se a posição $$h(key)$$ da tabela já estiver ocupada por um registro com chave diferente, a função de espalhamento secundária $$rh$$ será aplicada sobre o valor de $$h(key)$$, para encontrar outra posição onde o registro possa ser inserido. Caso a posição $$rh(h(key))$$ também esteja ocupada, um novo reespalhamento é efetuado e avalia-se a posição $$rh(rh(h(key)))$$.

  - **Quanto mais próximo da posição do conflito o novo registro for adicionado, melhor, pois diminui-se o retardo quando o registro for acessado!**
  
  - **Em que situação tem-se um loop infinito no primeior `while`?**

  - **O que pode acontecer se a função se respalhamento fosse rh(i) = (i+2) % MAXSIZE ?**

## Grupamento primário

A probabilidade de certas posições (reespalhadas) serem ocupadas aumenta, à medida que conflitos são tratados.1


## Encadeamento combinado

  * No encadeamento combinado, um **campo adicional** é inserido na tabela
  * Este novo campo guarda a posição do pŕoximo elemento
  * Assume-se também, **uma função pos_livre()**, a qual retorna uma posição não
    ocupada da tabela.
    
{% highlight cpp %}
struct Registro {
	k;     // Chave que identifica este registro, igual a nullkey se vazio
	info;  // Informação armazenada
    int prox;
} tabela[MAXSIZE];
{% endhighlight %}

**Exemplo**

Considere os elementos 14, 29, 34, 28, 42, 39, 84, 38, a função de espalhamento, e a função pos_livre(), descritas a seguir:

{% highlight cpp %}

// Assuma que esta função retorne a primeira posição livre a partir do fim da tabela.
int pos_livre();

int h(key) {
	return key % MAXSIZE; 
}
{% endhighlight %}

![My helpful screenshot]({{site.url}}/assets/encadeamento-combinado.png)

{% highlight cpp %}
int inserir(key, info) {
	int i = h(valor); // hash = 14 % 10 = 4;
	while (tabela[i].k != key && tabela[i].prox >= 0)
		i = tabela[i].prox;
	
	if (tabela[i].key == key)
		return i;

	int j = -1; // Posição a ser inserida
	if (tabela[i].k == nullkey)
		j = i;
	else {
		j  = pos_livre();      // Obtém a próxima posição livre
		t[i].prox = j;	   // Define t[4].next = 8
	}
	t[j].k    = key;
	t[j].info = info;
	return j;
}
{% endhighlight %}


# Encadeamento separado

Tanto o reespalhamento quanto o espalhamento combinado assumem tamanhos fixos de tabela. Portanto, se o número de registros ultrapassar o número de posições da tabela, será impossível inseri-los.

  * **Encadeamento separado** é outro método de tratar colisões
  * Requer a manutenção de uma lista ligada para cada conjunto de chaves que se espalham no mesmo valor.

![Encadeamento separado]({{site.url}}/assets/encadeamento-separado.png)

{% highlight cpp %}
Item* inserir(key, info) {
	int i = h(valor); // hash = 14 % 10 = 4;
	
	Item* ikey = find(tabela[i], key);
	
	// Se não encontrou, insere no fim da lista em tabela[i].
	if (ikey == NULL) { 
		ikey = novoItem(key,info);
		inserirFim(tabela[i], ikey);
	}
	return ikey;
}
{% endhighlight %}

# Organização dos elementos na tabela

Embora o espalhamento permita o quase *acesso direto* aos elementos armazenados (similarmente ao vetor, porém sem desperdício exagerado de memória), os itens numa tablea de espalhamento não são armazenado sequenciamente por chave, o que impede o percurso dos itens nesta ordem.


[1]: http://www.san.uri.br/~ober/arquivos/disciplinas/estruturaII_SI/(ebook)Estruturas%20de%20Dados%20Usando%20C%20(Tenenbaum).pdf
