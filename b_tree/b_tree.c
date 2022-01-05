#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

// A. creation and initialization
void 
create_b_tree (TREE *self, int min_size_of_key_array, int default_key){
    self->height = 0;
    self->root = create_node(min_size_of_key_array * 2, default_key);
}

NODE *
create_node(int min_size_of_key_array, int default_key){
    NODE *n = malloc(sizeof(NODE));
    n->left = NULL;
    n->right = NULL;

    init_keys(&(n->keys), min_size_of_key_array, default_key);
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
    if(self->height == 0){
        node_add(&(self->root->keys), key, &binary_search);
        self->height += 1;
        return;
    }

    if(self->root->keys.filled < self->root->keys.capacity){
        node_add(&(self->root->keys), key, &binary_search);
        return;
    } else {
        printf("UNIMPLEMENTED ADD\n");
        return;
    }
}

void  
node_add(FS_ARRAY *target, int key, int (*algorithm)(FS_ARRAY *self, int k, int start, int end)){
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
void 
print_b_tree(TREE *self){
    if(self->height == 0){
        print_empty_tree(self);
    } else if(self->height > 0){
        print_filled_tree(self);
    } else {
        printf("ERROR: [print_b_tree] undefined tree height: %i", self->height);
    }
}

void 
print_empty_tree(TREE *self) {
    printf("initialized tree: R [default_key: %i : capacity: %i] L [null] R [null]\n",self->root->keys.capacity, self->root->keys.default_key);
}

void 
print_filled_tree(TREE *self) {
    print_tree_info(self);
    print_tree(self->root, self->root->keys.capacity / 2 );
}

void 
print_tree_info(TREE *self){
    printf("filled tree: {height: %i, capacity: %i}\n",self->height, self->root->keys.capacity);
}

void 
print_tree(NODE *sub_tree,  int location){
    if(sub_tree->left == NULL && sub_tree->right == NULL){
        print_node(&(sub_tree->keys), location);
    } else {
        print_node(&(sub_tree->keys), location);
        print_tree(sub_tree->left, location--);
        print_tree(sub_tree->right, sub_tree->right->keys.filled + location++);
    }
}

void 
print_node(FS_ARRAY *key,  int location){
    for(int i = 0; i < location; i++)
        printf(" ");
    print_array(key);
    printf("\n");
}




