#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if (x >= 0){
        *y = x;
    } else {
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    int* p = NULL;
    a = (-10);
    p = &res;
    absolute(a, p);
    printf("%d\n", res);
    return EXIT_SUCCESS;
}

/* El parametro 'int* y' es de tipo in/out, ya que se necesita ingresar
dicha variable, a pesar de que su valor sea modificado por la función,
independientemente del valor con el que ingrese */

/*C para sus funciones tiene Parámetros In/Out, ya que a pesar de que
haya variables cuyo valor no importe debido a que este va a ser modificado
por la función, se necesita que dicho valor se ingrese previamente para asi
poder modificarlo, por lo que todas las variables son in/out*/