#include <stdio.h>
#include <stdlib.h>

#include "header/matriz/matriz.h"

void cria(LISTA *list);
int  insereLinha(LISTA *list, PONT pont);
int  insereColuna(LISTA* list, PONT pont);
void imprimeLinha(LISTA* list, int linha, int tamanho);

int main(){

    MATRIZ a, b, c;

    printf("Primeiro grupo de matrizes\n");
    criaMatriz(&a); leMatriz(&a); imprimeMatriz(&a);
    criaMatriz(&b); leMatriz(&b); imprimeMatriz(&b);
    printf("Soma\n");
    criaMatriz(&c); somaMatriz(&a, &b, &c); imprimeMatriz(&c);
    printf("Produto\n");
    apagaMatriz(&c); multiplicaMatriz(&a, &b, &c); imprimeMatriz(&c);

    printf("Segundo grupo de matrizes\n");
    apagaMatriz(&a); apagaMatriz(&b);apagaMatriz(&c);
    leMatriz(&a); imprimeMatriz(&a);  
    leMatriz(&b); imprimeMatriz(&b);
    printf("Soma\n");
    criaMatriz(&c); somaMatriz(&a, &b, &c); imprimeMatriz(&c);
    printf("Produto\n");
    apagaMatriz(&c); multiplicaMatriz(&a, &b, &c); imprimeMatriz(&c);

    apagaMatriz(&a);
    apagaMatriz(&b);
    apagaMatriz(&c);
      
    return 0;
}

void cria(LISTA *list){
    list->primeiro = NULL;
    list->ultimo = NULL;
}

int insereLinha(LISTA* list, PONT pont){
    PONT p = list->primeiro;
    if(p == NULL){
        p = PONT;
        return 1;
    }

    while(p.abaixo != NULL && p.abaixo.item.linha < pont.item.linha){
        if(p.abaixo.item.linha == pont.item.linha && p.abaixo.item.coluna > pont.item.coluna){
            pont.direita = p.abaixo;
            p.abaixo = pont;
            return 1;
        }

        p = p.abaixo;
    }

    if(p.item.linha != pont.item.linha){
        pont.abaixo = p.abaixo;
        p.abaixo = pont;
        return 1;
    }else{
	while(p.direita != NULL && p.direita.item.coluna < pont.item.coluna)
            p = p.direita;
        
        pont.direita = p.direita;
        p.direita = pont;
        return 1;
    }
}

int insereLinha(LISTA* list, PONT pont){
    PONT p = list->primeiro;
    if(p == NULL){
        p = PONT;
        return 1;
    }

    while(p.direita != NULL && p.direita.item.coluna < pont.item.coluna){
        if(p.direita.item.coluna == pont.item.coluna && p.direita.item.linha > pont.item.linha){
            pont.abaixo = p.direita;
            p.direita = pont;
            return 1;
        }

        p = p.direita;
    }

    if(p.item.coluna != pont.item.coluna){
        pont.direita = p.direita;
        p.direita = pont;
        return 1;
    }else{
	while(p.abaixo != NULL && p.abaixo.item.linha < pont.item.linha)
            p = p.abaixo;
        
        pont.abaixo = p.abaixo;
        p.abaixo = pont;
        return 1;
    }
}

void imprimeLinha(LISTA* list, int linha, int tamanho){
    PONT p = list->primeiro;
    if(p.item.linha != linha){
        while(p.abaixo != NULL && p.abaixo.item.linha <= linha)
            p = p.abaixo;

        if(p != NULL && p.item.linha != linha){
            p = NULL;
    }
    int i;
    for(i=0; i<tamanho; i++){
        if(p != NULL && p.item.coluna == i){
            printf("%d ", i);
            p = p.direita;
        } else
            printf("%d ", 0);
    }
}
