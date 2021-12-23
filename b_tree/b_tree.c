#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"


void 
create (TREE *instance_of_b_tree, int min_size_of_key_array, int default_key){
    instance_of_b_tree->height = 0;
    instance_of_b_tree->default_key = default_key;
    instance_of_b_tree->capacity = min_size_of_key_array * 2;

    instance_of_b_tree->root = create_node(instance_of_b_tree);
}

NODE *
create_node(TREE *t){
    NODE *n = malloc(sizeof(NODE));
    n->left = NULL;
    n->right = NULL;

    init_keys(&(n->keys), t->capacity, t->default_key);

    return n;
}

void 
init_keys(KEYS *keys, int capacity, int default_key){
    keys->data = malloc(sizeof(int) * capacity);
    keys->filled = 0;
    
    int i = 0;
    for(; i < capacity; i++){
        keys->data[i] = default_key;
    }
}


void
destroy(TREE *instance){
    free(instance->root->keys.data);
    free(instance->root);
    free(instance);
}

void print_b_tree(TREE *instance){
    if(instance->height == 0){
        printf("initialized tree: R [%i : %i] L [null] R [null]",instance->default_key, instance->capacity);
    }
}

