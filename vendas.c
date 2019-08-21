#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "vendas.h"

void atualizaEstoque(Lista *li){
  if(li == NULL)
      return;

  FILE* arq = fopen("produtos.txt", "w");

  Elem* no = *li;
  while(no != NULL){
      fprintf(arq, "%d %s %d %.2f\n", no->dados.codigo, no->dados.descricao, no->dados.qtd, no->dados.preco);
      no = no->prox;
  }
  
  fclose(arq);
}

void realizaVenda(Lista *li){

  Produto item;
  int cont = 1, codigo;
  int qtd;
  float dinheiro, valor = 0;

  printf("Adicionando produtos ao carrinho...\n");
  printf("Digite '0' para finalizar a compra.\n\n");

  FILE *cupom = fopen("cupom.txt", "w");
  fprintf(cupom, "         CUPOM FISCAL\n");
  fprintf(cupom, "----------------------------------\n");
  fprintf(cupom, "MERCADINHO E MERCEARIA DOM BOSCO\n");
  fprintf(cupom, "----------------------------------\n");
  fprintf(cupom, "ITEM - CÓDIGO - DESCRICAO -QNT - VALOR UNIT - VALOR ITEM\n");

  while(1) {
    printf("- %dº Produto -\nCódigo: ", cont);
    scanf("%d", &codigo);

    if (codigo == 0)
      break;

    if(consulta_lista_codigo(li, codigo, &item)){


      printf("Item: %s - Preço: R$%.2f - Quantidade: ", item.descricao, item.preco);
      scanf("%d", &qtd);

      if (qtd <= item.qtd){
        valor += qtd * item.preco;
        fprintf(cupom, "%d\t%d\t%s\t%d\tR$.2%f\tR$.2%f\n", cont, item.codigo, item.descricao, item.qtd, item.preco, qtd * item.preco);
        reduzQTD(li, codigo, qtd);
        cont++;
      }

      else
        printf("Quantidade estrapolando a quantidade que há no estoque (%d).\n", item.qtd);
    }
  }


  printf("Valor total: R$ %.2f\n", valor);
  printf("Dinheiro: R$ ");
  scanf("%f", &dinheiro);
  printf("Troco: R$ %f\n", dinheiro - valor);

  fprintf(cupom, "----------------------------------\n");
  fprintf(cupom, "TOTAL R$ %f\n", valor);
  fprintf(cupom, "DINHEIRO R$ %f\n", dinheiro);
  fprintf(cupom, "TROCO R$ %f\n", dinheiro - valor);
  printf("\nImprimindo cupom fiscal...\n");
  sleep(2);


  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  fprintf(cupom, "----------------------------------\n");
  fprintf(cupom, "DATA: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  fprintf(cupom, "----------------------------------\n");



  fclose(cupom);
}

void adicionaProduto(Lista* li){

  int tmp_codigo, tmp_qtd;
  float tmp_preco;
  char tmp_descricao[50];
  Produto item;
  printf("\nCODIGO - DESCRICAO - QUANTIDADE - PRECO\n>>> ");
  scanf("\n%d%s%d%f", &tmp_codigo, tmp_descricao, &tmp_qtd, &tmp_preco);

  if (!consulta_lista_codigo(li, tmp_codigo, &item)){
    item.codigo = tmp_codigo;
    item.qtd = tmp_qtd;
    item.preco = tmp_preco;
    strcpy(item.descricao, tmp_descricao);
    insere_lista_ordenada(li, item);
    printf("\nItem inserido com sucesso no estoque.\n");
  }
  else
    printf("\nJá existe um produto com este código. Operação negada.\n");
}

void removeProduto(Lista* li){

  int codigo;
  mostrarEstoque(li);
  printf("Digite o código do produto que deseja remover: ");
  scanf("%d", &codigo);
  if (remove_lista(li, codigo))
    printf("Item removido do estoque com sucesso.\n");
  else
    printf("O item com o codigo %d não foi encontrado no estoque.\n");

}

int reduzQTD(Lista* li, int codigo, int qtd_retirada){

  if(li == NULL)
      return 0;
  Elem *no = *li;
  while(no != NULL && no->dados.codigo != codigo){
      no = no->prox;
  }
  if(no == NULL)
      return 0;
  else {
      no->dados.qtd -= qtd_retirada;
      return 1;
  }
}

void alteraInfo(Lista *li, int escolha){

  int codigo;
  printf("Digite o código do item que deseja alterar a informação: ");
  scanf("%d", &codigo);

  if(li == NULL)
    printf("Não foi encontrado nenhum item com este código (%d).\n", codigo);
  Elem *no = *li;
  while(no != NULL && no->dados.codigo != codigo){
      no = no->prox;
  }
  if(no == NULL)
      printf("Não foi encontrado nenhum item com este código (%d).\n", codigo);
  else {
    if (escolha == 0){
      int nova_qtd;
      printf("Item: %s - Quantidade atual: %d\n", no->dados.descricao, no->dados.qtd);
      printf("Digite a nova quantidade unitária: ");
      scanf("%d", &nova_qtd);
      no->dados.qtd = nova_qtd;
    }
    else {
      float novo_preco;
      printf("Item: %s - Preço atual: %f\n", no->dados.descricao, no->dados.preco);
      printf("Digite o novo preço unitário: R$ ");
      scanf("%f", &novo_preco);
      no->dados.preco = novo_preco;
    }
  }
}
