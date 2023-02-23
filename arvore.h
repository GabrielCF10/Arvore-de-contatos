/*Gabriel Vasconcelos de Arruda. nUSP 12676192
Gabriel Carvalho Fernandes nUSP 13696662
Beatriz Vieira da Silva Andrade nUSP 13692362
Gabriel de Sousa Dalcin. nUSP 13750784
*/

#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRO 0
#define SUCESSO 1


typedef char t_chave[10];
typedef long int t_numero;


typedef struct t_elemento {
	t_chave nome;
	t_numero numero;
} t_elemento;


typedef struct t_no *t_apontador;


typedef struct t_no {
	t_elemento elemento;
	t_apontador esq, dir;
	int altura; 
} t_no;


typedef t_apontador t_avl;


//definições das funções
int criar(t_avl *avl);
void ApagaArvore(t_avl *avl);
int inserir(t_avl *avl, t_elemento elemento);
t_elemento pesquisar(t_avl *avl, t_chave nome);
int remover(t_avl *avl, t_elemento elemento);
int alterar(t_avl *avl, t_elemento elemento);



#endif