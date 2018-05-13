#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "heap.h"
#include "pqueue.h"

#define LEN 100

int int_compar(const void *p1, const void *p2)
{
    if (*(int*)p1 > *(int*)p2)
        return 1;
    else if (*(int*)p1 < *(int*)p2)
        return -1;
    else
        return 0;
}

int float_compar(const void *p1, const void *p2)
{
    if (*(float*)p1 > *(float*)p2)
        return 1;
    else if (*(float*)p1 < *(float*)p2)
        return -1;
    else
        return 0;
}

int main(int argc, char **argv)
{
    clock_t start_t, end_t, total_t;
    srand(time(NULL));

    float array[LEN];
    for(int i = 0; i<LEN; i++)
        array[i] = (float)(LEN-i);

    start_t = clock();
    hsort(array, LEN, sizeof(int), &float_compar);
    end_t = clock();
    total_t = end_t - start_t;
    for(int i=0; i<LEN; i++){
        printf("%f ", array[i]);
    }
    printf("\nClocks taken by CPU: %d\n", (int)total_t);


    pqueue_t *p;
    int v[10] = {-3, 1, 8, 2, -9, 7, 5, 4, -4, -7};

    p = pq_new(1, sizeof(int), &int_compar);
    assert(p != NULL);
    for(int i=0; i<10; i++){
        pq_insert(p, &v[i]);
    }
    for(int i=0; i<p->nnode; i++){
        printf("%d ", *(int*)p->list[i]);
    }
    printf("\n");
    while(pq_peak(p) != NULL){
        printf("%d ",*(int*)pq_extract(p));
    }
    printf("\n");
    pq_free(p);

    return 0;
}
