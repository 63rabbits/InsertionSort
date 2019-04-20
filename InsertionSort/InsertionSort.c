#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "InsertionSort.h"

//////////////////////////////////////////////////
//  public
bool insertionSortSimple(int *array, int length, SORT_OPTION_e option) {
    // Block illegal parameters.
    if (array == NULL) return false;
    if (length <= 0) return false;
    if ((SORT_OPTION_RANGE_PARTIAL & option) != 0) return false;
    if ((SORT_OPTION_INPLACE & option) != 0) return false;
    
    for (int i=1; i<length; i++) {
        int value = array[i];
        int j = i;
        if (SORT_OPTION_DESCENDING_ORDER & option) {
            while ((j > 0) && (array[j-1] < value)) {
                array[j] = array[j-1];
                j--;
            }
        }
        else {
            while ((j > 0) && (array[j-1] > value)) {
                array[j] = array[j-1];
                j--;
            }
        }
        array[j] = value;
    }
    
    return true;
}

bool insertionSort(int *array, int length, int leftIndex, int rightIndex, SORT_OPTION_e option) {
    // Block illegal parameters.
    if (array == NULL) return false;
    if (length <= 0) return false;
    if ((SORT_OPTION_INPLACE & option) != 0) return false;
    if (SORT_OPTION_RANGE_PARTIAL & option) {
        if ((leftIndex < 0) || (leftIndex >= length)) return false;
        if ((rightIndex < 0) || (leftIndex >= length)) return false;
        if (leftIndex > rightIndex) return false;
    }
    else {
        leftIndex = 0;
        rightIndex = length-1;
    }
    
    if (leftIndex == rightIndex) return true;   // There is no need to sort.
    
    for (int i=leftIndex+1; i<=rightIndex; i++) {
        int value = array[i];
        int j = i;
        if (SORT_OPTION_DESCENDING_ORDER & option) {
            while ((j > leftIndex) && (array[j-1] < value)) {
                array[j] = array[j-1];
                j--;
            }
        }
        else {
            while ((j > leftIndex) && (array[j-1] > value)) {
                array[j] = array[j-1];
                j--;
            }
        }
        array[j] = value;
    }
    
    return true;
}

void *insertionSortGeneral(void **array, int length, int (*comp)(void*, void*), int leftIndex, int rightIndex, SORT_OPTION_e option) {
    // Block illegal parameters.
    if (array == NULL) return NULL;
    if (length <= 0) return false;
    if (SORT_OPTION_RANGE_PARTIAL & option) {
        if ((leftIndex < 0) || (leftIndex >= length)) return NULL;
        if ((rightIndex < 0) || (leftIndex >= length)) return NULL;
        if (leftIndex > rightIndex) return NULL;
    }
    else {
        leftIndex = 0;
        rightIndex = length-1;
    }
    
    if (SORT_OPTION_INPLACE & option) {
        // nop
    }
    else {
        // duplicate an array.
        void *temp = malloc(sizeof(void*) * length);
        if (temp == NULL) return NULL;
        memcpy(temp, array, sizeof(void*) * length);
        array = temp;
    }
    
    if (leftIndex == rightIndex) return array;   // There is no need to sort.
    
    for (int i=leftIndex+1; i<=rightIndex; i++) {
        int j = i;
        void *element = array[i];
        if (SORT_OPTION_DESCENDING_ORDER & option) {
            while ((j > leftIndex) && (comp(array[j-1], element) < 0)) {
                array[j] = array[j-1];
                j--;
            }
        }
        else {
            while ((j > leftIndex) && (comp(array[j-1], element) > 0)) {
                array[j] = array[j-1];
                j--;
            }
        }
        array[j] = element;
    }
    
    return array;
}
