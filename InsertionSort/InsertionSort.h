#ifndef InsertionSort_h
#define InsertionSort_h

#include <stdbool.h>

//////////////////////////////////////////////////
typedef enum SORTOption {
    SORT_OPTION_NONE = 0,
    SORT_OPTION_ORDER = 0x0001,
    SORT_OPTION_RANGE = 0x0002,
    SORT_OPTION_PLACE = 0x0004,

    SORT_OPTION_ASCENDING_ORDER = 0x0000,
    SORT_OPTION_DESCENDING_ORDER = 0x0001,
    
    SORT_OPTION_RANGE_ALL = 0x0000,
    SORT_OPTION_RANGE_PARTIAL = 0x0002,
    
    SORT_OPTION_INPLACE = 0x0000,
    SORT_OPTION_NOT_INPLACE = 0x0004
    
} SORT_OPTION_e;

//////////////////////////////////////////////////
bool insertionSortSimple(int *array, int length, SORT_OPTION_e option);
bool insertionSort(int *array, int length, int leftIndex, int rightIndex, SORT_OPTION_e option);
void *insertionSortGeneral(void **array, int length, int (*comp)(void*, void*), int leftIndex, int rightIndex, SORT_OPTION_e option);

#endif
