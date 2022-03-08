#ifndef LINHA
#define LINHA
#define CELULA
#define LISTA

#define QTD_LINHA_CACHE 8
#define TAM_ENTRADA 11

typedef struct{
    int valor1;     //valor da primeira coluna da linha
    int valor2;     //valor da segunda coluna da linha
    int alteracao;   //se vai haver alteracao na primeira coluna da linha
}LinhaCache;

typedef struct Celula{
    LinhaCache Linha;
    struct Celula* Prox;
}Celula;

typedef struct{
    struct Celula* Primeiro;
    struct Celula* Ultimo;
    int Tamanho;
}TipoLista;

#endif