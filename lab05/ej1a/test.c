#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem value;
    struct _s_stack *next;
};

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    stack copy = s;
    s = copy->next;
    free(copy);
    return s;
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