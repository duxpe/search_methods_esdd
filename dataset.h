#include <stdio.h>
#include <stdlib.h>

typedef struct DataSet* T_DataSet;

typedef struct IndexTable* T_IndexTable;


T_DataSet create_data_set(int seed, int size);

// T_IndexTable create_index_table(T_DataSet data, int spacing); usuário não vai precisar de acesso...

int indexed_sequential_search(T_DataSet data, int search_key, int qtd_index);

void printArray(T_DataSet data_set);