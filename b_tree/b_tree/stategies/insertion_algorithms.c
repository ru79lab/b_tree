#include "insertion_algorithms.h"

bool 
approximated_lower_and_upper_bound(int k, int comp, int comp_neighbor);

bool
elem_is_upper_array_bound(int k, int comp, int comp_neighbor, int default_key);

bool
elem_is_lower_array_bound(int k, int comp, int mid);

int 
evaluate_insert(int return_value);

int
binary_search(FS_ARRAY *t, int k, int start, int end){
    _DEBUG("inserting %d, {start: %d, end: %d})\n", k, start, end);
    printf("\n");

    if(start == 0 && end == 0){
        return 0;
    }

    int mid = start + (end - start) / 2;
    assert(mid < t->filled);

    printf("mid: %d\n", mid);

    int comp = t->data[mid]; 
    if(k == comp){
        return CONTAINED;
    }
    else if(approximated_lower_and_upper_bound(k, comp, t->data[mid + 1])) {
        _DEBUG("case FOUND beetween {comp: %d, k: %d, comp + 1: %d}\n", comp, k, t->data[mid + 1]);
        return mid;
    } 
    else if(elem_is_upper_array_bound(k, comp, t->data[mid + 1], t->default_key)) {
        _DEBUG("case FOUND as upper bound {comp: %d, k: %d, comp + 1: %d}\n", comp, k, t->data[mid + 1]);
        return mid + 1;
    }  
    else if(elem_is_lower_array_bound(k, comp, mid)){
        _DEBUG("case FOUND as lower bound {comp: %d, k: %d, mid: %d}\n", comp, k, mid);
        return mid;
    } 
    else if (k <= comp){
        _DEBUG("case SMALLER {k:%d <= comp:%d}\n", k, comp);
        return binary_search(t, k, 0, mid);
    } else {
        _DEBUG("case LARGER {comp:%d < k:%d}\n", comp, k);
        return binary_search(t, k, mid + 1, t->filled);
    }
}


bool 
approximated_lower_and_upper_bound(int k, int comp, int comp_neighbor){
    return comp <= k && comp_neighbor > k;
}

bool
elem_is_upper_array_bound(int k, int comp, int comp_neighbor, int default_key){
    return (comp <= k && comp_neighbor == default_key);
}

bool
elem_is_lower_array_bound(int k, int comp, int mid){
    return (k <= comp && 0 == mid);
}

