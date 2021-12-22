#include <stdio.h>
#include "b_tree.h"

int main(){
    TREE t = *(new_b_tree(2, 0));

    for(int i = 0; i < t.root->keys.capacity; i++){
         printf("pos %d : %d;",i, t.root->keys.data[0]);
    }

    destroy(&t);

    return 0;
}