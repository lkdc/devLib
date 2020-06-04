#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LEN 11

int array_nr[LEN] = {10, 1, 4, 2, 1, 8, 4, 3, 2, 9, 12};


void swap(void *ap, void *bp, int size_p){

    void *buffer;

    buffer = malloc(size_p);
    memcpy(buffer, ap, size_p);
    memcpy(ap, bp, size_p);
    memcpy(bp, buffer, size_p);
    free(buffer);
}


void sort_nr(int *a, int len){

    for(int i = 0; i < len - 1; i++){
        for(int j = i + 1; j < len; j++){
            if(a[i] > a[j]){
                swap(&a[i], &a[j], sizeof(a[i]));
            }
        }
    }
}

void main(int argv, char *argc[]){
    sort_nr(array_nr,LEN);
    for(int i = 0; i < LEN; i++)
        printf("%d ", array_nr[i]);
    printf("\n");

}

