#ifndef COMMON_DEFINITIONS
#define COMMON_DEFINITIONS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

//#define DEBUG_BUILD

#ifndef DEBUG_BUILD
    #define _DEBUG(fmt, ...) printf("[ %s %s %d ] " fmt "\n" , __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__) 
#else 
    #define _DEBUG(...)
#endif
 
#endif // COMMON_DEFINITIONS