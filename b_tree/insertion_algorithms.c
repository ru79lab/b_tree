#include "insertion_algorithms.h"

void
binary_search(FS_ARRAY *t, int k, int start, int end){
    int mid = (end - start) / 2;

    if(t->data[mid] == k){
       move_and_insert(t, k, mid + 1);
       return;
    } else if (t->data[mid] < k){
        return binary_search(t, k, 0, mid);
    } else {
         return binary_search(t, k, mid, t->filled);
    }
}