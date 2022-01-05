#ifndef FIXED_SIZE_ARRAY
#define FIXED_SIZE_ARRAY

#include "common_def.h"

enum array_error{
    UNITIALIZED,
    INDEX_OUT_OF_BOUNDS
};

typedef struct fixed_size_array {
    int *data;
    int filled;
    int default_key;
    int capacity;
} FS_ARRAY;

void 
create_array(FS_ARRAY *self, int default_elem, int capacity);

int 
insert(FS_ARRAY *self, int elem, int at);

int 
move_and_insert(FS_ARRAY *self, int elem, int at);

void 
debug_array(FS_ARRAY *self);

void 
print_array_info(FS_ARRAY *self);

void 
print_hidden_array(FS_ARRAY *self);

void
print_array(FS_ARRAY *self);

#endif // FIXED_SIZE_ARRAY