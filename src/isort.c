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

//Insertion sort
void isort(void *base, size_t nmemb, size_t size,
            int (*compar)(const void *, const void *))
{
    size_t i,j;
    char *b = (char*)base;
    char *crt, *next;
    for(i = 0; i < nmemb; i++){
        for(j = i; j > 0; j--){
            crt = (char*)(b + j * size);
            next = (char*)(b + ((j - 1) * size));
            if (compar(crt, next) >= 0)
                break;
            else{
                swap(next, crt, size);
            }
        }
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
    isort(array, LEN, sizeof(int), &int_compar);
    end_t = clock();
    total_t = end_t - start_t;
    printf("\nClocks taken by CPU: %d\n", (int)total_t);
    return(0);
}





/*
void isort(int *a, int length)
{
    int i,j;
    int tmp;
    for(i=0; i<length; i++){
        j=i;
        for(j=i;j>0;j--){
            if (a[j] >= a[j-1])
                break;
            else{
                tmp = a[j];
                a[j]=a[j-1];
                a[j-1]=tmp;
            }
        }
    }
}
*/

/*
void isort(void *base, size_t nmemb, size_t size,
            int (*compar)(const void *, const void *))
{
    size_t i,j;
    size_t b = (size_t)base;
    size_t tmp = (size_t)malloc(size);
    if (!tmp){
        printf("Error during memory allocation");
        exit(0);
    size_t crt, next;
    for(i=0; i<nmemb; i++){
        for(j=i;j>0;j--){
            crt = b+(j*size);
            next = b+((j-1)*size);
            if (compar((void*)crt,(void*)next) >= 0)
                break;
            else{
//               void *memcpy(void *dest, const void *src, size_t n);
               memcpy((void*)tmp, (void*)crt, size);
               memcpy((void*)crt, (void*)next, size);
               memcpy((void*)next, (void*)tmp, size);
            }
        }
    }
    free((void*)tmp);
}
*/
