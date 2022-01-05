#include <stdio.h>
#include "b_tree.h"
#include "array.h"
#include "insertion_algorithms.h"

#define MIN_KEY_ARRAY_SIZE 2
#define DEFAULT_KEY 0

int main(){
    printf("B_TREE TEST\n\n");
    TREE t;

    printf("testing tree creation: \n\n");
    create_b_tree(&t, MIN_KEY_ARRAY_SIZE, DEFAULT_KEY);
    print_b_tree(&t);
    FS_ARRAY root_data = t.root->keys;
    debug_array(&root_data);

    printf("testing add to empty tree: \n\n");
    add(&t, 5);
    print_b_tree(&t);

    printf("testing add to root smaller: \n");
    add(&t, 4);
    print_b_tree(&t);

    printf("testing add to root equal: \n");
    add(&t, 4);
    print_b_tree(&t);


    printf("testing add to root bigger: \n");

    add(&t, 7);
    print_b_tree(&t);

    printf("testing add full root: \n");

    add(&t, 7);
    print_b_tree(&t);

    destroy(&t);
    exit(0);

    return 0;
}