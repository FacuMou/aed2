#include "strfuncs.h"
#include <stdio.h>

size_t string_length(const char *str){
    size_t i = 0;
    while (str[i] != '\0'){
        i++;
    }
    return i;
}

char *string_filter(const char *str, char c){
    size_t old_length = string_length(str);
    size_t new_length = 0;
    for (size_t i = 0; i < old_length; i++){
        if (str[i] != c){
            new_length++;
        }
    }

    char* new_string;
    // Reservo memoria requerida para una cadena de chars, añado 1 para '\0'
    new_string = (char *)malloc(sizeof(char) * (new_length+1)); 
    size_t j = 0;
    for(size_t i = 0; i < old_length; i++){
        if (str[i] != c){
            new_string[j+1] = str[i]; 
        }
    }
    new_string[new_length] = '\0'; // Guardo el caracter que indica fin de la cadena
    return new_string;
}