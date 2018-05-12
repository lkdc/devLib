#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include "compar.h"

#define LEN 32767

//Bubble sort
void bbsort(void *base, size_t nmemb, size_t size,
            int (*compar)(const void *, const void *))
{
    size_t i,j;
    int swapped;
    char *b = (char*)base;
    char *tmp;
    tmp = (char*)malloc(size);
    assert(tmp != NULL);
    char *crt, *next;
    for(i = 0; i < nmemb - 1; i++){
        swapped = 0;
        for(j = 0; j < nmemb - i - 1; j++){
            crt = (char*)(b + j * size);
            next = crt + size;
            if (compar(crt, next) >= 0){
//               void *memcpy(void *dest, const void *src, size_t n);
               memcpy(tmp, crt, size);
               memcpy(crt, next, size);
               memcpy(next, tmp, size);
               swapped = 1;
           }
        }
        if (!swapped) break;
    }
    free(tmp);
}

int main(int argc, char **argv)
{
    clock_t start_t, end_t, total_t;
    int array[LEN];
    srand(time(NULL));   // should only be called once
    for(size_t i = 0; i < LEN; i++){
        array[i]=rand();
    }
    start_t = clock();
    bbsort(array, LEN, sizeof(int), &int_compar);
    end_t = clock();
    total_t = end_t - start_t;
    printf("\nClocks taken by CPU: %d\n", (int)total_t);
    return(0);
}
