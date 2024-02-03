#include <stdlib.h>
#include "pair.h"

struct s_pair_t {
    int fst;
    int snd;
};
    // Constructors

pair_t pair_new (elem x, elem y){
    pair_t pair;
    pair = malloc(sizeof(struct s_pair_t));
    pair->fst = x;
    pair->snd = y;
    return pair;
}

pair_t pair_destroy(pair_t p){
    free(p);
    return p;
}
    // Operations

elem pair_first(pair_t p){
    return p->fst;
}

elem pair_second(pair_t p){
    return p->snd;
}

pair_t pair_swapped(pair_t p){
    pair_t copy = malloc(sizeof(struct s_pair_t));
    copy->fst = p->snd;
    copy->snd = p->fst;
    return copy;
}


/* La diferencia es que esta nueva definición sirve para
todo tipo de par de elementos, solo se requiere de
cambiar la especificación dada en pair.h por el tipo a trabajar.
En este caso, el tipo definido de 'elem' es Int.*/


