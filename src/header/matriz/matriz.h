#if !defined(MATRIZ_H)
#define MATRIZ_H

#include "lista.h"

typedef struct {
    int nLinhas, nColunas;
    LISTA *linha;
    LISTA *coluna;
} MATRIZ;

void criaMatriz(MATRIZ*);
void insereMatriz(MATRIZ*, int, int, double);
int  vaziaMatriz(MATRIZ*);
void leMatriz(MATRIZ*);
void imprimeMatriz(MATRIZ*);
void apagaMatriz(MATRIZ*);
void somaMatriz(MATRIZ*, MATRIZ*, MATRIZ*);
void multiplicaMatriz(MATRIZ*, MATRIZ*, MATRIZ*);

#endif
