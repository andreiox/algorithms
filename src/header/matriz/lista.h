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


void cria(LISTA*);
int  insereLinha(LISTA*,PONT);
int  insereColuna(LISTA*,PONT);
void imprimeLinha(LISTA*,int,int);

#endif
