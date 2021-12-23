#include <stdio.h>
#include "b_tree.h"

int main(){
    TREE t;
    create(&t, 2, 0);

    printf("after create: h: %d; d: %d\n", t.height, t.default_key);

    for(int i = 0; i < t.capacity; i++){
         printf("pos %d : %d;",i, t.root->keys.data[0]);
    }

    printf("\n");

    print_b_tree(&t);

    destroy(&t);

    return 0;
}