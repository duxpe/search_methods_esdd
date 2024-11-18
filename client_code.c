#include "dataset.h"
#include <time.h>

void main(){
    int index_table_qtt = 3;
    int search_key = 25252113;

    T_DataSet ds = create_data_set(1235, 1000000);
    double start = 0.0, end = 0.0, time = 0.0;
    
    printLine();
    printf("Bunca sem índices: \n");
    start = clock();
    int search = sequential_search(ds, search_key);
    end = clock();
    time = ((double)(end-start) / CLOCKS_PER_SEC);
    printf("\nA posição resultado foi: %d - %s.\n Tempo: %lfs\n", 
            search, search>0 ? "Sucesso" : "Não encontrado", time);
    printLine();

    start = 0.0, end = 0.0, time = 0.0;

    printLine();
    printf("Bunca com %d tabela(s) de índices: \n", index_table_qtt);
    start = clock();
    int search_i = indexed_sequential_search(ds, search_key, index_table_qtt);
    end = clock();
    time = ((double)(end-start) / CLOCKS_PER_SEC);
    printf("\nA posição resultado da busca com index foi: %d - %s.\n Tempo decorrido: %lfs\n", 
            search_i, search_i>0 ? "Sucesso" : "Não encontrado", time);
    printLine();
}