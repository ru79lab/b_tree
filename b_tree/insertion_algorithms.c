#include "insertion_algorithms.h"

int
binary_search(FS_ARRAY *t, int k, int start, int end){
    _DEBUG("inserting %d, {start: %d, end: %d})\n", k, start, end);

    if(start == 0 && end == 0){
        return insert(t, k, 0);
    }

    int mid = (end - start) / 2;
    assert(mid < t->filled);

    int comp = t->data[mid]; 
    if(comp == k){
       return move_and_insert(t, k, mid + 1);
    } else if(comp < k && t->data[mid + 1] > k) {
        return move_and_insert(t, k, mid + 1);
    }
    else if (comp < k){
        return binary_search(t, k, 0, mid);
    } else {
        return binary_search(t, k, mid, t->filled);
    }
}