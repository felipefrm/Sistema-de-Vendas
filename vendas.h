#ifndef VENDAS
#define VENDAS
#include "lista.h"

void atualizaEstoque(Lista *li);
void realizaVenda(Lista *li);
void adicionaProduto(Lista* li);
void removeProduto(Lista* li);
int reduzQTD(Lista* li, int codigo, int qtd_retirada);
void alteraInfo(Lista *li, int escolha);

#endif
