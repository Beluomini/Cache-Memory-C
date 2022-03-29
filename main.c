# include <stdio.h>
# include <string.h>
# include <time.h>
# include "toolsFila.c"
# include "toolsRamCache.c"

int main (){
    int opcao;
    srand((unsigned)time(NULL));

    // Criacao da memoria RAM
    int memRam[QTD_LINHA_RAM];
    for(int i=0; i<QTD_LINHA_RAM; i++){
        memRam[i] = rand() % RANGE_RAM_VALORES;
    }
    printf("\n\n---> Imprimindo memoria RAM\n");
    for(int i=0; i<QTD_LINHA_RAM; i++){
        printf("posicao %d -> %d   ", i, memRam[i]);
        if(i%6 == 0){
            printf("\n");
        }
    }

    // Criacao da ordemm de acesso na RAM
    int acessosRAM[TAM_ENTRADA_ACESSOS];
    for(int i=0; i<TAM_ENTRADA_ACESSOS; i++){
        acessosRAM[i] = rand() % QTD_LINHA_RAM;
    }
    // 1 Se haverá alteracao e 0 se não havera
    int alteracaoEntrada[TAM_ENTRADA_ACESSOS];
    for(int i=0; i<TAM_ENTRADA_ACESSOS; i++){
        alteracaoEntrada[i] = rand() % 2;
    }

    printf("\n\n---> Imprimindo ordem de acesso da memoria RAM\n");
    for(int i=0; i<TAM_ENTRADA_ACESSOS; i++){
        printf("acesso %d -> alteracao %d\n", acessosRAM[i], alteracaoEntrada[i]);
    }



    printf("\n---> Criou lista vazia para memoria Cache\n"); // Cria uma lista vazia para memoia Cache
    TipoLista memCache;
    FLVazia(&memCache);

    for(int acessoAtual = 0; acessoAtual < TAM_ENTRADA_ACESSOS; acessoAtual++){ // Percorre todos os valores de acesso a ram
        
        printf("\n\n---> Pegando posicao %d na memoria RAM\n", acessosRAM[acessoAtual]);

        // Cria uma celula com o valor da posicao da RAM que foi acessado
        Celula a;
        a.Linha.alteracao = alteracaoEntrada[acessoAtual];
        a.Linha.fifo = acessoAtual;
        if(acessosRAM[acessoAtual] % 2 == 0){
            a.Linha.posicaoValor1 = memRam[acessosRAM[acessoAtual]];
            a.Linha.posicaoValor2 = memRam[acessosRAM[acessoAtual]+1];
            if(alteracaoEntrada[acessoAtual] == 1){
                a.Linha.valor1 = rand() % RANGE_RAM_VALORES;
                printf("\n--> Alteracao do valor: %d => %d", memRam[a.Linha.posicaoValor1], a.Linha.valor1);
            }else{
                a.Linha.valor1 = memRam[a.Linha.posicaoValor1];
            }
            a.Linha.valor2 = memRam[a.Linha.posicaoValor2];
        }else{
            a.Linha.posicaoValor1 = memRam[acessosRAM[acessoAtual]-1];
            a.Linha.posicaoValor2 = memRam[acessosRAM[acessoAtual]];
            a.Linha.valor1 = memRam[a.Linha.posicaoValor1];
            if(alteracaoEntrada[acessoAtual] == 1){
                a.Linha.valor2 = rand() % RANGE_RAM_VALORES;      
                printf("\n--> Alteracao do valor: %d => %d", memRam[a.Linha.posicaoValor2], a.Linha.valor2);
            }else{
                a.Linha.valor2 = memRam[a.Linha.posicaoValor2];
            }
        }

        // Busca a celula na memoria cache
        printf("\n--> Buscando celula %d - %d | %d - %d na memoria cache\n", a.Linha.posicaoValor1, a.Linha.valor1, a.Linha.posicaoValor2, a.Linha.valor2);
        Celula* encontrou = buscaNaCache(a, &memCache);
        if(encontrou == NULL){ // Se nao encontrou
            printf("\n-> Nao esta na cache\n");
            if(memCache.Tamanho < QTD_LINHA_CACHE){ // Se a cache não estiver cheia insere no fim da lista
                printf("\n> Inserindo na cache\n");
                Insere(a.Linha, &memCache);
            }else{ // Se a cache estiver cheia, usa um dos metodos FIFO ou LRU
                printf("\n> Cache cheia\n> Metodo de substituicao:");
                // Menu de opções
                printf("\n1 - Metodo de substituicao FIFO");
                printf("\n2 - Metodo de substituicao LRU");
                printf("\n>>> ");
                scanf("%d", &opcao);
                if(opcao == 1){
                    // Coloca o valor que foi inserido primeiro no topo da lista para ser removido
                    reorganizaFifo(&memCache);
                }
                // Remove o prieiro da lista
                removePrimeiroLista(a, &memCache, memRam);
            }
        }else{
            printf("\n-> Achou na posicao na cache (HIT)\n");
            // Em caso de HIT atualiza a memoria cache colocando a celula na ultma posicao e a cache eh impressa
            reorganizaHit(encontrou, &memCache);
            Imprime(memCache);
            
        }
    }

    printf("\n\n---> Imprimindo memoria RAM\n");
    for(int i=0; i<QTD_LINHA_RAM; i++){
        printf("posicao %d -> %d   ", i, memRam[i]);
        if(i%6 == 0){
            printf("\n");
        }
    }
    
    printf("\n\n---> Imprimindo memoria cache\n");
    Imprime(memCache);

    printf("\n\nPrograma Finalizado :)\n");
    return 0;

}