#include <stdio.h>
#include <stdlib.h>

#include "header/matriz/matriz.h"

// CRIACAO
void criaMatriz(MATRIZ *a);
void criaListaColuna(LISTA *l, int nColunas);
void criaListaLinha(LISTA *l, int nLinhas);

// OUTPUT
void imprimeMatriz(MATRIZ *a);
void imprimeLinha(LISTA *l, int i, int colunas);

// INPUT
void leMatriz(MATRIZ *a);
void insereMatriz(MATRIZ *a, int linha, int coluna, double valor);
void insereLinha(PONT p, PONT inserir);
void insereColuna(PONT p, PONT inserir);

// UTILS
int vaziaMatriz(MATRIZ *a);
void apagaMatriz(MATRIZ *a);
void apagaLinha(PONT p);
void apagaColuna(PONT p);

int main(int argc, char *argv[])
{

    MATRIZ a, b, c;

    printf("Primeiro grupo de matrizes\n");
    criaMatriz(&a); leMatriz(&a); imprimeMatriz(&a);
    criaMatriz(&b); leMatriz(&b); imprimeMatriz(&b);

    /*
    printf("Soma\n");
    criaMatriz(&c); somaMatriz(&a, &b, &c); imprimeMatriz(&c);
    printf("Produto\n");
    apagaMatriz(&c); multiplicaMatriz(&a, &b, &c); imprimeMatriz(&c);

    printf("Segundo grupo de matrizes\n");
    apagaMatriz(&a); apagaMatriz(&b); apagaMatriz(&c);
    leMatriz(&a); imprimeMatriz(&a);
    leMatriz(&b); imprimeMatriz(&b);
    printf("Soma\n");
    criaMatriz(&c); somaMatriz(&a, &b, &c); imprimeMatriz(&c);
    printf("Produto\n");
    apagaMatriz(&c); multiplicaMatriz(&a, &b, &c); imprimeMatriz(&c);

    apagaMatriz(&a);
    apagaMatriz(&b);
    apagaMatriz(&c);
    */

    printf("\n\nPress ENTER key to Continue\n");
    getchar();

    return 0;
}

// -------------------------------------------- OPERACOES



// -------------------------------------------- UTILS
int vaziaMatriz(MATRIZ *a) {
    if (a->linha->primeiro == NULL)
        return 1;

    return 0;
}

void apagaMatriz(MATRIZ *a) {
    apagaLinha(a->linha->primeiro);
    apagaColuna(a->coluna->primeiro);
}

void apagaLinha(PONT p) {
    if (p->abaixo != NULL)
        apagaLinha(p->abaixo);

    PONT li = p->direita;
    while (li != NULL) {
        PONT aux = li->direita;
        free(li);
        li = aux;
    }

    p->direita = NULL;
}

void apagaColuna(PONT p) {
    PONT li = p->direita;
    while (li != NULL) {
        li->abaixo = NULL;
        li = li->direita;
    }
}

// -------------------------------------------- INPUTS

void leMatriz(MATRIZ *a) {
    scanf("%d", &(a->nLinhas));
    scanf("%d", &(a->nColunas));
    criaListaLinha(a->linha, a->nLinhas);
    criaListaColuna(a->coluna, a->nColunas);

    int linha, coluna;
    double valor;

    scanf("%d", &linha);
    scanf("%d", &coluna);
    scanf("%lf", &valor);

    while (!(linha < 0 && coluna < 0 && valor < 0.0)) {
        insereMatriz(a, linha, coluna, valor);

        scanf("%d", &linha);
        scanf("%d", &coluna);
        scanf("%lf", &valor);
    }
}

void insereMatriz(MATRIZ *a, int linha, int coluna, double valor) {
    ITEM item;
    item.linha = linha;
    item.coluna = coluna;
    item.valor = valor;

    PONT p = (PONT)malloc(sizeof(CELULA));
    p->item = item;
    p->abaixo = NULL;
    p->direita = NULL;

    insereLinha(a->linha->primeiro, p);
    insereColuna(a->coluna->primeiro, p);
}

void insereLinha(PONT p, PONT inserir) {
    while (p->item.linha < inserir->item.linha)
        p = p->abaixo;

    PONT direita = p->direita;
    if (direita == NULL) {
        p->direita = inserir;
    }
    else if (direita->item.coluna < inserir->item.coluna) {
        insereLinha(direita, inserir);
    }
    else if (direita->item.coluna > inserir->item.coluna) {
        inserir->direita = direita;
        p->direita = inserir;
    }
    else {
        direita->item.valor = inserir->item.valor;
    }
}

void insereColuna(PONT p, PONT inserir) {
    while (p->item.coluna < inserir->item.coluna)
        p = p->direita;

    PONT abaixo = p->abaixo;
    if (abaixo == NULL) {
        p->abaixo = inserir;
    }
    else if (abaixo->item.linha < inserir->item.linha) {
        insereColuna(abaixo, inserir);
    }
    else if (abaixo->item.linha > inserir->item.linha) {
        inserir->abaixo = abaixo;
        p->abaixo = inserir;
    }
    else {
        abaixo->item.valor = inserir->item.valor;
    }
}

// ---------------------------------------------------- CRIACAO

void criaMatriz(MATRIZ *a) {
    a->nLinhas = 0;
    a->nColunas = 0;
    a->linha = (LISTA *)malloc(sizeof(LISTA));
    a->coluna = (LISTA *)malloc(sizeof(LISTA));
    a->linha->primeiro = NULL;
    a->linha->ultimo = NULL;
    a->coluna->primeiro = NULL;
    a->coluna->ultimo = NULL;
}

void criaListaColuna(LISTA *l, int nColunas) {
    PONT anterior = NULL;

    int i;
    for (i = 0; i <= nColunas; i++) {
        ITEM item;
        item.coluna = i;
        item.linha = 0;
        item.valor = 0.0;

        PONT p = (PONT)malloc(sizeof(CELULA));
        p->item = item;
        p->abaixo = NULL;
        p->direita = NULL;

        if (i == 0) l->primeiro = p;
        if (i == nColunas) l->ultimo = p;
        if (anterior != NULL) anterior->direita = p;

        anterior = p;
    }
}

void criaListaLinha(LISTA *l, int nLinhas) {

    PONT anterior = NULL;

    int i;
    for (i = 0; i <= nLinhas; i++) {
        ITEM item;
        item.coluna = 0;
        item.linha = i;
        item.valor = 0.0;

        PONT p = (PONT)malloc(sizeof(CELULA));
        p->item = item;
        p->abaixo = NULL;
        p->direita = NULL;

        if (i == 0) l->primeiro = p;
        if (i == nLinhas) l->ultimo = p;
        if (anterior != NULL) anterior->abaixo = p;

        anterior = p;
    }

}

// -------------------------- OUTPUT

void imprimeMatriz(MATRIZ *a) {
    int i;
    for (i = 1; i <= a->nLinhas; i++) {
        imprimeLinha(a->linha, i, a->nColunas);
    }
}

void imprimeLinha(LISTA *l, int i, int colunas) {
    PONT p = l->primeiro->abaixo;
    while (p->item.linha < i)
        p = p->abaixo;

    p = p->direita;
    printf("\n");
    int j;
    for (j = 1; j <= colunas; j++) {
        if (p && p->item.linha == i && p->item.coluna == j) {
            printf("%f   ", p->item.valor);
            p = p->direita;
        }
        else {
            printf("0.0   ");
        }
    }
}
