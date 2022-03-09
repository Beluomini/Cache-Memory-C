#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "estrutura.h"

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

//Caso a cache esteja cheia, retira o ultimo valor que foi adicionado a ela
int substituiCacheFifo(Celula valor, TipoLista *memCache, int *memRam){
    printf("\n> Limpou uma linha\n");

    if(memCache->Primeiro->Prox->Linha.alteracao == 1){
        int posicaoValor1 = memCache->Primeiro->Prox->Linha.posicaoValor1;
        int posicaoValor2 = memCache->Primeiro->Prox->Linha.posicaoValor2;
        printf("\n>> Alterou a linha %d da RAM: %d => %d", posicaoValor1, memRam[posicaoValor1], memCache->Primeiro->Prox->Linha.valor1);
        printf("\n>> Alterou a linha %d da RAM: %d => %d", posicaoValor2, memRam[posicaoValor2], memCache->Primeiro->Prox->Linha.valor2);
        memRam[posicaoValor1] = memCache->Primeiro->Prox->Linha.valor1;
        memRam[posicaoValor2] = memCache->Primeiro->Prox->Linha.valor2;
        
    }
    Retira(memCache->Primeiro, memCache);
    Insere(valor.Linha, memCache);
    printf("\n> Inseriu o novo\n");
    return 0;
}