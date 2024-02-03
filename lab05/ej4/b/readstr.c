#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    fgets(user_input, MAX_LENGTH, stdin);
    int length = strlen(user_input);
    user_input[length-1] = '\0';

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}

/* Uno de los problemas que identifique fue que:
* -El tamaño de la entrada es indiferente, salvo en el caso de números,
* en cuyo caso el programa tiene un límite el cual si se excede, el programa termina
*/