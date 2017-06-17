---
layout: post
title: Tabelas Hash,encadeamento separado
description:  .
author: Jean P. Martins
category: tabelas hash
tags: hash, exercicio
finished: false
---


# Conteúdo
* Do not remove this line (it will not be displayed)
{:toc}

> [Estruturas de dados usando C (Tenenbaum, Sec.7.4, pg. 595 - 603; 620 - 628)][1]

# Contextualização
Uma tabela hash armazena informações que possam ser identificadas por uma chave única. Suponhamos, por exemplo, uma estrutura que armazene informações de um aluno, e o identifique por um número de matrícula.

```cpp
typedef struct
{
	long matricula;
	char nome[100];
	struct _item* prox;
	struct _item* ant;
} Aluno;
```

Caso tivéssemos um número fixo de alunos `N`, as respectivas estruturas podem ser armazenadas em um vetor de tamanho `N`. 

```cpp
const int N = 100;
Aluno turma[N];   // Uma turma tem, neste exemplo, um máximo de 100 alunos
```

Nestas condições, considere a seguinte problema:

  * Dada o vetor `turma` contendo `N` alunos, retorne o aluno de matrícula `M`!
  
  
## A matrícula como índice do vetor turma

Se assumirmos que o campo `matricula` da estrutura `Aluno` é um número $0\dots N-1$; o vetor turma pode ser criado de forma que o `Aluno` de matrícula $i$ ($0 \leq i < N$), esteja na posição $i$ do vetor `turma`.

Neste caso, para retornar o aluno de matrícula $0 \leq M < N$, bastaria retornar o aluno armazenado na respectiva posição.

```cpp
// Caso o índice do vetor equivalha ao número de matrícula.
return turma[M];
```

## A matrícula não pode ser usada como índice do vetor turma

Considere agora, que o campo `matricula` é um número muito maior, no intervalo $0 \leq m < 10^7$. Devido ao valor máximo ser muito grande, não é viável criar um vetor `turma[10 000 000]`, para armazenar apenas $N$ alunos.

### Procurar o aluno de matrícula M em uma list

Caso utilizássemos uma lista para armazenar todos os $N$ alunos, a procura pelo aluno de matrícula `M` envolveria o percurso dessa lista do início ao fim, comparando-se a matrícula dos alunos encontrados com `M` até que o aluno de matrícula `M` seja encontrado. Existiria outra estrutura de dados em que a busca pelo aluno de matrícula `M` possa ser feita de forma mais eficiente? 

### Procurar o aluno de matrícula M em uma tabela hash

Uma alternativa para o armazenamento dos `N` alunos é a utilização de uma tabela hash, em que o número de `matrícula` seria utilizado como chave de acesso ao respectivo aluno.

Veja [Seção 7.4 pgs. (595-598)](http://www.san.uri.br/~ober/arquivos/disciplinas/estruturaII_SI/(ebook)Estruturas%20de%20Dados%20Usando%20C%20(Tenenbaum).pdf)) para uma leitura introdutória à tabelas hash.

Considere que a capacidade ($n$) do vetor utilizado como tabela hash será sempre menor que o número total de alunos, ou seja, $n < N$. 

### Conflitos de espalhamento

Conflitos de espalhamento deverão ser tratados por meio da técnica de *encadeamento separado*[Seção 7.4 pgs. (624-628)](http://www.san.uri.br/~ober/arquivos/disciplinas/estruturaII_SI/(ebook)Estruturas%20de%20Dados%20Usando%20C%20(Tenenbaum).pdf) , a qual consiste em armazenar em uma lista, todos alunos cujos indices caírem sobre o mesmo valor de hash. 

### Estrutura da tabela

A tabela hash será, neste caso, um vetor de listas de alunos, isto é, em cada uma de suas `n` posições, o vetor conterá uma `Lista*` cujos itens armazenarão uma estrutura `Aluno*` cada. Uma tabela hash de capacidade 3, inicialmente, assume a configuração a seguir:

```cpp
	0 -> NULL
	1 -> NULL
	2 -> NULL
```

Após a inserção dos valores a seguir

``` 
1923123123	Jean-Paulo-Martins 
1231231249 	Maria-Josefina
1449989959 	Joaquim-Felix 
```

E uma função de espalhamento, definida para uma tabela de tamanho $n=3$;
```cpp
int h(long mat) {
	return mat % n;
}
```

A tabela hash correspondente teria a seguinte estrutura:

```cpp
Posição | Itens da lista
0       |-> {1923123123, "Jean-Paulo-Martins"} -> NULL
1       |-> {1231231249, "Maria-Josefina"} <-> {1449989959, "Joaquim-Felix"}-> NULL
2       |-> NULL
```

Observe que o conflito de espalhamento foi solucionado armazenando-se todos os alunos com o mesmo hash `h(matricula)` na mesma lista, na posição `h(matricula)` da tabela.


# Objetivos

Implementar uma função que permita a inserção de $N$ alunos em uma tabela hash de capacidade $n$, com $n < N$. Com tratamento de conflitos de espalhamento por *encadeamento separado*.

# Entrada de dados

O primeiro item de entrada é o tamanho máximo, ou capacidade, da tabela hash a ser criada. A leitura desse valor é efetuada da seguinte forma em C++: 

```cpp
int capacidade;
cin >> capacidade;
```

O próximo número de entrada, indicará a quantidade de elementos a serem inseridos na tabela hash.

```cpp
int n; // Número de alunos a serem inseridos
cin >> n;
```

Definidas a capacidade e a quantidade de alunos, os próximos itens a serem lidos descreverão os alunos, que deverão ser amazenados em `struct Aluno`. Portanto, para lermos um aluno.

```cpp
long matricula;
char[100] nome;
cin >> matricula >> nome;
```

Assumindo-se que a função que insere um aluno na tabela hash já esteja implementada, e obedeça o seguinte protótipo de função:

```cpp
int inserir(Lista** thash, long matricula, char* nome);
```
A entrada de dados completa pode ser implementada da seguinte forma:

```cpp
int capacidade;
int n;
cin >> capacidade >> n;

Lista** thash = (Lista**) malloc(capacidade * sizeof(Lista*));

long matricula;
char[100] nome;
for (int i = 0; i < n; i++) {
	cin >> matricula >> nome;
	inserir(thash, matricula, nome);
}
```

## Exemplo de entrada com 3 alunos e capacidade 3

```
3 3 
1923123123	Jean-Paulo-Martins 
1231231249 	Maria-Josefina 
1449989959 	Joaquim-Felix 
```

## Exemplo de saída

Imprimir a tabela hash, cada linha a lista correspondente. No exemplo a seguir:

```cpp
Posição | Itens da lista
0       |-> {1923123123, "Jean-Paulo-Martins"} -> NULL
1       |-> {1231231249, "Maria-Josefina"} <-> {1449989959, "Joaquim-Felix"}-> NULL
2       |-> NULL
```

Deve-se imprimir (a terceira linha está vazia):
```
0:1923123123
1:1231231249, 1449989959
2:
```

[1]: http://www.san.uri.br/~ober/arquivos/disciplinas/estruturaII_SI/(ebook)Estruturas%20de%20Dados%20Usando%20C%20(Tenenbaum).pdf
