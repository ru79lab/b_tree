#ifndef B_TREE
#define B_TREE

#include "array.h"
#include "insertion_algorithms.h"

typedef struct node {
    FS_ARRAY keys;
    FS_ARRAY *left;
    FS_ARRAY *right;
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
create_node();

void 
init_keys(FS_ARRAY *keys, int capacity, int default_key);
/******************************************************************************************************************************/
// B. logic
void
add(TREE *self, int key);

void 
node_add(FS_ARRAY *target, int key, void (*algorithm)(FS_ARRAY *t, int k));
/******************************************************************************************************************************/
// C. cleaning
void
destroy(TREE *self);
/******************************************************************************************************************************/
// D. helpers
void print_b_tree(TREE *self);

#endif // B_TREE
