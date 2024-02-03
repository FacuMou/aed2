#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree){
    return (tree == NULL) ? true : (
        (tree->left == NULL ? true : (
            (tree->left->elem >= tree->elem))) || 
        (tree->right == NULL ? true : (
            (tree->right->elem >= tree->elem))));
}

abb abb_empty(void) {
    return NULL;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    abb compare = abb_empty();
    abb before = abb_empty();
    if(!abb_exists(tree,e)){
        abb node=malloc(sizeof(struct _s_abb));
        node->elem=e;
        node->left=NULL;
        node->right=NULL;
        if(abb_is_empty(tree)){
            tree=node;
        }else{
            compare=tree;
            while(!abb_is_empty(compare)){
                before=compare;
                if(elem_less(e,compare->elem)){
                    compare=compare->left;
                }else{
                    compare=compare->right;
                }
            }
            if(elem_less(e,before->elem)){
               before->left=node;
            }else{
               before->right=node;
            }
        }
    }
    before=NULL;
    compare=NULL;
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}
bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    if (tree == NULL){
        is_empty = true;
    }
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    struct _s_abb *aux = tree;
    while(!exists && aux != NULL){
        if (elem_eq(e, aux->elem)) {
            exists = true;
        } else if(elem_less(e, aux->elem)){
            aux = aux->left;
        } else if (elem_less(aux->elem, e)){
            aux = aux->right;
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e){
    assert(invrep(tree));
    if(!abb_is_empty(tree)){
        abb node_before=tree;
        abb node_delete=tree;
        abb_elem elem;
        while(!abb_is_empty(node_delete)){
            abb p=node_delete->right;
            elem=node_delete->elem;
            if(elem_eq(e,elem)){
                abb d=node_delete->right;
                abb q=node_delete->left;
                if(!abb_is_empty(q)){
                    while(!abb_is_empty(d->left)){
                        d=d->left;
                    }
                    d->left=q;
                }
                if(elem_less(e,node_before->elem)){
                    node_before->left=p;
                }else if(elem_eq(e,node_before->elem)){
                    tree=p;
                }else{
                    node_before->right=p;
                }
                p=NULL;
                d=NULL;
                q=NULL;
                node_delete->left=node_delete->right=NULL;
                free(node_delete);
            }
            if(elem_less(e,elem)){
                node_before=node_delete;
                node_delete=node_delete->left;
            }else{
                node_before=node_delete;
                node_delete=node_delete->right;
            }
        }
        node_before=NULL;
        node_delete=NULL;
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (tree == NULL){return INT_MAX;}
    else{
        while (tree->right != NULL){
            tree = tree->right;
        }
        max_e = tree->elem;
        assert(invrep(tree) && abb_exists(tree, max_e));
        return max_e;
    }
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (tree == NULL){return INT_MAX;}
    else{
        while (tree->left != NULL){
            tree = tree->left;
        }
        min_e = tree->elem;
        assert(invrep(tree) && abb_exists(tree, min_e));
        return min_e;
    }
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL){
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

