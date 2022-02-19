#ifndef INSERTION_ALG
#define INSERTION_ALG

#include "array.h"
#include "common_def.h"

enum insertion_result {
    CONTAINED = -1
};

extern int 
binary_search(FS_ARRAY *t, int k, int start, int end);

#endif // INSERTION_ALG