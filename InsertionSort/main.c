#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include "InsertionSort.h"

//////////////////////////////////////////////////
typedef struct Element {
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);
int comp(void *elementA, void *elementB);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int testCount = 10;
    int numElement = 30;
    
    int beginOfPartial = 10;
    int endOfPartial = 15;
    
    int array[numElement];
    void *parray[numElement];
    srand((unsigned) time(NULL));
    
    for (int testNo=0; testNo<testCount; testNo++) {
        printf("\n=== [Test #%d] === ", testNo+1);
        switch (testNo) {
            case 0:
                printf("Simple Sort\n");
            {
                printf("\n*** make array ***\n");
                for (int i=0; i<numElement; i++) {
                    array[i] = rand()%100;
                    printf("%2d, ", array[i]);
                }
                printf("\n");
                
                printf("\n*** insetion sort ***\n");
                bool check = insertionSortSimple(array, numElement, SORT_OPTION_ASCENDING_ORDER);
                if (!check) {
                    printf("error [%s] : could not sort.\n", __func__);
                    break;
                }
                for (int i=0; i<numElement; i++) {
                    printf("%2d, ", array[i]);
                }
                printf("\n");
            }
                break;
            case 1:
                printf("Partially Sort\n");
                printf("begin index = %d\n", beginOfPartial);
                printf("end   index = %d\n", endOfPartial);
            {
                printf("\n*** make array ***\n");
                for (int i=0; i<numElement; i++) {
                    if (i == beginOfPartial) printf("[ ");
                    array[i] = rand()%100;
                    printf("%2d, ", array[i]);
                    if (i == endOfPartial) printf("] ");
                }
                printf("\n");
                
                printf("\n*** insetion sort (partial) ***\n");
                bool check = insertionSort(array, numElement, beginOfPartial, endOfPartial, SORT_OPTION_RANGE_PARTIAL);
                if (!check) {
                    printf("error [%s] : could not sort.\n", __func__);
                    break;
                }
                for (int i=0; i<numElement; i++) {
                    if (i == beginOfPartial) printf("[ ");
                    printf("%2d, ", array[i]);
                    if (i == endOfPartial) printf("] ");
                }
                printf("\n");
            }
                break;
            case 2:
                printf("General Sort\n");
            {
                printf("\n*** make array ***\n");
                for (int i=0; i<numElement; i++) {
                    int value = rand()%100;
                    Element_t *element = createElement(value);
                    parray[i] = element;
                    printf("%2d, ", value);
                }
                printf("\n");
                
                printf("\n*** insetion sort ***\n");
                void **newArray = insertionSortGeneral(parray, numElement, comp, 0, 0, SORT_OPTION_ASCENDING_ORDER);
                if (newArray == NULL) {
                    printf("error [%s] : could not sort.\n", __func__);
                    break;
                }
                for (int i=0; i<numElement; i++) {
                    printf("%2d, ", ((Element_t*)newArray[i])->value);
                    free(newArray[i]);
                }
                free(newArray);
                printf("\n");
            }
                break;
            case 3:
                printf("Partially General Sort\n");
                printf("begin index = %d\n", beginOfPartial);
                printf("end   index = %d\n", endOfPartial);
            {
                printf("\n*** make array ***\n");
                for (int i=0; i<numElement; i++) {
                    if (i == beginOfPartial) printf("[ ");
                    int value = rand()%100;
                    Element_t *element = createElement(value);
                    parray[i] = element;
                    printf("%2d, ", value);
                    if (i == endOfPartial) printf("] ");
                }
                printf("\n");
                
                printf("\n*** insetion sort (partial) ***\n");
                void **newArray = insertionSortGeneral(parray, numElement, comp, beginOfPartial, endOfPartial, SORT_OPTION_DESCENDING_ORDER | SORT_OPTION_RANGE_PARTIAL);
                if (newArray == NULL) {
                    printf("error [%s] : could not sort.\n", __func__);
                    break;
                }
                for (int i=0; i<numElement; i++) {
                    if (i == beginOfPartial) printf("[ ");
                    printf("%2d, ", ((Element_t*)newArray[i])->value);
                    if (i == endOfPartial) printf("] ");
                    free(newArray[i]);
                }
                free(newArray);
                printf("\n");
            }
                // *************************************
                testNo = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
    }
}

Element_t *createElement(int value) {
    Element_t *element = malloc(sizeof(Element_t));
    if (element == NULL) return NULL;
    element->value = value;
    return element;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}

int comp(void *elementA, void *elementB) {
    Element_t *element1 = elementA;
    Element_t *element2 = elementB;
    return element1->value - element2->value;
}
