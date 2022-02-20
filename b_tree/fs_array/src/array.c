#include <stdlib.h>
#include <stdio.h>
#include "array.h"

// 0. private
int 
insert(FS_ARRAY *self, int elem, int at);

int
move_and_insert(FS_ARRAY *self, int elem, int at);

bool
check_init( FS_ARRAY *self);

bool
check_bounds(FS_ARRAY *self, int at);

bool
range_check(FS_ARRAY *self, int start, int end);

bool
check_not_full(FS_ARRAY *self);

bool
check_not_empty(FS_ARRAY *self);


int  
create_array(FS_ARRAY *self, int capacity, int default_key) {
    if (capacity <= 0) 
        return NEGATIVE_CAPACITY;

    self->data = malloc(sizeof(int) * capacity);
    if (self->data == NULL) 
        return 0;

    self->filled = 0;
    self->capacity = capacity;
    self->default_key = default_key;

    for (int i = 0;  i < capacity; i++)
        self->data[i] = default_key;
    

    return 1;
}

int 
array_copy(FS_ARRAY *self, FS_ARRAY *to) {
    int c = create_array(to, self->capacity, self->default_key);

    if (c != SUCCESS)
        return c;

    int filled = self->filled;
    to->filled = filled; 

    for (int i = 0;  i < filled; i++)
        to->data[i] = self->data[i];

    return SUCCESS;
}


int 
array_insert(FS_ARRAY *self, int elem, int at){
    if (!check_init(self))
        return UNINITIALIZED;

    if(!check_bounds(self, at))
        return INDEX_OUT_OF_BOUNDS;
    
    if (!check_not_full(self))
        return FULL;

    if(at == self->filled)
        return insert(self, elem, at);

    else 
        return move_and_insert(self, elem, at);
}

int
array_replace(FS_ARRAY *self, int at, int with){
    if (!check_init(self))
        return UNINITIALIZED;

    if(!check_bounds(self, at))
        return INDEX_OUT_OF_BOUNDS;

    self->filled -= 1;
    return insert(self, with, at);
}


int 
insert(FS_ARRAY *self, int elem, int at){
    /*printf("array before insert: \n");
    debug_array(self);
    printf("\n");*/

    _DEBUG("insert data: {elem: %i, at: %d}\n", elem, at);

    self->data[at] = elem;
    self->filled += 1;

    /*printf("array after insert: \n");
    debug_array(self);
    printf("\n");*/
    return 1;
}

int 
move_and_insert(FS_ARRAY *self, int elem, int at){
    // moving each element one position to the right without overwritting an element
    for(int i = self->filled; i > at; i--){
        _DEBUG("placing %i for %i to %i\n", self->data[i - 1], self->data[i], i);
        self->data[i] = self->data[i - 1];
        _DEBUG("(%i : %i, %i : %i)\n", self->data[i], i, self->data[i - 1], i - 1);
    }

    insert(self, elem, at);
    return 1;
}

int
array_delete_at(FS_ARRAY *self, int at) {
    _DEBUG("removing elem at %d", at);

    if (! check_init(self))
        return UNINITIALIZED;

    if(! check_bounds(self, at)){
        return INDEX_OUT_OF_BOUNDS;
    } 

    if(! check_not_empty(self))
        return EMPTY;

    for (int i = at; i < self->filled; i++) {
        if (i + 1 == self->filled)
            self->data[i] = self->default_key;
        else 
            self->data[i] = self->data[i + 1];
    }

    self->filled -= 1;

    return SUCCESS;
}

int 
copy_range(FS_ARRAY *to, FS_ARRAY *from, int start, int end){
    if(to == NULL || from == NULL){
        return UNINITIALIZED;
    }

    if(!range_check(to, start, end) || !range_check(from, start, end)){
        return INDEX_OUT_OF_BOUNDS;
    }

    for(int i = start; i < end; i++){
        to->data[i] = from->data[i];
    }

    return SUCCESS;
}

bool 
array_equals(FS_ARRAY *self, FS_ARRAY *other) {
    if (NULL == self || NULL == other) 
        return false;
 
    if (NULL == self->data) 
        return false;

    if (NULL == other->data) 
        return false;

    if (self->capacity != other->capacity)
        return false;

    if (self->filled != other->filled)
        return false;

    if (self->default_key != other->default_key)
        return false;

    for (int i = 0; i < self->filled; i++) {
        if(self->data[i] != other->data[i])
            return false;
    }

    return true;
}

void 
array_clean(FS_ARRAY *self) {
    free(self->data);
}


void
print_array(FS_ARRAY *self){
    // repr: [ data[0], data[1], ... , data[self->filled - 1] ]
    if(self->filled > 0){

        printf("[ ");
        
        for (int i = 0; i < self->filled - 1; i++){
            printf("%i, ", self->data[i]);
        }

        printf("%i ]", self->data[self->filled - 1]);
        printf("\n");
    }
}

void 
debug_array(FS_ARRAY *self){
    print_array_info(self);
    print_hidden_array(self);
}

void 
print_hidden_array(FS_ARRAY *self){
    printf("[ ");
    
    for (int i = 0; i < self->capacity - 1; i++){
        printf("%i, ", self->data[i]);
    }

    printf("%i ]", self->data[self->capacity - 1]);
    printf("\n");
}

void 
print_array_info(FS_ARRAY *self){
    printf("FIXED_SIZE_ARRAY: {capacity: %d, filled: %d, default_key: %d}\n", self->capacity, self->filled, self->default_key);
}


/* checker */


bool 
check_init(FS_ARRAY *self) {
    if(self == NULL){
        _DEBUG("WARNING: unitialized fs_array %p", self);
        return 0;
    } 

    if (self->data == NULL) {
        _DEBUG("WARNING: unitialized data of fs_array %p", self);
        return 0;
    }

    return 1;
}

bool 
check_bounds(FS_ARRAY *self, int at){
    if (at > self->filled) {
        _DEBUG("WARNING: index %d of out bounds of fs_array %p", at, self);
        return 0;
    }

    return 1;
}

bool 
check_not_full(FS_ARRAY *self) {
    if (self->filled == self->capacity) {
        _DEBUG("WARNING: fs_array %p is full", self);
        return 0;
    }

    return 1;
}

bool
check_not_empty(FS_ARRAY *self) {
    if(self->filled == 0) {
        _DEBUG("WARNING: fs_array %p is empty", self);
        return 0;
    }

    return 1;
}

bool
range_check(FS_ARRAY *self, int start, int end){
    return start >= 0 && self->filled > start && self->filled >= end;
}