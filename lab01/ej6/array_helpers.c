#include <stdio.h>
#include <stdlib.h>
#include "mybool.h"
#include "array_helpers.h"

void array_swap(int a[], unsigned int i, unsigned int j){
    int aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

mybool array_is_sorted(int a[], unsigned int length){
    mybool sorted = true;
    if (length != 0){
        for (unsigned int i = 0; i < length - 1 ; i++){
            sorted = sorted && (a[i] <= a[i+1]);
            if (!(a[i] <= a[i+1])){
                sorted = false;
                break;
        }
    }
    }
    return sorted;
}

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    FILE *pFile = fopen(filepath, "r");
    fscanf(pFile, "%u", &max_size); // Escanea el unsigned int del primer renglon y lo asocia a la variable max_size
    for (unsigned int i = 0; i < max_size; i++){
        fscanf(pFile, "%d", &array[i]);
        if (feof(pFile)){
            exit(EXIT_FAILURE);
        }
    }
    fclose(pFile);
    return max_size;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0; i < length; i++){
        printf("%d", a[i]);
        if (i != length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

