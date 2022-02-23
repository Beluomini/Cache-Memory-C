# include <stdio.h>
# include <string.h>
# include "toolsFila.c"
# include "toolsRamCache.c"

int main (){
    int entrada[TAM_ENTRADA] = {3,2,4,7,3};
    int entradaAtual = 0;

    int memRam[1000];
    for(int i=0; i<1000; i++){
        memRam[i] = i;
        // memRam[i] = rand() % 1000;
    }

    // for(int i=0; i<1000; i++){
    //     printf("%d\n", memRam[i]);
    // }

    TipoLista memCache;
    FLVazia(&memCache);
    printf("\n--> Criou lista vazia\n");

    for(int i=0; i<TAM_ENTRADA; i++){
        printf("\n\n--> Procurando pelo %d\n", entrada[entradaAtual]);
        int valoresBloco[2];
        int cont = 0;
        int vef = 0;
        while(vef == 0 && cont < 1000){
            if(entrada[entradaAtual] == memRam[cont]){
                if(cont % 2 == 0){
                    valoresBloco[0] = cont;
                    valoresBloco[1] = cont+1;
                }else{
                    valoresBloco[0] = cont-1;
                    valoresBloco[1] = cont;
                }
                Celula a;
                a.Linha.valor1 = valoresBloco[0];
                a.Linha.valor2 = valoresBloco[1];
                vef = 1;

                Celula* encontrou = buscaNaCache(a, &memCache);

                if(encontrou == NULL){
                    if(memCache.Tamanho < QTD_LINHA_CACHE){
                        printf("\n\n--> Inserindo na cache\n");
                        Insere(a.Linha, &memCache);
                    }else{
                        printf("\n--> Cache cheia, 'removendo' uma linha\n");
                        // Insere(a.Linha, &memCache);
                    }
                }else{
                    printf("\n\n--> Achou -----------------------------------");
                    printf ("\nvalor1: %d", encontrou->Linha.valor1);
                    printf ("\nvalor2: %d", encontrou->Linha.valor2);
                    printf ("\nalterar valor1: %d", encontrou->Linha.alterar1);
                    printf ("\nalterar valor2: %d", encontrou->Linha.alterar2);
                }
            }
            cont++;
        }
        if(vef == 0){
            printf("\n\nValor não encontrado na RAM\n");
        }
        entradaAtual++;
    }

    Imprime(memCache);

    
    printf("\n\nPrograma Finalizado :)\n");
    return 0;
}