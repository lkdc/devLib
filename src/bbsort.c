#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>

#define LEN 32767

int int_compar(const void *p1, const void *p2)
{
    if (*(int*)p1 > *(int*)p2)
        return 1;
    else if (*(int*)p1 < *(int*)p2)
        return -1;
    else
        return 0;
}

void swap(void *v1, void *v2, size_t size)
{
    void *v;
    v = malloc(size);
    assert(v != NULL);
//  void *memcpy(void *dest, const void *src, size_t n);
    memcpy(v, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, v, size);
    free(v);
}

//Bubble sort
void bbsort(void *base, size_t nmemb, size_t size,
            int (*compar)(const void *, const void *))
{
    size_t i,j;
    int swapped;
    char *b = (char*)base;
    char *crt, *next;
    for(i = 0; i < nmemb - 1; i++){
        swapped = 0;
        for(j = 0; j < nmemb - i - 1; j++){
            crt = (char*)(b + j * size);
            next = crt + size;
            if (compar(crt, next) >= 0){
                swap(next, crt, size);
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
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
