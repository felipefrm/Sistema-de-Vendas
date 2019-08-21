#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"
#include "lista.h"

void main(void) {

  Produto item;
  Lista *li = cria_lista();
  FILE *arq = fopen("produtos.txt", "r");

  while(!feof(arq)){
    fscanf(arq, "%d %s %d %f", &item.codigo, item.descricao, &item.qtd, &item.preco);
    insere_lista_ordenada(li, item);
  }

  int opcao = -1;
  while (1){

  printf("\nO que deseja fazer?\n\n");

    while (1){

      printf("[1] Realizar Venda\n[2] Adicionar produto ao banco de dados\n"
             "[3] Remover produto do banco de dados\n[4] Alterar quantidade unitaria de produto no estoque\n"
             "[5] Alterar preço de produto no estoque\n[6] Mostrar estoque\n\n[0] Encerrar sessão\n\n>>> ");
      scanf("%d", &opcao);

      if (opcao < 0 || opcao > 6)
        printf("\nOpção inexistente. Digite novamente a opção desejada. ");

      else
        break;
    }

    if (opcao == 0){
      atualizaEstoque(li);
      libera_lista(li);
      return;
    }

    if (opcao == 1){
      realizaVenda(li);
    }

    else if (opcao == 2){
      adicionaProduto(li);
    }

    else if (opcao == 3){
      removeProduto(li);
    }

    else if (opcao == 4){
      alteraInfo(li, 0);
    }

    else if (opcao == 5){
      alteraInfo(li, 1);
    }

    else if (opcao == 6){
      mostrarEstoque(li);
    }
  }
}
