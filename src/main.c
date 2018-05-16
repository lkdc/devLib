#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "heap.h"
#include "pqueue.h"

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

    start_t = clock();
//
    end_t = clock();
    total_t = end_t - start_t;
//
    printf("\nClocks taken by CPU: %d\n", (int)total_t);


    return 0;
}
