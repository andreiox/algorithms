#include <stdio.h>
#include <stdlib.h>

#include "header/matriz/matriz.h"

/*
    ALUNOS

    Andre Macedo
    Mateus Coelho
    Rafael Rabelo

    Turma 4NA
*/

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
void copiaMatriz(MATRIZ *a, MATRIZ *b);
void apagaLinha(PONT p);
void apagaColuna(PONT p);
void removeCoordenada(MATRIZ *a, int linha, int coluna);
double getValorDaCoordenada(MATRIZ *a, int linha, int coluna);

// OPERACOES
void somaMatriz(MATRIZ *a, MATRIZ *b, MATRIZ *c);
void multiplicaMatriz(MATRIZ *a, MATRIZ *b, MATRIZ *c);

int main(int argc, char *argv[])
{
    MATRIZ a, b, c;

    printf("Primeiro grupo de matrizes\n");
    criaMatriz(&a); leMatriz(&a); imprimeMatriz(&a);
    criaMatriz(&b); leMatriz(&b); imprimeMatriz(&b);
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

    int i;
    scanf("%d", &i);

    return 0;
}

// -------------------------------------------- OPERACOES
void multiplicaMatriz(MATRIZ *a, MATRIZ *b, MATRIZ *c) {

    if (a->nColunas != b->nLinhas || a->nLinhas != b->nColunas) {
        printf("Nao e possivel fazer a soma porque as dimencoes nao atendem aos requisitos da multiplicacao.\n");
        return;
    }

    // Seta dimencoes da matriz resultado
    c->nColunas = b->nColunas;
    c->nLinhas = a->nLinhas;
    // Cria as listas linha e coluna
    criaListaLinha(c->linha, c->nLinhas);
    criaListaColuna(c->coluna, c->nColunas);

    // Pega a primeira posicao da lista encadeada de linhas
    PONT p = a->linha->primeiro->abaixo;
    // Enquanto houver linhas
    while (p != NULL) {
        int coluna = 1;
        // Agora vou percorrer as posicoes da matriz 
        while (coluna <= c->nColunas) {
            // variavel com o primeiro valor da linha
            PONT li = p->direita;
            double valor = 0;
            // percorre a linha inteira fazendo o calculo e adicionando ao valor total
            while (li != NULL) {
                double aux = li->item.valor * getValorDaCoordenada(b, li->item.coluna, coluna);
                valor += aux;
                li = li->direita;
            }

            // se o valor for diferente de 0 eu devo adicionar na matriz
            if (valor != 0) {
                insereMatriz(c, p->item.linha, coluna, valor);
            }
            coluna++;
        }

        p = p->abaixo;
    }
}

void somaMatriz(MATRIZ *a, MATRIZ *b, MATRIZ *c) {
    if (a->nColunas != b->nColunas || a->nLinhas != b->nLinhas) {
        printf("Nao e possivel fazer a soma porque as dimencoes nao atendem aos requisitos da soma.\n");
        return;
    }

    // copio todos os valores da matriz a para a matriz resultado
    copiaMatriz(a, c);

    // Pega a primeira posicao da lista encadeada de linhas
    PONT p = b->linha->primeiro->abaixo;
    while (p != NULL) {
        PONT li = p->direita;
        // percorro os elementos da linha p->item.linha realizando a soma e inserindo na matriz caso o valor seja diferente de 0 e removendo da matriz caso seja 0.
        while (li != NULL) {
            double valor = getValorDaCoordenada(c, li->item.linha, li->item.coluna);
            if ((valor + li->item.valor) != 0)
                insereMatriz(c, li->item.linha, li->item.coluna, (valor + li->item.valor));
            else
                removeCoordenada(c, li->item.linha, li->item.coluna);

            li = li->direita;
        }
        p = p->abaixo;
    }
}

// -------------------------------------------- UTILS
void removeCoordenada(MATRIZ *a, int linha, int coluna) {
    PONT p = a->linha->primeiro;
    while (p->item.linha != linha)
        p = p->abaixo;

    PONT anterior = p;
    p = p->direita;
    while (p != NULL && p->item.coluna < coluna) {
        anterior = p;
        p = p->direita;
    }
    anterior->direita = p->direita;

    p = a->coluna->primeiro;
    while (p->item.coluna != coluna)
        p = p->direita;

    anterior = p;
    p = p->abaixo;
    while (p != NULL && p->item.linha < linha) {
        anterior = p;
        p = p->abaixo;
    }
    anterior->abaixo = p->abaixo;
}

void copiaMatriz(MATRIZ *a, MATRIZ *b) {
    b->nColunas = a->nColunas;
    b->nLinhas = a->nLinhas;
    criaListaLinha(b->linha, b->nLinhas);
    criaListaColuna(b->coluna, b->nColunas);

    PONT p = a->linha->primeiro->abaixo;
    while (p != NULL) {
        PONT li = p->direita;
        while (li != NULL) {
            insereMatriz(b, li->item.linha, li->item.coluna, li->item.valor);
            li = li->direita;
        }
        p = p->abaixo;
    }

}

// pega o PONT da coordenada (linha,coluna) na matriz A e retorna o valor do item caso exista um PONT, se nao retorna 0.
double getValorDaCoordenada(MATRIZ *a, int linha, int coluna) {
    PONT p = a->linha->primeiro;
    while (p->item.linha != linha)
        p = p->abaixo;

    p = p->direita;
    while (p != NULL && p->item.coluna < coluna)
        p = p->direita;

    if (p != NULL && p->item.coluna == coluna)
        return p->item.valor;

    return 0;
}

// verifica se a matriz está vazia.
int vaziaMatriz(MATRIZ *a) {
    if (a->linha->primeiro == NULL)
        return 1;

    return 0;
}

void apagaMatriz(MATRIZ *a) {
    if (a->nLinhas != 0 && a->nColunas != 0) {
        apagaLinha(a->linha->primeiro);
        apagaColuna(a->coluna->primeiro);
    }
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
    // leio o numero de linhas e numero de colunas
    scanf("%d", &(a->nLinhas));
    scanf("%d", &(a->nColunas));
    // crio listas encadeadas para linha e coluna
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

    // após ter declarado o PONT e o ITEM para os valores de linha, coluna e valor, insiro o PONT na lista de linha e na lista de coluna
    insereLinha(a->linha->primeiro, p);
    insereColuna(a->coluna->primeiro, p);
}

void insereLinha(PONT p, PONT inserir) {
    // percorro até chegar à linha que devo inserir
    while (p->item.linha < inserir->item.linha)
        p = p->abaixo;

    PONT direita = p->direita;
    // se o PONT direita for nulo entao essa linha ainda nao tem nenhum PONT, entao apenas adiciono no final
    if (direita == NULL) {
        p->direita = inserir;
    }
    // se o PONT direita for menor entao faço uma chamada recursiva passando a variavel direita como o primeiro argumento
    else if (direita->item.coluna < inserir->item.coluna) {
        insereLinha(direita, inserir);
    }
    // se o PONT direita for maior, eu insiro o novo PONT antes dele
    else if (direita->item.coluna > inserir->item.coluna) {
        inserir->direita = direita;
        p->direita = inserir;
    }
    else {
        // se já existe um PONT com as mesmas coordenadas eu substituo o valor
        direita->item.valor = inserir->item.valor;
    }
}

// basicamente a mesma coisa do inserelinha
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

// Como eu fiz uma lista encadeada para as listas coluna e linha, faço um loop para declarar um PONT para cada linha/coluna nos metodos criaListaColuna e criaListaLinha
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
    printf("Matriz:\n");
    for (i = 1; i <= a->nLinhas; i++) {
        imprimeLinha(a->linha, i, a->nColunas);
        printf("\n");
    }
    printf("Fim matriz.\n");
}

void imprimeLinha(LISTA *l, int i, int colunas) {
    PONT p = l->primeiro->abaixo;
    while (p->item.linha < i)
        p = p->abaixo;

    p = p->direita;
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
