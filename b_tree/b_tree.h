#ifndef B_TREE
#define B_TREE

#include "array.h"
#include "insertion_algorithms.h"
#include "common_def.h"

typedef struct node {
    FS_ARRAY keys;
    struct node *left;
    struct node *right;
} NODE;

typedef struct b_tree
{
    NODE *root;
    int height;
    int default_key;
    int capacity;
} TREE;

// A. creation and initialization
void
create(TREE *self, int min_size_of_key_array, int default_key);

NODE *
create_node(TREE *self);

void 
init_keys(FS_ARRAY *keys, int capacity, int default_key);
/******************************************************************************************************************************/
// B. logic
void
add(TREE *self, int key);

void 
node_add(FS_ARRAY *target, int key, int (*algorithm)(FS_ARRAY *t, int k, int start, int end));
/******************************************************************************************************************************/
// C. cleaning
void
destroy(TREE *self);
/******************************************************************************************************************************/
// D. helpers
void 
print_b_tree(TREE *self);

void 
print_empty_tree(TREE *self);

void 
print_filled_tree(TREE *self);

void 
print_tree_info(TREE *self);

void 
print_tree(NODE *sub_tree,  int location);

void 
print_node(FS_ARRAY *key,  int location);

#endif // B_TREE
