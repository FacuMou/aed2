#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

#define INITIAL_CAPACITY 1

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

// Invariante de representación
bool inv_rep(stack s){
    return s != NULL;
}

stack stack_empty() {
    stack s = (stack)malloc(sizeof(struct _s_stack));
    s->elems = (stack_elem *)calloc(INITIAL_CAPACITY, sizeof(stack_elem));
    s->size = 0;
    s->capacity = INITIAL_CAPACITY;
    assert(inv_rep(s));
    return s;
}

stack stack_push(stack s, stack_elem e) {
    assert(inv_rep(s));
    if (s->size == s->capacity) {
        // Si la pila está llena, se solicita más memoria para el doble de la capacidad actual
        unsigned int new_capacity = s->capacity * 2;
        s->elems = (stack_elem *)realloc(s->elems, new_capacity * sizeof(stack_elem));
        s->capacity = new_capacity;
    }
    s->elems[s->size] = e;
    s->size++;
    assert(inv_rep(s));
    return s;
}

stack stack_pop(stack s) {
    assert(inv_rep(s));
    if (!stack_is_empty(s)) {
        s->size--;
    }
    assert(inv_rep(s));
    return s;
}

unsigned int stack_size(stack s) {
    assert(inv_rep(s));
    return s->size;
}

stack_elem stack_top(stack s) {
    assert(inv_rep(s));
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s) {
    assert(inv_rep(s));
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s) {
    assert(inv_rep(s));
    stack_elem *array = (stack_elem *)calloc(s->size, sizeof(stack_elem));
    for (unsigned int i = 0; i < s->size; i++) {
        array[i] = s->elems[s->size-1-i];
    }
    assert(inv_rep(s));
    return array;
}

stack stack_destroy(stack s) {
    assert(inv_rep(s));
    free(s->elems);
    free(s);
    return NULL;
}