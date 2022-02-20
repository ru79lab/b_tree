#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/array.h"


static FS_ARRAY a;

void prepare_array(void);

int
init_suite_1(void) {
    create_array(&a, 4, -1);
    return 0;
}


int
clean_suite_1(void) {
    array_clean(&a);
    return 0;
}

void 
test_create(void) {
    CU_ASSERT(a.capacity == 4);
    CU_ASSERT(a.default_key == -1);
    CU_ASSERT(a.filled == 0);
    CU_ASSERT(a.data != NULL);

    int check = 1;
    for (int i = 0; i < a.capacity; i++) {
        if (a.data[i] != a.default_key)
            check = 0;
    }

    CU_ASSERT(check == 1);
}

void test_array_equals(void) {
    prepare_array();
    FS_ARRAY b;

    create_array(&b, a.capacity, a.default_key);
    b.filled = a.filled;
    for(int i = 0; i < a.filled; i++)
        b.data[i] = a.data[i];

    CU_ASSERT(array_equals(&a, &b));

    array_clean(&b);
}

void 
test_array_copy(void) {
    prepare_array();

    FS_ARRAY copy_a;
    int check = array_copy(&a, &copy_a);

    if(check != SUCCESS) 
        CU_ASSERT(check == 0 || check == NEGATIVE_CAPACITY);

    CU_ASSERT(array_equals(&a, &copy_a));

    array_clean(&copy_a);
}

void 
test_insert (void) {
    int check1 = array_insert(&a, 3, 1);
    CU_ASSERT(check1 == INDEX_OUT_OF_BOUNDS);

    array_insert(&a, 3, 0);
    CU_ASSERT(a.data[0] == 3);

    array_insert(&a, 2, 1);
    CU_ASSERT(a.data[1] == 2);
    CU_ASSERT(a.data[0] == 3);

    array_insert(&a, 1, 1);
    CU_ASSERT(a.data[2] == 2);
    CU_ASSERT(a.data[1] == 1);
    CU_ASSERT(a.data[0] == 3);

    array_insert(&a, 4, 0);
    CU_ASSERT(a.data[0] == 4);
    CU_ASSERT(a.data[1] == 3);
    CU_ASSERT(a.data[2] == 1);
    CU_ASSERT(a.data[3] == 2);

    int check2 = array_insert(&a, 5, 0);
    CU_ASSERT(a.data[0] == 4);
    CU_ASSERT(a.data[1] == 3);
    CU_ASSERT(a.data[2] == 1);
    CU_ASSERT(a.data[3] == 2);

    CU_ASSERT(check2 == FULL);
}

void 
test_replace(void) {
    prepare_array();

    int old_filled = a.filled;
    int replace_at = 0, replace_with = 10;

    array_replace(&a, replace_at, replace_with);

    CU_ASSERT(a.data[replace_at] == replace_with);
    CU_ASSERT(a.filled == old_filled);
}

void 
test_replace_at_OUT_OF_BOUNDS(void) {
    prepare_array();

    int old_filled = a.filled;
    int replace_at = old_filled + 1, replace_with = 10;
    int old_value_at = a.data[replace_at];

    int check = array_replace(&a, replace_at, replace_with);

    CU_ASSERT(check == INDEX_OUT_OF_BOUNDS);
    CU_ASSERT(a.data[replace_at] == old_value_at);
    CU_ASSERT(a.filled == old_filled);
} 

void 
test_array_delete(void) {
    prepare_array();

    int old_filled = a.filled;
    int at = 1;

    FS_ARRAY copy_a;
    array_copy(&a, &copy_a); 
    array_delete_at(&a, at);

    CU_ASSERT(a.filled = old_filled - 1);

    for (int i = 0; i < a.filled; i++) {
        if(i < at) {
            CU_ASSERT(a.data[i] == copy_a.data[i]);
        }
        else {
            CU_ASSERT(a.data[i] == copy_a.data[i+1]);    
        }
    }
}

void 
test_array_delete_filled_bound(void) {
    prepare_array();

    int old_filled = a.filled;
    int at = old_filled - 1;

    FS_ARRAY copy_a;
    array_copy(&a, &copy_a); 
    array_delete_at(&a, at);

    CU_ASSERT(a.filled = old_filled - 1);

    for (int i = 0; i < a.filled; i++) {
        if(i < at) {
            CU_ASSERT(a.data[i] == copy_a.data[i]);
        }
        else {
            CU_ASSERT(a.data[i] == copy_a.default_key);    
        }
    }
}

void prepare_array(void) {
    array_insert(&a, 3, 0);
    array_insert(&a, 2, 1);
    array_insert(&a, 1, 1);
    array_insert(&a, 4, 0);
}


int 
main(){
    CU_pSuite pSuite = NULL;

    /* init the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", &init_suite_1, &clean_suite_1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add tests to the suite */
     if (
         (NULL == CU_add_test(pSuite, "test of array_create", &test_create)) ||
         (NULL == CU_add_test(pSuite, "test of array_insert", &test_insert)) ||
         (NULL == CU_add_test(pSuite, "test of array_replace", &test_replace))||
         (NULL == CU_add_test(pSuite, "test of test_replace_at_OUT_OF_BOUNDS", &test_replace_at_OUT_OF_BOUNDS)) ||
         (NULL == CU_add_test(pSuite, "test of test_array_equals", &test_array_equals)) || 
         (NULL == CU_add_test(pSuite, "test of test_array_copy", &test_array_copy)) ||
         (NULL == CU_add_test(pSuite, "test of test_array_delete", &test_array_delete)) ||
         (NULL == CU_add_test(pSuite, "test of test_array_delete_filled_bound", &test_array_delete_filled_bound)) 
        ) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error(); 
}






