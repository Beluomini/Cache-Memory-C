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
            
            int entrada[TAM_ENTRADA] = {3,2,4,7,21,5,10,24,12,14,16};
            int alteracaoEntrada[TAM_ENTRADA] = {0,0,0,0,0,0,0,0,0,0,0};
            int entradaAtual = 0;
            int memRam[1000];

            for(int i=0; i<1000; i++){
                memRam[i] = i;
                // memRam[i] = srand() % 1000;
            }

            TipoLista memCache;
            FLVazia(&memCache);
            printf("\n--> Criou lista vazia\n");

            for(int i=0; i<TAM_ENTRADA; i++){
                printf("\n\n--> Procurando pelo %d\n", entrada[entradaAtual]);
                int cont = 0;
                int vef = 0;
                while(vef == 0 && cont < 1000){
                    if(entrada[entradaAtual] == memRam[cont]){
                        Celula a;
                        a.Linha.alteracao = alteracaoEntrada[entradaAtual];
                        if(cont % 2 == 0){
                            a.Linha.valor1 = cont;
                            a.Linha.valor2 = cont+1;
                        }else{
                            a.Linha.valor1 = cont-1;
                            a.Linha.valor2 = cont;
                        }

                        Celula* encontrou = buscaNaCache(a, &memCache);
                        if(encontrou == NULL){
                            printf("\n-> nao esta na cache\n");
                            if(memCache.Tamanho < QTD_LINHA_CACHE){
                                printf("\n\n--> Inserindo na cache\n");
                                Insere(a.Linha, &memCache);
                            }else{
                                printf("\n--> Cache cheia\n");
                                insereNaCache(a, &memCache);
                            }
                        }else{
                            printf("\n-> Achou na posicao %d\n", cont);
                            ImprimeCelula(*encontrou);
                        }
                        vef = 1;
                    }
                    cont++;
                }
                if(vef == 0){
                    printf("\n\n-> Valor não encontrado na RAM\n");
                }
                entradaAtual++;
            }
            printf("\n\n--> Imprimindo cache\n");
            Imprime(memCache);

        }
   

   
    }while(opcao != 0);
    printf("\n\nPrograma Finalizado :)\n");
    return 0;
}