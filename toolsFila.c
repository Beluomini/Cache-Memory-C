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

//Insere no fim da lista
void Insere (LinhaCache novaLinha, TipoLista *Lista){
    Lista -> Ultimo -> Prox = (Celula*) malloc(sizeof(Celula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Linha = novaLinha;
    Lista -> Ultimo -> Prox = NULL;
    Lista -> Tamanho++;
}

//Busca um valor na lista remove caso encontre
void Retira (Celula* p, TipoLista *Lista){
    Celula* q;
    if (Vazia(*Lista)){
        printf ("Erro: lista vazia ou posicao inexistente.\n");
    }else if(p->Prox==NULL){
        q = Lista->Primeiro;
        while(q->Prox != p){
            q = q->Prox;
        }
        q->Prox = NULL;
        Lista->Ultimo = q;
        Lista->Tamanho--;
        free(p);
    }else{
        q = p->Prox;
        p->Prox = q->Prox;
        if (p->Prox == NULL)
            Lista->Ultimo = p;
        free(q);
        Lista->Tamanho--;
    }
}

//Busca um valor na lista remove caso encontre
void RetiraPrimeiro (Celula* p, TipoLista *Lista){
    if (Vazia(*Lista)){
        printf ("Erro: lista vazia ou posicao inexistente.\n");
    }else if(p->Prox==NULL){
        Lista -> Primeiro = (Celula*) malloc(sizeof(Celula));
        Lista -> Ultimo = Lista -> Primeiro;
        Lista -> Primeiro -> Prox = NULL;
        Lista->Tamanho--;
        free(p);
    }else{
        Lista->Primeiro = p->Prox;
        Lista->Tamanho--;
        free(p);
    }
}

//Imprime a lista
void Imprime(TipoLista Lista){
    Celula* Aux;
    int i=1;
    Aux = Lista.Primeiro -> Prox;
    printf ("\n-----------------------------------------------------");
    while (Aux != NULL){
        printf ("\nCodigo do elemento %d: %d", i, Aux->Linha.valor1);
        printf ("\nCodigo do elemento %d: %d", i, Aux->Linha.valor2);
        printf ("\nCodigo do elemento %d: %d", i, Aux->Linha.alteracao);
        printf ("\n-----------------------------------------------------");
        Aux=Aux->Prox;
        i++;
    }
}

//Imprime a lista uma Celula
void ImprimeCelula(Celula cel){
    printf("\n\n-> Celula -----------------------------------");
    printf ("\nvalor1: %d", cel.Linha.valor1);
    printf ("\nvalor2: %d", cel.Linha.valor2);
    printf ("\nverificador de alteracao: %d", cel.Linha.alteracao);
    printf ("\n-----------------------------------------------------\n");
}