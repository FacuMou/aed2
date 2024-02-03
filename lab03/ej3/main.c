#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parse_filepath(int argc, char *argv[]) {
    char *result = NULL;
    bool valid_args_count = (argc == 2);
    if (!valid_args_count) {
        printf("Filepath args not valid");
        exit(EXIT_FAILURE);
    }
    result = argv[1];
    return result;
}
char* data_is_sorted(char letters[],char sorted[], unsigned int indexes[], unsigned int max_size){
    unsigned int p = 0;
    for (unsigned int i = 0; i < max_size; i++){
        p = indexes[i];
        sorted[p] = letters[i];
    }
    return sorted;
}

unsigned int data_from_file(const char *path,
                            unsigned int indexes[],
                            char letters[],
                            unsigned int max_size){
    FILE *pFile = fopen(path, "r");
    if (pFile == NULL){
        printf("File does not exist");
        exit(EXIT_FAILURE);
    } 
    if (max_size > MAX_SIZE){
        printf("Data length not allowed");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0;
    int length;
    while (!feof(pFile) && i < max_size){

        length = fscanf(pFile, "%u -> *%c* ", &(indexes[i]), &(letters[i]));

        if (length != 2){
            printf("Formato de archivo invalido \n");
        }
        i++;
    }
    fclose(pFile);
    return i;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    // cargar lo pasado por consola
    filepath = parse_filepath(argc, argv);
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    unsigned int length = data_from_file(filepath, indexes, letters, MAX_SIZE);
    char sorted[MAX_SIZE];
    data_is_sorted(letters, sorted, indexes, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

