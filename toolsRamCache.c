#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int insereNaCache(Celula valor, TipoLista *memCache){
    if(buscaNaCache(valor, memCache) == NULL){
        if(memCache->Tamanho < QTD_LINHA_CACHE){
            Insere(valor.Linha, memCache);
            printf("\n\n--> Inserindo na cache\n");
            return 1;
        }else{
            printf("\n-->'removendo' uma linha\n");
            Retira(memCache->Primeiro, memCache);
            printf("\n---> removeu o ultimo\n");
            Insere(valor.Linha, memCache);
            printf("\n---> inseriu o novo\n");
            return 0;
        }
    }
    return 0;
}