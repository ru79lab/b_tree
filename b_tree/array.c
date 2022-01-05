#include <stdlib.h>
#include <stdio.h>
#include "array.h"

void 
create_array(FS_ARRAY *self, int length, int default_key){
    self->data = malloc(sizeof(int) * length);
    self->filled = 0;
    self->length = length;

    for (int i = 0;  i < length; i++){
        self->data[i] = default_key;
    }
}

int 
insert(FS_ARRAY *self, int elem, int at){
    if(self == NULL || self->data == NULL){
        return UNITIALIZED;
    }

    if(at >= self->length){
        return INDEX_OUT_OF_BOUNDS;
    } 

    self->data[at] = elem;
    self->filled += 1;
    return 1;
}

int 
move_and_insert(FS_ARRAY *self, int elem, int at){
    if(self == NULL || self->data == NULL){
        return UNITIALIZED;
    }

    if(self->filled + 1 == self->length - 1){
        return INDEX_OUT_OF_BOUNDS;
    }

    for(int i = at + 1; i + 1 < self->filled + 1; i++){
            self[i + 1] = self[i];
    }

    self->data[at] = elem;
    self->filled += 1;
    return 1;
}

void
print_array(FS_ARRAY *self){
    // repr: [ data[0], data[1], ... , data[self->filled - 1] ]
    printf("[ ");
    
    for (int i = 1; i < self->filled - 1; i++){
        printf("%c, ", self->data[i]);
    }

    printf("%i ]", self->data[self->filled - 1]);
}