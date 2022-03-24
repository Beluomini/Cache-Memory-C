# include <stdio.h>
# include <string.h>
# include "toolsFila.c"
# include "toolsRamCache.c"

int main (){
    int opcao = 1;
    // Menu de opções
    printf("\n\n 0 - Sair");
    printf("\n 1 - Metodo de substituicao FIFO");
    printf("\n 2 - Metodo de substituicao LRU");
    printf("\n Resposta: ");
    scanf("%d", &opcao);
    do{
        
        int acessosRAM[TAM_ENTRADA_ACESSOS] = {3,2,4,7,21,4,10,24,12,14,16,32}; // Ordem de acesso de posicoes da RAM
        int alteracaoEntrada[TAM_ENTRADA_ACESSOS] = {0,0,1,0,0,0,0,0,0,0,0,0}; // 1 Se haverá alteracao e 0 se não haverá

        // Criacao da memoria RAM
        int memRam[QTD_LINHA_RAM];
        for(int i=0; i<QTD_LINHA_RAM; i++){
            memRam[i] = i;
            // memRam[i] = rand() % RANGE_RAM_VALORES;
        }

        printf("\n---> Criou lista vazia para memoria Cache\n"); // Cria uma lista para memoia Cache
        TipoLista memCache;
        FLVazia(&memCache);

        for(int acessoAtual = 0; acessoAtual < TAM_ENTRADA_ACESSOS; acessoAtual++){ // Percorre todos os valores de acesso a ram
            printf("\n\n---> Pegando posicao %d na memoria RAM\n", acessosRAM[acessoAtual]);

            Celula a;
            a.Linha.alteracao = alteracaoEntrada[acessoAtual];
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

            printf("\n--> Buscando celula %d - %d | %d - %d na memoria cache\n", a.Linha.posicaoValor1, a.Linha.valor1, a.Linha.posicaoValor2, a.Linha.valor2);

            Celula* encontrou = buscaNaCache(a, &memCache);
            if(encontrou == NULL){
                printf("\n-> Nao esta na cache\n");

                if(memCache.Tamanho < QTD_LINHA_CACHE){ // Se a cache não estiver cheia insere no fim da lista
                    printf("\n> Inserindo na cache\n");
                    Insere(a.Linha, &memCache);
                }else{ // Se a cache estiver cheia, usa um dos metodos FIFO ou LRU
                    printf("\n> Cache cheia\n");
                    // Para ambas as opcoes, o metodo FIFO é o que vai ser usado para subtituicao de velores na CACHE.
                    // No entando o LRU é aplicado quando há um HIT movendo o valor que fio acessado para o topo da lista do fifo novamente
                    substituiCacheFifo(a, &memCache, memRam);
                }
            }else{
                printf("\n-> Achou na posicao na cache (HIT)\n");
                Imprime(memCache);
                if(opcao == 2){
                    printf("\n> Para o LRU valor tem que ser jogado para o final da lista\n");
                    Celula *aux = memCache.Primeiro->Prox;
                    while(aux != NULL && memCache.Ultimo != encontrou){
                        if(aux->Prox == encontrou){
                            printf("\n> Movendo para o final da lista\n");
                            aux->Prox = encontrou->Prox;
                            memCache.Ultimo->Prox = encontrou;
                            memCache.Ultimo = encontrou;
                            memCache.Ultimo->Prox = NULL;
                        }
                        aux = aux->Prox;
                    }

                }
                Imprime(memCache);
                
            }
        }

        for(int i=0; i<100; i++){
            printf("\n%d", memRam[i]);
        }
        
        printf("\n\n--> Imprimindo cache\n");
        Imprime(memCache);

        // Menu de opções
        printf("\n\n 0 - Sair");
        printf("\n 1 - Metodo de substituicao FIFO");
        printf("\n 2 - Metodo de substituicao LRU");
        printf("\n Resposta: ");
        scanf("%d", &opcao);

    }while(opcao != 0);
    printf("\n\nPrograma Finalizado :)\n");
    return 0;

}