#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *arq = fopen("produtos.txt", "r");
  int codigo, qtd;
  float preco;
  char descricao[50];

  fscanf(arq, "%d %s %d %f", &codigo, descricao, &qtd, &preco);

  printf("Codigo: %d\nDescricao: %s\nQTD: %d\nPreco: %f\n", codigo, descricao, qtd, preco);

  fscanf(arq, "%d %s %d %f", &codigo, descricao, &qtd, &preco);

  printf("Codigo: %d\nDescricao: %s\nQTD: %d\nPreco: %f\n", codigo, descricao, qtd, preco);


  fclose(arq);
}
