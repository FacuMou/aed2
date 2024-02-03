#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data
{
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length)
{
    struct bound_data res;
    bool rep;
    rep = true;
    res.exists = false;
    res.is_lowerbound = res.is_upperbound = true;
    for (int i = 0; i < length; i++)
    {
        if (value < arr[i])
        {
            res.is_lowerbound = true && res.is_lowerbound;
            res.is_upperbound = false && res.is_upperbound;
        }
        if (value > arr[i])
        {
            res.is_upperbound = true && res.is_upperbound;
            res.is_lowerbound = false && res.is_lowerbound;
        }
        if (value == arr[i] && rep)
        {
            res.exists = true;
            res.where = i;
            rep = false;
        }
    }
    return res;
}
void pedirarreglo(int arr[], unsigned int length)
{
    unsigned int i = 0;
    while (i < length)
    {
        printf("Ingrese el numero para la posicion %u del arreglo\n", i);
        scanf("%u", &arr[i]);
        i++;
    }
}

int main(void)
{
    int arr[ARRAY_SIZE];
    pedirarreglo(arr, ARRAY_SIZE);
    int value;
    printf("Ingrese un valor a verificar\n");
    scanf("%d", &value);
    struct bound_data result = check_bound(value, arr, ARRAY_SIZE);
    if (result.exists)
    {
        printf("Se ha encontrado el valor en la posicion %u\n", result.where);
        if (result.is_lowerbound)
        {
            printf("El valor introducido es el minimo del arreglo\n");
        }
        if (result.is_upperbound)
        {
            printf("El valor introducido es el maximo del arreglo\n");
        }
    }
    else
    {
        printf("No se ha encontrado el valor\n");
        if (result.is_lowerbound)
        {
            printf("El valor introducido es una cota minima\n");
        }
        else
        {
            printf("El valor introducido es una cota maxima\n");
        }
    }
    return EXIT_SUCCESS;
}
