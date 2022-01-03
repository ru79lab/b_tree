#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

// A. creation and initialization
void 
create (TREE *self, int min_size_of_key_array, int default_key){
    self->height = 0;
    self->default_key = default_key;
    self->capacity = min_size_of_key_array * 2;

    self->root = create_node(self);
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
init_keys(FS_ARRAY *keys, int capacity, int default_key){
    create_array(keys, capacity, default_key);
}
/******************************************************************************************************************************/
// B. logic
void 
add(TREE *self, int key){
    if(self->height == 1){
        node_add(&(self->root->keys), key, &binary_search);
    }
}

void 
node_add(FS_ARRAY *target, int key, void (*algorithm)(FS_ARRAY *t, int k, int start, int end)){
    (*algorithm)(target, key, 0, target->filled);
}
/******************************************************************************************************************************/
// C. cleaning
void
destroy(TREE *self){
    free(self->root->keys.data);
    free(self->root);
    free(self);
}
/******************************************************************************************************************************/
// D. helpers
void print_b_tree(TREE *self){
    if(self->height == 0){
        printf("initialized tree: R [%i : %i] L [null] R [null]",self->default_key, self->capacity);
    }
}

