# Simulação de memória Principal e memoria Cache em C

## O programa simula a comunicação entre os dois tipos de memória usando a técnica de escrita Write-Back e podendo ter substituições por FIFO e LRU em tempo de execução

Para a execução do código é preciso executar o arquivo main.exe (compilação do oarquivoo main.c)

No arquivo estrutura.h é possível alterar
- o tamanho da memoria principal
- o tamanho dos valores que terá em cada uma de suas linhas
- o tamanho da memoria cache
- a quantidade de acessos que serão feitos na memoria principal

Os valores da memoria principal, as posições de acesso da memoria principal e se haverá alteração ou não são gerados aleatóriamente