# include <stdio.h>
# include <string.h>
# include "toolsFila.c"
# include "toolsRamCache.c"

int main (){
    int opcao = 1;
    do{
        printf("\n\n 0 - Sair");
        printf("\n 1 - Metodo de substituicao FIFO");
        printf("\n 2 - Metodo de substituicao Aleatorio");
        printf("\n Resposta: ");
        scanf("%d", &opcao);
        
        if(opcao == 1){
            
            int entrada[TAM_ENTRADA] = {3,2,4,7,21,6,10,24,12,14,16,32};
            int alteracaoEntrada[TAM_ENTRADA] = {0,0,1,0,0,0,0,0,0,0,0,0};
            int entradaAtual = 0;
            int memRam[1000];

            for(int i=0; i<1000; i++){
                memRam[i] = i;
                // memRam[i] = rand() % 1000;
            }

            TipoLista memCache;
            FLVazia(&memCache);
            printf("\n---> Criou lista vazia\n");

            for(int i=0; i<TAM_ENTRADA; i++){
                printf("\n\n---> Procurando pelo %d na memoria RAM\n", entrada[entradaAtual]);
                int cont = 0;
                int vef = 0;
                while(vef == 0 && cont < 1000){
                    if(entrada[entradaAtual] == memRam[cont]){

                        Celula a;
                        a.Linha.alteracao = alteracaoEntrada[entradaAtual];
                        if(cont % 2 == 0){
                            a.Linha.posicaoValor1 = cont;
                            a.Linha.posicaoValor2 = cont+1;
                            if(alteracaoEntrada[entradaAtual] == 1){
                                a.Linha.valor1 = rand() % 1000;
                                printf("\nvalor a ser trocado %d\n", a.Linha.valor1);
                            }else{
                                a.Linha.valor1 = memRam[a.Linha.posicaoValor1];
                            }
                            a.Linha.valor2 = memRam[a.Linha.posicaoValor2];
                        }else{
                            a.Linha.posicaoValor1 = cont-1;
                            a.Linha.posicaoValor2 = cont;
                            a.Linha.valor1 = memRam[a.Linha.posicaoValor1];
                            if(alteracaoEntrada[entradaAtual] == 1){
                                a.Linha.valor2 = rand() % 1000;
                                printf("\nvalor a ser trocado %d\n", a.Linha.valor2);
                            }else{
                                a.Linha.valor2 = memRam[a.Linha.posicaoValor2];
                            }
                        }
                        Celula* encontrou = buscaNaCache(a, &memCache);
                        if(encontrou == NULL){
                            printf("\n--> Nao esta na cache\n");
                            if(alteracaoEntrada[entradaAtual] == 1){
                                if(cont % 2 == 0){
                                    a.Linha.valor1 = rand() % 1000;
                                    printf("\nvalor a ser trocado %d\n", a.Linha.valor1);
                                }else{
                                    a.Linha.valor2 = rand() % 1000;
                                    printf("\nvalor a ser trocado %d\n", a.Linha.valor2);
                                }
                            }

                            if(memCache.Tamanho < QTD_LINHA_CACHE){
                                printf("\n-> Inserindo na cache\n");
                                Insere(a.Linha, &memCache);
                            }else{
                                printf("\n-> Cache cheia\n");
                                substituiCacheFifo(a, &memCache, memRam);
                            }
                        }else{
                            printf("\n--> Achou na posicao %d\n", cont);
                            ImprimeCelula(*encontrou);
                        }
    
                        vef = 1;
                    }

                    cont++;
                }

                if(vef == 0){
                    printf("\n\n---> Valor nao encontrado na RAM\n");
                }
                entradaAtual++;
            }
            for(int i=0; i<100; i++){
                printf("\n%d", memRam[i]);
            }
            printf("\n\n--> Imprimindo cache\n");
            Imprime(memCache);

        }
   

   
    }while(opcao != 0);
    printf("\n\nPrograma Finalizado :)\n");
    return 0;
}