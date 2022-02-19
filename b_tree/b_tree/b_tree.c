#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "b_tree.h"

// 0. private 
void
insert_to_tree(NODE *node, int key, TREE *self);

NODE *
identify_child_with_range_for_key(NODE **children, int n_children, int key);

void
tree_growth(NODE *node, int key, TREE *self);

int 
identify_median(FS_ARRAY *keys, int key);

// A. creation and initialization
void 
create_b_tree (TREE *self, int min_size_of_key_array, int default_key){
    self->height = 0;
    self->root = create_node(min_size_of_key_array * 2, default_key, NULL);
}

NODE *
create_node(int min_size_of_key_array, int default_key, NODE *parent){
    NODE *n = malloc(sizeof(NODE));

    n->children = NULL;
    n->n_children = 0;

    n->parent=parent;

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

    insert_to_tree(self->root, key, self);
}

void
insert_to_tree(NODE *node, int key, TREE *self){
    if(node->keys.filled < node->keys.capacity){
        node_add(&(node->keys), key, &binary_search);
        return;
    } else if (node->n_children == 0){
        // tree needs to grow
        tree_growth(node, key, self);

    } else {
        NODE *next = identify_child_with_range_for_key(node->children, node->n_children, key);
        insert_to_tree(next, key, self);
    }
}

int  
node_add(FS_ARRAY *target, int key, int (*algorithm)(FS_ARRAY *self, int k, int start, int end)){
    int index = (*algorithm)(target, key, 0, target->filled);
    if(index == CONTAINED){
        return CONTAINED;
    }
    return array_insert(target, key, index); 
}

void
tree_growth(NODE *node, int key, TREE *self){
    int median = identify_median(&(node->keys), key);
    if(node->parent == NULL){
        NODE *new_root = create_node(node->keys.capacity, node->keys.default_key, NULL);
        node->parent = new_root;
        self->root = new_root;
        self->height += 1;

        array_insert(&(new_root->keys), median, 0);
        if(median != key){
            array_replace(&(node->keys), (int)node->keys.filled / 2, key);
        }

        new_root->children = malloc(sizeof(NODE) * 2);
        new_root->children[0] = create_node(node->keys.capacity, node->keys.default_key, new_root);
        copy_range(new_root->children[0], &(node->keys), 0, node->keys.filled);
        new_root->children[0]->keys.filled = (int) node->keys.filled / 2;

        // todo: move range in node->keys
        // set filled to (int) node->keys.filled / 2
        // set new_root->children[1] = node
    }
    // todo: handle 
}

int 
identify_median(FS_ARRAY *keys, int key){
    if((int)(keys->filled / 2 ) == binary_search(keys, key, 0, keys->filled)){
        // => key would be the new median if inserted
        return key;
    } else {
        // => key would be smaller or larger than median as mid position
        return keys->data[(int)keys->filled / 2];
    }
}

NODE *
identify_child_with_range_for_key(NODE **children, int n_children, int key){
    for(int i = 0; i < n_children; i++) {
        if(range_fits(&(children[i]->keys), key))
            return children[i];
    }
}

bool
range_fits(FS_ARRAY *range, int key){
    return range->data[0] <= key && range->data[range->filled] >= key;
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
    if(sub_tree->children == NULL){
        print_node(&(sub_tree->keys), location);
    } else {
        print_node(&(sub_tree->keys), location);
        for(int i = 0; i < sub_tree->n_children; i++) {
            print_tree(sub_tree->children[i], 0);
        }
    }
}

void 
print_node(FS_ARRAY *key,  int location){
    for(int i = 0; i < location; i++)
        printf(" ");
    print_array(key);
    printf("\n");
}




