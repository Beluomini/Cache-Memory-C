#ifndef LINHA
#define LINHA
#define CELULA
#define LISTA

#define QTD_LINHA_CACHE 8
#define TAM_ENTRADA 5

typedef struct{
    int valor1;     //valor da primeira coluna da linha
    int valor2;     //valor da segunda coluna da linha
    int alterar1;   //se vai haver alteracao na primeira coluna da linha
    int alterar2;   //se vai haver alteracao na segunda coluna da linha
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