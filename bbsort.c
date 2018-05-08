#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>

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
    for(i=0; i<nmemb-1; i++){
        swapped = 0;
        for(j=0; j<nmemb-i-1; j++){
            crt = (char*)(b+(j*size));
            next = crt+size;
            if (compar(crt,next) >= 0){
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

int memb_compare(const void *p1, const void *p2)
{
    return((*(int*)p1) - (*(int*)p2));
}

int main(int argc, char **argv)
{
    clock_t start_t, end_t, total_t;
    int array[LEN];
    srand(time(NULL));   // should only be called once
    for(size_t i=0;i<LEN;i++){
        array[i]=rand() % 100;
    }
    start_t = clock();
    bbsort(array,LEN,sizeof(int),&memb_compare);
    end_t = clock();
    total_t = end_t - start_t;
//    for(size_t i=0; i<LEN; i++){
//        printf("%d\n", array[i]);
//    }
    printf("\nClocks taken by CPU: %d\n", (int)total_t);
    return(0);
}
