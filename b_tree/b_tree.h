#ifndef B_TREE
#define B_TREE

typedef struct keys {
    int *data;
    int size;
    int capacity;
} KEYS;

typedef union node {
    KEYS keys;
    KEYS *left;
    KEYS *right;
} NODE;

typedef union b_tree
{
    NODE *root;
    int height;
} TREE;

TREE * 
new_b_tree(int min_size_of_key_array, int default_key);

void
destroy(TREE *instance);




#endif // B_TREE
