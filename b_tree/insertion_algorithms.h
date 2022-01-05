#ifndef INSERTION_ALG
#define INSERTION_ALG

#include "array.h"
#include "common_def.h"

int 
binary_search(FS_ARRAY *t, int k, int start, int end);

bool 
approximated_lower_and_upper_bound(int k, int comp, int comp_neighbor);

bool
elem_is_upper_array_bound(int k, int comp, int comp_neighbor, int default_key);

bool
elem_is_lower_array_bound(int k, int comp, int mid);


#endif // INSERTION_ALG