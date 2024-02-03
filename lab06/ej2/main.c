#include <stdlib.h>
#include <string.h>
#include "string.h"

int main(void) {
    char p1[23],p2[23];
    string word1,word2;
    printf("Ingrese una palabra: ");
    scanf("%s",p1);
    printf("\n");
    word1=string_create(p1);
    printf("Ingrese otra palabra: ");
    scanf("%s",p2);
    printf("\n");
    word2=string_create(p2);
    if(string_eq(word1,word2)){
        printf("Las palabras ingresadas son iguales.\n");
    }else if(string_less(word1,word2)){
        printf("La primer palabra es menor a la segunda.\n");
    }else{
        printf("La primer palabra es mayor a la segunda.\n");
    }
    return EXIT_SUCCESS;
}
