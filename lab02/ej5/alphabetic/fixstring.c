#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    unsigned int length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool equal = true;
    unsigned int length_s1 = fstring_length(s1);
    unsigned int length_s2 = fstring_length(s2);
    unsigned int i = 0;

    if (length_s1 == length_s2) {
        while (i < length_s1 && equal) {
            if (s1[i] == s2[i]) {
                equal = true;
            } else {
                equal = false;
            }
            i++;
        }
    } else {
        equal = false;
    }
    return equal;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool lesseq = true;
    unsigned int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        i++;
    }
    if (s1[i] > s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        lesseq = false;
    } 
    else if (s2[i] == '\0') {
        lesseq = false;
    }
    return lesseq;
}

void fstring_set(fixstring s1, const fixstring s2){
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0'){
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2){
    fixstring aux;
    fstring_set(aux, s1);
    fstring_set(s1, s2);
    fstring_set(s2, aux);
}