#ifndef B_TREE
#define B_TREE

typedef struct keys {
    int *data;
    int filled;
} KEYS;

typedef struct node {
    KEYS keys;
    KEYS *left;
    KEYS *right;
} NODE;

typedef struct b_tree
{
    NODE *root;
    int height;
    int default_key;
    int capacity;
} TREE;

void
create(TREE *instance_of_b_tree, int min_size_of_key_array, int default_key);

NODE *
create_node();

void 
init_keys(KEYS *keys, int capacity, int default_key);

void
destroy(TREE *instance);

void print_b_tree(TREE *instance);




#endif // B_TREE
