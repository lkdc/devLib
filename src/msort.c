#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include "util.h"

#define LEN 32767
//Merge sort
void array_merge(int array[], int begin, int end)
{
    int mid = begin + (end - begin) / 2;
    int i = begin;
    int j = mid + 1;

    int *p;
    int k = 0;
    p = (int*)malloc((end - begin + 1)*sizeof(int));
    assert(p != NULL);

    while((i <= mid) && (j <= end)){
        if(array[i] < array[j]){
            p[k] = array[i];
            i++;
            k++;
        } else{
            p[k] = array[j];
            j++;
            k++;
        }
    }
    while(i <= mid){
        p[k] = array[i];
        i++;
        k++;
    }
    while(j <= end){
        p[k] = array[j];
        j++;
        k++;
    }
    i = begin;
    k = 0;
    while(i <= end){
        array[i] = p[k];
        i++;
        k++;
    }
    free(p);
}

void array_divide(int array[], int begin, int end)
{
    int mid = begin + (end - begin) / 2;

    if ((end - begin) < 1){
        return;
    } else{
        array_divide(array, begin, mid);
        array_divide(array, mid + 1, end);
    }
    array_merge(array, begin, end);
}

void array_msort(int array[], int n)
{
    assert(n > 0);
    assert(array != NULL);
    array_divide(array, 0, n-1);
}

/************************************************************************/

static void merge(void *base, size_t begin, size_t end, size_t size,
                            int (*compar)(const void *, const void *))
{
    size_t mid = begin + (end - begin) / 2;
    size_t i = begin;
    size_t j = mid + 1;

    char *bi;
    char *bj;
    char *pk;

    char *b = (char*)base;

    size_t k = 0;
    char *p;
    p = (char*)malloc((end - begin + 1) * size);
    assert(p != NULL);
    while((i <= mid) && (j <= end)){
        bi = (char*)(b + i * size);
        bj = (char*)(b + j * size);
        pk = (char*)(p + k * size);
        if (compar(bi, bj) < 0){
//          void *memcpy(void *dest, const void *src, size_t n);
            memcpy(pk, bi, size);
            i++;
            k++;
        }else{
            memcpy(pk, bj, size);
            j++;
            k++;
        }
    }
    while(i <= mid){
        bi = (char*)(b + i * size);
        pk = (char*)(p + k * size);
        memcpy(pk, bi, size);
        i++;
        k++;
    }
    while(j <= end){
        bj = (char*)(b + j * size);
        pk = (char*)(p + k * size);
        memcpy(pk, bj, size);
        j++;
        k++;
    }
    i = begin;
    k = 0;
    while(i<=end){
        bi = (char*)(b + i * size);
        pk = (char*)(p + k * size);
        memcpy(bi, pk, size);
        i++;
        k++;
    }
    free(p);
}

static void divide(void *base, size_t begin, size_t end, size_t size,
                        int (*compar)(const void *, const void *))
{
    size_t mid = begin + (end - begin) / 2;

    if ((end - begin) < 1){
        return;
    } else{
        divide(base, begin, mid, size, compar);
        divide(base, mid + 1, end, size, compar);
    }
    merge(base, begin, end, size, compar);
}

void msort(void *base, size_t nmemb, size_t size,
                        int (*compar)(const void *, const void *))
{
    assert(base != NULL);
    assert(nmemb > 0);
    assert(size > 0);
    assert(compar != NULL);
    divide(base, 0, nmemb - 1, size, compar);
}

int main(int argc, char **argv)
{
    clock_t start_t, end_t, total_t;
    int array[LEN];
    srand(time(NULL));
    for(size_t i = 0; i < LEN; i++){
        array[i]=rand() % 1000;
    }
    start_t = clock();
    msort(array, LEN, sizeof(int), &int_compar);
//    array_msort(array, LEN);
//    qsort(array, LEN, sizeof(int), &int_compar);
    end_t = clock();
    total_t = end_t - start_t;
    printf("\nClocks taken by CPU: %d\n", (int)total_t);

    return 0;
}
