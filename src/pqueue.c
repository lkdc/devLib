#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

pqueue_t *pq_new(size_t capacity, size_t size, int (*compar)(const void *, const void *))
{
    pqueue_t *p;
    p = (pqueue_t*)malloc(sizeof(pqueue_t));
    assert(p != NULL);
    if(capacity == 0){
        return NULL;
    } else{
        p->list = malloc(capacity * sizeof(size_t));
        assert(p->list != NULL);
    }
    p->nnode = 0;
    p->capacity = capacity;
    p->size = size;
    p->compar = compar;
    return p;
}

void pq_free(pqueue_t *p)
{
    if (p->list != NULL){
        free(p->list);
    }
    p->nnode = 0;
    p->capacity = 0;
    p->size = 0;
    free(p);
}

static void pq_push_up(pqueue_t *p, size_t node)
{
    if (node == 0){
        return;
    } else if (p->compar(p->list[node], p->list[PARENT(node)]) > 0){
        SWAP(p, node, PARENT(node));
        pq_push_up(p, PARENT(node));
    }
}

static void pq_heapify(pqueue_t *p, size_t node)
{
    size_t max;
    if (p->nnode < RIGHT(node)){
        return;
    } else if (p->nnode == RIGHT(node)){
        if (p->compar(p->list[node], p->list[LEFT(node)]) < 0){
            SWAP(p, node, LEFT(node));
            pq_heapify(p, LEFT(node));
        } else return;
    } else if (p->nnode > RIGHT(node)){
        if (p->compar(p->list[LEFT(node)], p->list[RIGHT(node)]) < 0){
            max = RIGHT(node);
        } else {
            max = LEFT(node);
        }
        if (p->compar(p->list[node], p->list[max]) < 0){
            SWAP(p, node, max);
            pq_heapify(p, max);
        }
    }
}

void pq_insert(pqueue_t *p, void *node)
{
    if (p->nnode < p->capacity){
        p->list[p->nnode] = node;
        pq_push_up(p, p->nnode);
        p->nnode++;
    } else {
        if (p->capacity > 0){
            p->capacity <<= 1;
        } else{
            p->capacity = 1;
        }
        p->list = realloc(p->list, p->capacity * sizeof(size_t));
        p->list[p->nnode] = node;
        pq_push_up(p, p->nnode);
        p->nnode++;
    }
}

void *pq_extract(pqueue_t *p)
{
    void *v;
    if (p->nnode == 0)
        v = NULL;
    else if (p->nnode == 1){
        p->nnode--;
        v = p->list[p->nnode];
        p->list[p->nnode] = NULL;
    } else{
        p->nnode--;
        SWAP(p, 0, p->nnode);
        v = p->list[p->nnode];
        p->list[p->nnode] = NULL;
        pq_heapify(p, 0);
    }
    if (p->capacity > p->nnode<<2){
        p-> capacity >>=1;
        p->list = realloc(p->list, p->capacity * sizeof(size_t));
    }
    return v;
}

void *pq_peak(pqueue_t *p)
{
    if (p->nnode == 0){
        return NULL;
    } else {
        return (p->list[0]);
    }
}

/*
void pq_build(pqueue_t *p)
{
    if (p->nnode > 0){
        for(size_t i = (p->nnode-1)>>1; i>0; i--){
            pq_heapify(p, i);
        }
    }
    pq_heapify(p,0);
}

void pq_sort(pqueue_t *p)
{
    size_t nnode = p->nnode;

    pq_build(p);
    while(p->nnode > 0){
        p->nnode--;
        SWAP(p, p->nnode, 0);
        pq_heapify(p, 0);
    }
    p->nnode = nnode;
}
*/
