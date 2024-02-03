#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    return d == NULL ? true : (
        (d->left == NULL ? true : 
            key_less(d->left->key, d->key) &&
            !key_eq(d->left->key, d->key) &&
            invrep(d->left))
        &&
        (d->right == NULL ? true :
            key_less(d->right->key, d->key) &&
            !key_eq(d->right->key, d->key) &&
            invrep(d->right))
    );
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict)==0);
    return dict;
}

static dict_t last(dict_t d, dict_t node){
     if(d == NULL){
         d=node;
     }else if(key_less(node->key,d->key)){
         d->left=last(d->left,node);
     }else{
         d->right=last(d->right,node);
     }
     return d;
}

dict_t dict_add(dict_t dict, key_t word, value_t def){
    assert(invrep(dict));
    dict_t compare=dict;
    if(dict_exists(dict,word)){
        while(compare != NULL && !key_eq(compare->key,word)){
            if(key_less(word,compare->key)){
                compare=compare->left;
            }else{
                compare=compare->right;
            }
        }
        compare->value=value_destroy(compare->value);
        compare->value=def;
    }else{
        dict_t node=calloc(1,sizeof(struct _node_t));
        node->left=NULL;
        node->right=NULL;
        node->key=word;
        node->value=def;
        dict=last(dict,node);
    }
    compare=NULL;
    assert(invrep(dict) && key_eq(def, dict_search(dict, word)));
    return dict;
}

static value_t searching(dict_t dict, key_t word){
    value_t def;
    if(key_eq(dict->key,word)){
            def=dict->value;
        }else if(key_less(word,dict->key)){
            def=dict_search(dict->left,word);
        }else{
            def=dict_search(dict->right,word);
        }
    return def;
}

value_t dict_search(dict_t dict, key_t word){
    assert(invrep(dict));
    value_t def=NULL;
    if(dict_exists(dict,word)){
        def=searching(dict,word);
    }
    assert(dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word){
    assert(invrep(dict));

    bool exists = (dict == NULL ? false :
        key_eq(dict->key,word) ? true :
            dict_exists(dict->left,word) || dict_exists(dict->right,word));

    assert(invrep(dict));
    return exists;
}

unsigned int dict_length(dict_t dict){
    assert(invrep(dict));
    unsigned int length=0;
    if(dict != NULL){
        length = 1+dict_length(dict->left)+dict_length(dict->right);
    }
    return length;
}

static dict_t path(dict_t dict , dict_t pointed_node){
    if(dict->right != NULL){
        dict=dict->right;
        dict_t d=dict;
        while(d->left != NULL){
            d=d->left;
        }
        d->left=pointed_node;
        pointed_node=NULL;
        d=NULL;
    }else{
        dict=dict->left;
    }
    return dict;
}

dict_t dict_remove(dict_t dict, key_t word){
    assert(invrep(dict));
    if(dict_exists(dict,word)){
        dict_t pointed_node=NULL;
        dict_t node_delete=dict;
        if(key_eq(dict->key,word)){
            pointed_node=dict->left;
            dict=path(dict,pointed_node);
        }else{
            while(!key_eq(node_delete->key,word)){
                if(key_less(word,node_delete->key)){
                    node_delete=node_delete->left;
                }else{
                    node_delete=node_delete->right;
                }
            }
            pointed_node=node_delete->left;
            dict_t new_dict=node_delete;
            new_dict=path(new_dict,pointed_node);
            new_dict=NULL;
        }
        node_delete->left=node_delete->right=NULL;
        node_delete->key=key_destroy(node_delete->key);
        node_delete->value=value_destroy(node_delete->value);
        free(node_delete);
        node_delete=NULL;
        pointed_node=NULL;
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict){
    assert(invrep(dict));
    dict=dict_destroy(dict);
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump_ddot(FILE *file){
    fprintf(file, ":");
}

void dict_dump_jump(FILE *file){
    fprintf(file, "\n");
}

void dict_dump(dict_t dict, FILE *file){
    assert(invrep(dict) && file != NULL);
    if (dict != NULL) {
        dict_dump(dict->left,file);
        key_dump(dict->key,file);
        dict_dump_ddot(file);
        value_dump(dict->value,file);
        dict_dump_jump(file);
        dict_dump(dict->right,file);
    }
}

dict_t dict_destroy(dict_t dict){
    assert(invrep(dict));
    if(dict != NULL){
        dict->left=dict_destroy(dict->left);
        dict->right=dict_destroy(dict->right);
        dict->key=key_destroy(dict->key);
        dict->value=value_destroy(dict->value);
        free(dict);
        dict=NULL;
    }
    assert(dict == NULL);
    return dict;
}

