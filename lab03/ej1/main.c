/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

  int x = 1;
  person_t m = {90, 'M'};
  int a[] = {0, 1, 2, 3};
  int* p = NULL;
  person_t* q = NULL;
  
  // p : puntero ; &p : 'espacio en la memoria' asignado al puntero ; 
  // *p : 'valor' del espacio asignado al puntero

  p = &x, q = &m;
  *p = 9;
  q->age = 100;
  q->name_initial = 'F';

  printf("x = %d\n", x);
  printf("m = (%d, %c)\n", m.age, m.name_initial);
  
  // NULL : libera el valor de la memoria ; Free : elimina el puntero al espacio de la memoria
  
  p = NULL;
  free(p);

  p = &a[1];
  *p = 42;

  printf("a[1] = %d\n", a[1]);

  return EXIT_SUCCESS;
}

