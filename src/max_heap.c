#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "dev.h"

#include <time.h>
#define LEN 32767

int main(int argc, char **argv)
{

    clock_t start_t, end_t, total_t;
    srand(time(NULL));   // should only be called once

    max_heap_t *p[1];
    int key;
    for(int i=0; i<1; i++){
        p[i] = new_heap(1000000, sizeof(int));
        for(int j=0; j<1000000; j++){
            key = rand();
            max_heap_insert(p[i], &key, &int_compar);
        }
//        heap_sort(p[i], &int_compar);
        free_heap(p[i]);
    }


//    printf("Done!\n");
//    while(1);

/*
    for(int i = 1; i < 7; i++){
        insert_node(p, &i, &int_compar);
    }
    int *idx;
    idx = p->list;
    for(int i=0; i<6; i++){
        printf("%d ", *idx);
        idx++;
    }
*/




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

    return 0;

}
/*
void max_heapify(max_heap_t *h, size_t node)
{
    size_t tmp;
    size_t left = node*2;
    size_t right = node*2+1;

    if (h->nr_nodes < node*2){
        return;
    } else if(h->nr_nodes == node*2){
        if (h->list[node] < h->list[left]){
            tmp = h->list[node];
            h->list[node] = h->list[left];
            h->list[left] = tmp;
            max_heapify(h, left);
        } else return;
    } else if(h->nr_nodes > node*2){
        if (h->list[left] > h->list[right]){
            if (h->list[node] < h->list[left]){
                tmp = h->list[node];
                h->list[node] = h->list[left];
                h->list[left] = tmp;
                max_heapify(h, left);
            } else return;
        } else if (h->list[left] <= h->list[right])
            if (h->list[node] < h->list[right]){
                tmp = h->list[node];
                h->list[node] = h->list[right];
                h->list[right] = tmp;
                max_heapify(h, right);
            } else return;
    }
}

void max_heapify(max_heap_t *h, size_t node, int (*compar)(const void *, const void *))
{
    size_t left = node*2;
    size_t right = node*2+1;
    size_t inode;
    size_t ileft;
    size_t iright;

    if (h->nr_nodes < node*2){
        return;
    } else if (h->nr_nodes == node*2){
        inode =(size_t)h->list + node*h->sz_node;
        ileft = (size_t)h->list + left*h->sz_node;
        if (compar((void*)inode, (void*)ileft) < 0){
            swap((void*)inode, (void*)ileft, h->sz_node);
            max_heapify(h, left, compar);
        } else return;
    } else if(h->nr_nodes > node*2){
        inode =(size_t)h->list + node*h->sz_node;
        ileft = (size_t)h->list + left*h->sz_node;
        iright = (size_t)h->list + right*h->sz_node;

        if (compar((void*)ileft, (void*)iright) > 0){
            if (compar((void*)inode, (void*)ileft) < 0){
                swap((void*)inode, (void*)ileft, h->sz_node);
                max_heapify(h, left, compar);
            } else return;

        } else if (compar((void*)ileft, (void*)iright) <= 0){
            if (compar((void*)inode, (void*)iright) < 0){
                swap((void*)inode, (void*)iright, h->sz_node);
                max_heapify(h, right, compar);
            } else return;
        }
    }
}
*/
