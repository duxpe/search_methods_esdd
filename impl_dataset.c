#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct DataSet {
    int size;
    unsigned int *data;
};

struct IndexTable {
    int start;
    int end;
};


// Criar o DataSet
T_DataSet create_data_set(int seed, int size) {
    if (size <= 0) {
        fprintf(stderr, "Tamanho inválido para o DataSet.\n");
        exit(EXIT_FAILURE);
    }

    T_DataSet data_set = malloc(sizeof(struct DataSet));
    if (data_set == NULL) {
        perror("Falha na alocação de memória para o DataSet");
        exit(EXIT_FAILURE);
    }

    unsigned int *arr = malloc((size + 1) * sizeof(unsigned int));
    if (arr == NULL) {
        perror("Falha na alocação de memória para o array de dados");
        free(data_set);
        exit(EXIT_FAILURE);
    }

    arr[0] = seed;
    srand(seed);
    for (unsigned int i = 1; i < size; i++) {
        arr[i] = arr[i - 1] + ((rand() % 100)) + 1;
    }

    data_set->data = arr;
    data_set->size = size;
    if(DEBUG == 1){
        printf("First element : [%d]\n",data_set->data[0]);
        printf("Middle element : [%d]\n",data_set->data[size/2]);
        printf("Last element : [%d]\n",data_set->data[size-1]);
    }
    return data_set;
}

int sequential_search_range(T_DataSet data, int search_key, int start, int end){
    for (int i = start; i <= end; i++) {
        if (data->data[i] == search_key) {
            return i;
        }
    }

    return -1;
}

int sequential_search(T_DataSet data, int search_key){
    for (int i = 0; i < data->size; i++) {
        if (data->data[i] == search_key) {
            return i;
        }
    }

    return -1;
}

// Calcula qual o tamanho do bloco
int calculate_block_size(int start, int end) {
    if (start >= end) {
        printf("Start (%d) econtrou End (%d). Ops!\n", start, end);
        return 2;
    }

    int total_size = end - start;
    return (total_size * 0.1) > 1 ? (total_size * 0.1) : 2;
}

// Cria índices
T_IndexTable create_index_table(T_DataSet data, int original_start, int original_end, int blocksize, int search_key) {
    if (data == NULL || data->data == NULL) {
        printf("DataSet inválido.\n");
        exit(EXIT_FAILURE);
    }
    if (blocksize <= 0) {
        printf("Tamanho de bloco inválido.\n");
        exit(EXIT_FAILURE);
    }

    int size = data->size;
    int group_qtt = (size + blocksize - 1) / blocksize;

    int *elements = malloc(group_qtt * sizeof(int));
    int *indexes = malloc(group_qtt * sizeof(int));

    if (elements == NULL || indexes == NULL) {
        printf("Falha na alocação de memória tablas indexes");
        free(elements);
        free(indexes);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < group_qtt; i++) {
        elements[i] = data->data[i * blocksize];
        indexes[i] = i * blocksize;
    }

    int start = 0, end = 0;
    for (int i = 0; i < group_qtt; i++) {
        if (search_key < elements[i]) {
            break;
        }
        start = indexes[i];
        end = (i == group_qtt - 1) ? size - 1 : indexes[i + 1] - 1;
    }

    free(elements);
    free(indexes);

    T_IndexTable table = malloc(sizeof(struct IndexTable));
    if (table == NULL) {
        printf("Falha: alocação de memóriaa tipo IndexTable");
        exit(EXIT_FAILURE);
    }

    table->start = start;
    table->end = end;
    if(DEBUG == 1){
        printf("BlockSize: %d \nStart: %d End: %d \n", blocksize, start, end);
    }
    return table;
}

// Busca sequencial indexada
int indexed_sequential_search(T_DataSet data, int search_key, int indexes_qtt) {
    if (data == NULL || data->data == NULL) {
        printf("DataSet inválido.\n");
        return -2;
    }
    if (indexes_qtt <= 0) {
        printf("Quantidade de tables índice dvem ser maior que 0 :(\n");
        return -2;
    }

    int start = 0, end = data->size;
    for (int i = 0; i < indexes_qtt; i++) {
        if(DEBUG == 1){
            printf("Processo da Tabela Index: %d\n",i);
        }
        int block_size = calculate_block_size(start, end);
        T_IndexTable index = create_index_table(data, 0, data->size, block_size, search_key);
        start = index->start;
        end = index->end;
        free(index);
    }

    return sequential_search_range(data, search_key, start, end);
}

// Utilidades para print
void printArray(T_DataSet ds) {
    if (ds == NULL || ds->data == NULL) {
        printf("DataSet inválido.\n");
        return;
    }
    printf("array = [");
    for (int i = 0; i < ds->size; i++) {
        printf("%u, ", ds->data[i]);
    }
    printf("];\n");
}

void printLine(){
    printf("-------------------------------------------------------------------\n");
}