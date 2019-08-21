#ifndef LISTA
#define LISTA

typedef struct produto {
  int codigo;
  char descricao[50];
  int qtd;
  float preco;
} Produto;

//Definiçao do tipo lista
struct elemento {
    struct produto dados;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct produto al);
int insere_lista_inicio(Lista* li, struct produto al);
int insere_lista_ordenada(Lista* li, struct produto al);
int remove_lista(Lista* li, int codigo);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void mostrarEstoque(Lista* li);
int consulta_lista_codigo(Lista* li, int mat, struct produto *al);
int consulta_lista_pos(Lista* li, int pos, struct produto *al);

#endif
