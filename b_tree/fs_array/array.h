#ifndef FIXED_SIZE_ARRAY
#define FIXED_SIZE_ARRAY

#include "../common_def.h"

typedef enum array_error{
    UNINITIALIZED = -2 ,
    INDEX_OUT_OF_BOUNDS = -3,
    FULL = -4,
    SUCCESS = 1
} ARRAY_ERROR;

typedef struct fixed_size_array {
    int *data;
    int filled;
    int default_key;
    int capacity;
} FS_ARRAY;

int 
create_array(FS_ARRAY *self, int capacity, int default_key);
/* 
    Returns : 1 <==> malloc(capacity * sizeof(int)) != NULL
              0 <==> malloc(capacity * sizeof(int)) == NULL
    Requires: capacity > 0
    Ensures : self->capacity     == capacity                AND 
              self->default_key  == default_key             AND
              self->filled       == 0                       AND   
              self->data         != NULL                    AND
              forall i : 0 <= i < self->capacity 
                        ==> self->data[i] == self->default_key
*/

int 
array_insert(FS_ARRAY *self, int elem, int at);
/* 
    Returns : 1 <==> check_init(self) AND check_bounds(self, at) AND check_not_full(self)
              0 <==> NOT(check_init(self) OR check_bounds(self) OR check_not_full(self))
    Requires: check_init(self) AND check_bounds(self) AND check_not_full(self)
    Ensures : self->filled == OLD(self->filled) + 1 AND   
              self->data[at] == elem AND
                forall i : 0 <= i < at           ==> old(self->data[i]) == self->data[i] AND
                           at < i < self->filled ==> old(self->data[i - 1]) == self->data[i]
*/

int
array_replace(FS_ARRAY *self, int at, int with);
/*
    Returns : 1                   <==> check_init(self) AND check_bounds(self, at)
              UNINITIALIZED       <==> NOT(check_init(self))
              INDEX_OUT_OF_BOUNDS <==> NOT(check_bounds(self, at) 
    Requires: check_init(self) AND check_bounds(self, at)
    Ensures : self->data[at] == with AND
              self->filled   == OLD(self->filled)  
*/

int
delete_at(FS_ARRAY *self, int at);

int 
copy_range(FS_ARRAY *to, FS_ARRAY *from, int start, int end);

void 
clean_array(FS_ARRAY *self);

void 
debug_array(FS_ARRAY *self);

void 
print_array_info(FS_ARRAY *self);

void 
print_hidden_array(FS_ARRAY *self);

void
print_array(FS_ARRAY *self);

#endif // FIXED_SIZE_ARRAY