#if !defined(LISTA_H)
#define LISTA_H

typedef struct CELULA_TAG *PONT;

typedef struct {
    int linha, coluna;
    double valor;
} ITEM;

typedef struct CELULA_TAG {
    ITEM item;
    PONT direita;
    PONT abaixo;
} CELULA;

typedef struct {
    PONT primeiro, ultimo;
} LISTA;


void criaListaColuna(LISTA*, int);
void criaListaLinha(LISTA*, int);
void insereLinha(PONT, PONT);
void insereColuna(PONT, PONT);
void imprimeLinha(LISTA*, int, int);

#endif
