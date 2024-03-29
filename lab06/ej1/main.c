/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    int options = 7;
    int answer = -1;
    int input;
    do {
        printf("Ingresa una opción: \n"
        "1 ........ Mostrar árbol por pantalla\n"
        "2 ........ Agregar un elemento\n"
        "3 ........ Eliminar un elemento\n"
        "4 ........ Chequear existencia de elemento\n"
        "5 ........ Mostrar longitud del árbol\n"
        "6 ........ Mostrar raiz, máximo y mínimo del árbol\n"
        "7 ........ Salir\n\n"
        "Opcion: ");
        scanf(" %d", &answer);
        if (options > 7 || options < 0){
            printf("Opción no válida!");
            exit(EXIT_FAILURE);
        }
        switch(answer){
            case 1 :
                abb_dump(tree);
                break;
            case 2 :
                printf("Ingrese un elemento a añadir al árbol: ");
                scanf("%d", &input);
                tree = abb_add(tree, input);
                break;
            case 3 :
                printf("Ingrese un elemento a eliminar del árbol: ");
                scanf("%d", &input);
                if (!abb_exists(tree, input)){
                    printf("El elemento no se encuentra en el árbol");
                    exit(EXIT_FAILURE);
                }
                tree = abb_remove(tree, input);
                break;
            case 4 :
                printf("Ingrese un elemento a verificar del árbol: ");
                scanf("%d", &input);
                if (abb_exists(tree, input)){
                    printf("El elemento SI se encuentra en el árbol\n");
                }else {
                    printf("El elemento NO se encuentra en el árbol\n");
                }
                break;
            case 5 :
                printf("Longitud del árbol: %d\n", abb_length(tree));
                break;
            case 6 :
                printf("Raiz del árbol: %d\n", abb_root(tree));
                printf("Máximo del árbol: %d\n", abb_max(tree));
                printf("Mínimo del árbol: %d\n", abb_min(tree));
                break;
            case 7 :
                break;
        }
    } while (answer == (-1));

    tree = abb_destroy(tree);

    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    return (EXIT_SUCCESS);
}
