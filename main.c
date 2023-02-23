/*Gabriel Vasconcelos de Arruda. nUSP 12676192
Gabriel Carvalho Fernandes nUSP 13696662
Beatriz Vieira da Silva Andrade nUSP 13692362
Gabriel de Sousa Dalcin. nUSP 13750784
*/
#include "arvore.h"


int main() {
  t_avl avl;
  t_elemento elemento;


criar(&avl);

int cont = 0;
char opcao = '1';


  do {
    scanf("%c", &opcao);
      cont++;
      if (opcao == '0') //sai do programa
      {
        ApagaArvore(&avl);
        break;
      }

    if(opcao == 'I'){ //inserir
    if (scanf("%s", elemento.nome) == 1) 
      {
        if (scanf("%ld", &elemento.numero) == 1)
          inserir(&avl, elemento);
      }
    }
    else if(opcao =='P'){ //pesquisar
        if (scanf("%s", elemento.nome) == 1)
        pesquisar(&avl, elemento.nome);
    }
    else if(opcao == 'R'){// remover
      if (scanf("%s", elemento.nome) == 1) 
        remover(&avl, elemento);
    }

    else if(opcao == 'A'){  // alterar
         if (scanf("%s", elemento.nome) == 1) {
        if (scanf("%ld", &elemento.numero) == 1)
          alterar(&avl, elemento);
      }

   }
   
  }while (opcao != '0' || cont < 1000000000);
return 0;
}  

 