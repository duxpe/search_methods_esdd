#include "dataset.h"

void main(){
    T_DataSet ds = create_data_set(1234,1000000);

    printArray(ds);

    int search = indexed_sequential_search(ds, 121029, 3);

    printf("A posição resultado da busca foi: %d - %s\n", 
            search, search>0 ? "Sucesso" : "Não encontrado");
}