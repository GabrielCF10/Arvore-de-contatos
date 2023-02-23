/*Gabriel Vasconcelos de Arruda. nUSP 12676192
Gabriel Carvalho Fernandes nUSP 13696662
Beatriz Vieira da Silva Andrade nUSP 13692362
Gabriel de Sousa Dalcin. nUSP 13750784
*/


#include "arvore.h"



static int maior(int a, int b) {
  return a > b ? a : b; // função retorna o maior valor 
} 


static int criarNo(t_avl *avl, t_elemento elemento) {
  *avl = (t_avl)malloc(sizeof(t_no));
  if (*avl == NULL)
    return ERRO;

  (*avl)->esq = NULL;
  (*avl)->dir = NULL;
  (*avl)->elemento = elemento;
  (*avl)->altura = 0;

  return SUCESSO;
}

static int retornarAltura(t_avl *avl) { // ajuda no calculo de balanceamento
  if ((*avl) == NULL)
    return -1;
  else
    return (*avl)->altura;
}

static int checar_fb(t_avl *avl) {  // verifica o balanceamento
  if ((*avl) == NULL)
    return ERRO;
  else {
    if ((*avl)->esq == NULL && (*avl)->dir == NULL) {
      return ERRO;
    } else {
      return retornarAltura(&(*avl)->esq) -
     retornarAltura(&(*avl)->dir);
    }
  }
}


static void rotacaoEsq(t_avl *avl) {
  t_apontador j, B;
// filho à esq da raiz
  j = (*avl)->dir;
  // filho à esq à dir da raiz
  B = j->esq;


  // a sub-arv muda de pai pela antiga raiz
  (*avl)->dir = B;
  // aux passa a ser a raiz
  j->esq = (*avl);

  (*avl)->altura = maior(retornarAltura(&(*avl)->esq), retornarAltura(&(*avl)->dir)) + 1;

  j->altura = maior(retornarAltura(&j->esq), retornarAltura(&j->dir)) + 1;

  // mudar o ponteiro "de cima"
  *avl = j;
}

static void rotacaoDir(t_avl *avl) {

  t_apontador j, B;
  // filho à dir da raiz
  j = (*avl)->esq;
  // filho à dir à esq da raiz
  B = j->dir;

// a sub-arv muda de pai pela antiga raiz
  (*avl)->esq = B;
  // aux passa a ser a raiz
  j->dir = (*avl);

  (*avl)->altura = maior(retornarAltura(&(*avl)->esq), retornarAltura(&(*avl)->dir)) + 1;

  j->altura = maior(retornarAltura(&j->esq), retornarAltura(&j->dir)) + 1;

  // mudar o ponteiro "de cima"
  *avl = j;
}

static void rotacaoEsqDir(t_avl *avl) {
  rotacaoEsq(&(*avl)->esq);

  rotacaoDir(avl);
}

static void rotacaoDirEsq(t_avl *avl) {

  // rotacionar à direita
  rotacaoDir(&(*avl)->dir);
  // rotacionar à esquerda
  rotacaoEsq(avl);
}


static void buscaMaiorEsqETroca(t_avl *raiz, t_avl *subarv) {

  if ((*subarv)->dir == NULL) {

    t_apontador p;

    (*raiz)->elemento = (*subarv)->elemento;

    p = *subarv;
    *subarv = (*subarv)->esq;
    free(p);

  } else {
    buscaMaiorEsqETroca(raiz, &(*subarv)->dir);
  }
}


int criar(t_avl *avl) {
  // inicializa a avl
  *avl = NULL;
  return SUCESSO;
}


void ApagaArvore(t_avl *avl) {

    if((*avl) != NULL){
      ApagaArvore(&(*avl)->esq);
      ApagaArvore(&(*avl)->dir);
    free(*avl);
    }
}


int inserir(t_avl *avl, t_elemento elemento) {

  if ((*avl) == NULL) {
    return criarNo(avl, elemento);
  }
  // considerar chaves primarias
  if (strcmp(elemento.nome, (*avl)->elemento.nome) == 0) {
    printf("Contatinho ja inserido\n");
    return ERRO;
  } else {


    if (strcmp(elemento.nome, (*avl)->elemento.nome) < 0) {
      inserir(&(*avl)->esq, elemento); 
      (*avl)->altura = maior((*avl)->altura, retornarAltura(&(*avl)->esq) + 1);
    }
    if (strcmp(elemento.nome, (*avl)->elemento.nome) > 0) {
        inserir(&(*avl)->dir, elemento); 
      (*avl)->altura = maior((*avl)->altura, retornarAltura(&(*avl)->dir) + 1);
    }
  }

  int bf = checar_fb(avl);

  if (bf > 1) { 

    //2 casos
    int bf_son;
    bf_son = checar_fb(&(*avl)->esq);

    if (bf_son >= 0) {
      rotacaoDir(avl); 
    } else {
      rotacaoEsqDir(avl); 
    }

  } else if (bf < -1) { // dir
    int bf_son;
    bf_son = checar_fb(&(*avl)->dir);
    if (bf_son <= 0) {
      rotacaoEsq(avl);
    } else {
      rotacaoDirEsq(avl); 
    }
  }
  return SUCESSO;
}


t_elemento pesquisar(t_avl *avl, t_chave nome) {
  if ((*avl) == NULL) {
     printf("Contatinho nao encontrado\n");
     t_elemento elemento;
    return elemento;
  }
 
  if (strcmp(nome, (*avl)->elemento.nome) == 0) {
    printf("Contatinho encontrado: telefone %ld \n", (*avl)->elemento.numero);
		return (*avl)->elemento;
   
  } else {
    if (strcmp(nome, (*avl)->elemento.nome) < 0) {
      return pesquisar(&(*avl)->esq, nome);
    } else {
      return pesquisar(&(*avl)->dir, nome);
    }
  }
}


int remover(t_avl *avl, t_elemento elemento) {
 
  // nao achou 
  if ((*avl) == NULL) {
    printf("Operacao invalida: contatinho nao encontrado\n");
		return ERRO;
  }
//busca: esquerda ou direita
  if (strcmp(elemento.nome, (*avl)->elemento.nome) < 0) {
    return remover(&(*avl)->esq, elemento);
    

  } else if (strcmp(elemento.nome, (*avl)->elemento.nome) > 0) {
    return remover(&(*avl)->dir, elemento);
    


  } // Se não é neenhum dos dois casos, então achou a chave
    t_apontador p;
    
    if ((*avl)->esq == NULL && (*avl)->dir == NULL) { // caso 1 (folha)
      p = *avl;
      *avl = NULL;
      free(p);

    } else if ((*avl)->esq == NULL) { // caso 2 (dir)
      p = *avl;
      *avl = (*avl)->dir;
      free(p);

    } else if ((*avl)->dir == NULL) { // caso 3 (esq)
      p = *avl;
      *avl = (*avl)->esq;
      free(p);

    } else { // caso 4: remoção de um nó com dois filhos
      buscaMaiorEsqETroca(avl, &(*avl)->esq);
    }

    int bf = checar_fb(avl);
    // verificar o fator de balanceamento
        if (bf > 1) { // lado esquerdo da avl
        int bf_son; 
        bf_son = checar_fb(&(*avl)->esq); 
        if (bf_son >= 0) {
            rotacaoDir(avl); 
        } else {
            rotacaoEsqDir(avl); 
        }

    } else if (bf < -1) { // lado direito da avl
      int bf_son;
      bf_son = checar_fb(&(*avl)->dir);
      if (bf_son <= 0) {
        rotacaoEsq(avl); 
      } else {
        rotacaoDirEsq(avl); 
      }
    }
  
  return SUCESSO;
}


int alterar(t_avl *avl, t_elemento elemento) {
  //verifica se existe o contato
  if ((*avl) == NULL) {
    printf("Operacao invalida: contatinho nao encontrado\n");
		return ERRO;
  }
  // caso existir
  if (strcmp(elemento.nome,(*avl)->elemento.nome) == 0) {
    (*avl)->elemento.numero = elemento.numero;
    return SUCESSO;
    // se nao busca na recursao
  } else {
        if (strcmp(elemento.nome,(*avl)->elemento.nome) > 0) {
            return alterar(&(*avl)->dir, elemento);
        } else {
            return alterar(&(*avl)->esq, elemento);
        }
    }
}



