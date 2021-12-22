#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

TREE * 
new_b_tree (int min_size_of_key_array, int default_key){
    TREE *instance_of_b_tree = instance_of_b_tree = malloc(sizeof(TREE));
    instance_of_b_tree->height = 0;
    int c = min_size_of_key_array * 2;

    instance_of_b_tree->root = malloc(sizeof(NODE));
    instance_of_b_tree->root->left = NULL;
    instance_of_b_tree->root->right = NULL;

    instance_of_b_tree->root->keys.data = malloc(sizeof(int) * c);
    instance_of_b_tree->root->keys.capacity = c;
    instance_of_b_tree->root->keys.size = 0;
    
    int i = 0;
    for(; i < c; i++){
        instance_of_b_tree->root->keys.data[i] = default_key;
    }

    return instance_of_b_tree;
}

void
destroy(TREE *instance){
    free(instance->root->keys.data);
    free(instance->root);
    free(instance);
}

