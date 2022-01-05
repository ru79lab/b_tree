#include <stdlib.h>
#include <stdio.h>
#include "array.h"

void 
create_array(FS_ARRAY *self, int capacity, int default_key){
    self->data = malloc(sizeof(int) * capacity);
    self->filled = 0;
    self->capacity = capacity;
    self->default_key = default_key;

    for (int i = 0;  i < capacity; i++){
        self->data[i] = default_key;
    }
}

int 
insert(FS_ARRAY *self, int elem, int at){
    if(self == NULL || self->data == NULL){
        return UNITIALIZED;
    }

    if(at >= self->capacity){
        return INDEX_OUT_OF_BOUNDS;
    } 

    printf("array before insert: \n");
    debug_array(self);
    printf("\n");

    _DEBUG("insert data: {elem: %d, at: %d}\n", elem, at);

    self->data[at] = elem;
    self->filled += 1;

    printf("array after insert: \n");
    debug_array(self);
    printf("\n");
    return 1;
}

int 
move_and_insert(FS_ARRAY *self, int elem, int at){
    if(self == NULL || self->data == NULL){
        return UNITIALIZED;
    }

    if(self->filled + 1 == self->capacity){
        return INDEX_OUT_OF_BOUNDS;
    }

    printf("array before move and insert: \n");
    debug_array(self);
    printf("\n");

    _DEBUG("insert data: {elem: %d, at: %d}\n", elem, at);

    // moving each element one position to the right without overwritting an element
    for(int i = self->filled; i > at; i--){
        _DEBUG("placing %i for %i to %i\n", self->data[i - 1], self->data[i], i);
        self->data[i] = self->data[i - 1];
        _DEBUG("(%i : %i, %i : %i)\n", self->data[i], i, self->data[i - 1], i - 1);
    }

    // place element to insert at at and increase filled
    _DEBUG("placing elem %i to: %i; current: %i\n", elem, at, self->data[at]);
    self->data[at] = elem;
    self->filled += 1;

    printf("array after move and insert: \n");
    debug_array(self);
    printf("\n");

    return 1;
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