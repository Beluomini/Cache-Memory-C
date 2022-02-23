#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "estrutura.h"

void FLVazia (TipoLista *Lista){
    Lista -> Primeiro = (Celula*) malloc(sizeof(Celula));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
    Lista -> Tamanho = 0;
}

int Vazia (TipoLista Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere (LinhaCache novaLinha, TipoLista *Lista){
    Lista -> Ultimo -> Prox = (Celula*) malloc(sizeof(Celula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Linha = novaLinha;
    Lista -> Ultimo -> Prox = NULL;
    Lista -> Tamanho++;
}

//Busca um valor na memoria ram e retorna -1 caso nao encontre ou a linha em que o valor se encontra na cache
Celula* buscaNaCache(Celula cel, TipoLista *memCache){
    Celula* aux;
    aux = memCache->Primeiro;
    while(aux != NULL){
        if(aux->Linha.valor1 == cel.Linha.valor1 || aux->Linha.valor2 == cel.Linha.valor2){
            return aux;
        }
        aux = aux->Prox;
    }
    return aux;
}

void Retira (Celula* p, TipoLista *Lista){
    Celula* q;
    if (Vazia(*Lista)||p->Prox==NULL){
        printf ("Erro: lista vazia ou posicao inexistente.\n");
    }else{
        q = p->Prox;
        p->Prox = q->Prox;
        if (p->Prox == NULL)
            Lista->Ultimo = p;
        free(q);
        Lista->Tamanho--;
    }
}

void Imprime(TipoLista Lista){
    Celula* Aux;
    int i=1;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL){
        printf ("\n\nCodigo do elemento %d: %d", i, Aux->Linha.valor1);
        printf ("\n\nCodigo do elemento %d: %d", i, Aux->Linha.valor2);
        printf ("\n\nCodigo do elemento %d: %d", i, Aux->Linha.alterar1);
        printf ("\n\nCodigo do elemento %d: %d", i, Aux->Linha.alterar2);
        printf ("\n-----------------------------------------------------\n");
        Aux=Aux->Prox;
        i++;
    }
}