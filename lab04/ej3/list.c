#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct node_t {
    list_elem value;
    struct node_t *next;
}Nodo;

list empty(){
    return NULL;
}

list addl(list l, list_elem e){
    struct node_t *n;
    n = malloc(sizeof(struct node_t));
    n->next = l;
    n->value = e;
    l = n;
    n = NULL;
    return l;
}

void destroy(list l){
    list q = NULL;
    while (l->next != NULL){
        q = l;
        l = l->next;
        free(q);
        q = NULL;
    }
    free(l);
}

bool is_empty(list l){
    return (l == empty(l));
}

list_elem head(list l){
    assert(!is_empty(l));
    return l->value;
}

list tail(list l){
    assert(!is_empty(l));
    return l->next;
}

list addr(list l, list_elem e){
    list n;
    n = malloc(sizeof(struct node_t));
    n->value = e;
    n->next = NULL;
    if (l != NULL){
        list copy;
        copy = l;
        while (l->next != NULL){
        copy = copy->next;
        }
        copy->next = n;
    } else {
        l = n;
        }
    return l;
}

unsigned int length(list l){
    unsigned int i = 0u;
    list c = l;
    while (c->next != NULL){
        c = c->next;
        i++;
    }
    return i;
}

list concat(list l1, list l2){
    if (l1 != NULL){
        list copy;
        copy = l1;
        while (l1->next != NULL){
        copy = copy->next;
        }
        copy->next = l2;
    } else {
        l1 = l2;
        }
    return l1;
}

list_elem index(list l, unsigned int i){
    assert(i < length(l));
    unsigned int index = 0u;
    list copy = l;
    while (index < i){
        copy = copy->next;
        index++;
    }
    return copy->value;
}

list take(list l, unsigned int n){
    list q = l;
    for (unsigned int i=0; i != n; i++){
        q = q->next;
    }
    q = q->next;
    destroy(l);
    return q;
}

list drop(list l, unsigned int n){
    assert(n < length(l));
    while (n > 0){
        l = l->next;
        n--;
    }
    return l;
}

list copy_list(list l){
    list copy = empty();
    copy = concat(copy, l);
    return copy;
}
