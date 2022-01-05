#ifndef COMMON_DEFINITIONS
#define COMMON_DEFINITIONS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG_BUILD
    #define _DEBUG(fmt, args...) printf("[ %s %s %d ] "fmt, __FILE__, __FUNCTION__, __LINE__, args) 
#else 
    #define _DEBUG(...)
#endif
 
#endif // COMMON_DEFINITIONS