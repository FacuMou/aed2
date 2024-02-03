#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem value;
    struct _s_stack *next;
};

stack stack_empty(){
    stack s=NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack copy = malloc(sizeof(struct _s_stack));
    copy->value = e;
    copy->next = s;
    s = copy;
    copy = NULL;
    free(copy);
    return s;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    stack copy = s;
    s = copy->next;
    free(copy);
    return s;
}

unsigned int stack_size(stack s){
    unsigned int length = 0u;
    stack copy = s;
    if (s == NULL){
        return length;
    }
    length++;
    while (copy->next != NULL){
        copy = copy->next;
        length++;
    }
    return length;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->value;
}

bool stack_is_empty(stack s){
    return (stack_size(s) == 0);
}

stack_elem *stack_to_array(stack s){
    int st_length = stack_size(s);
    stack_elem *array = calloc(st_length, sizeof(struct _s_stack));
    for (int i = 0; i < st_length; i++){
        array[i] = stack_top(s);
        s = stack_pop(s);
    }
    return array;
}

stack stack_destroy(stack s){
    stack aux = NULL;
    while (s->next != NULL){
        aux = s;
        s = s->next;
        free(aux);
    }
    return s;
}