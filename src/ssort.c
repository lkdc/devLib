#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include "compar.h"

#define LEN 32767
//Selection sort
void isort(void *base, size_t nmemb, size_t size,
            int (*compar)(const void *, const void *))
{
    size_t i,j;
    char *b = (char*)base;
    char *ai;
    char *aj;
    char *min;

    char *tmp;
    tmp = (char*)malloc(size);
    assert(tmp != NULL);

    for(i = 0; i < nmemb-1; i++){
        ai = (char*)(b + (i * size));
        min = ai;
        for(j = i + 1; j < nmemb; j++){
            aj = (char*)(b + (j * size));
            if (compar(aj, min) < 0){
                min = aj;
            }
        }
        if (compar(min, ai) < 0){
//          void *memcpy(void *dest, const void *src, size_t n);
            memcpy(tmp, min, size);
            memcpy(min, ai, size);
            memcpy(ai, tmp, size);
        }
    }
    free(tmp);
}

int main(int argc, char **argv)
{
    clock_t start_t, end_t, total_t;
    int array[LEN];
    srand(time(NULL));   // should only be called once
    for(size_t i=0;i<LEN;i++){
        array[i]=rand();
    }
    start_t = clock();
    isort(array, LEN, sizeof(int), &int_compar);
    end_t = clock();
    total_t = end_t - start_t;
    printf("\nClocks taken by CPU: %d\n", (int)total_t);
    return(0);
}
