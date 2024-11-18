#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct DataSet* T_DataSet;

typedef struct IndexTable* T_IndexTable;


T_DataSet create_data_set(int seed, int size);

int sequential_search(T_DataSet data, int search_key);

int indexed_sequential_search(T_DataSet data, int search_key, int qtd_index);

void printArray(T_DataSet data_set);

void printLine();

