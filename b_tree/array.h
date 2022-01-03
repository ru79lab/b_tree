#ifndef FIXED_SIZE_ARRAY
#define FIXED_SIZE_ARRAY

enum array_error{
    UNITIALIZED,
    INDEX_OUT_OF_BOUNDS
};

typedef struct fixed_size_array {
    int *data;
    int length;
    int filled;
} FS_ARRAY;

void 
create_array(FS_ARRAY *self, int length, int default_elem);

int 
insert(FS_ARRAY *self, int elem, int at);

int 
move_and_insert(FS_ARRAY *self, int elem, int at);

#endif // FIXED_SIZE_ARRAY