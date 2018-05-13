#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "heap.h"

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

/* MAX HEAP */

max_heap_t *new_heap(size_t max_nodes, size_t sz_node)
{
    max_heap_t *p;
    p = (max_heap_t*)malloc(sizeof(max_heap_t));
    p->list = malloc(max_nodes * sz_node);
    p->nr_nodes = 0;
    p->max_nodes = max_nodes;
    p->sz_node = sz_node;
    return p;
}

void free_heap(max_heap_t *p)
{
    free(p->list);
    p->list = NULL;
    p->nr_nodes = 0;
    p->max_nodes = 0;
    p->sz_node = 0;
    free(p);
}

static void push_up(max_heap_t *p, size_t node_idx,
                    int (*compar)(const void *, const void *))
{
    int parrent_idx = (node_idx-1)/2;

    char *inode;
    char *iparrent;

    inode = (char*)p->list + node_idx * p->sz_node;
    iparrent = (char*)p->list + parrent_idx * p->sz_node;


    if (node_idx == 0){
        return;
    } else if (compar(inode, iparrent) > 0){
        swap(inode, iparrent, p->sz_node);
        push_up(p, parrent_idx, compar);
    }
}

static void max_heapify(max_heap_t *p, size_t node,
                        int (*compar)(const void *, const void *))
{
    size_t left = node*2+1;
    size_t right = node*2+2;
    char* inode;
    char* ileft;
    char* iright;

    inode =(char*)p->list + node * p->sz_node;
    ileft = (char*)p->list + left * p->sz_node;
    iright = (char*)p->list + right * p->sz_node;

    if (p->nr_nodes < node*2+2){
        return;
    } else if (p->nr_nodes == node*2+2){
        if (compar(inode, ileft) < 0){
            swap(inode, ileft, p->sz_node);
            max_heapify(p, left, compar);
        } else return;
    } else if(p->nr_nodes > node*2+2){
        if (compar(ileft, iright) > 0){
            if (compar(inode, ileft) < 0){
                swap(inode, ileft, p->sz_node);
                max_heapify(p, left, compar);
            } else return;
        } else if (compar(ileft, iright) <= 0){
            if (compar(inode, iright) < 0){
                swap(inode, iright, p->sz_node);
                max_heapify(p, right, compar);
            } else return;
        }
    }
}

void max_heap_insert(max_heap_t *p, void *key,
                        int (*compar)(const void *, const void *))
{

    char *idx_new_node;

    if (p->nr_nodes < p->max_nodes){
        idx_new_node = (char*)p->list + p->nr_nodes * p->sz_node;
        memcpy(idx_new_node, key, p->sz_node);
        push_up(p, p->nr_nodes, compar);
        p->nr_nodes++;
    } else {
        if (p->max_nodes > 0){
            p->max_nodes *= 2;
        } else{
            p->max_nodes = 1;
        }
        p->list = realloc(p->list, p->max_nodes * p->sz_node);
        idx_new_node = (char*)p->list + p->nr_nodes * p->sz_node;
        memcpy(idx_new_node, key, p->sz_node);
        push_up(p, p->nr_nodes, compar);
        p->nr_nodes++;
    }
}

void build_max_heap(max_heap_t *p,
                        int (*compar)(const void *, const void *))
{
    for(size_t i = (p->nr_nodes-1)/2; i>0; i--){
        max_heapify(p, i, compar);
    }
    max_heapify(p,0,compar);
}

void sort_max_heap(max_heap_t *p,
                        int (*compar)(const void *, const void *))
{
    size_t nr_nodes = p->nr_nodes;

    char *root;
    char *last_node;

    build_max_heap(p, compar);

    root = (char*)p->list;
    while(p->nr_nodes > 0){
        last_node = (char*)p->list + (p->nr_nodes-1)*p->sz_node;
        swap(last_node, root, p->sz_node);
        p->nr_nodes--;
        max_heapify(p, 0, compar);
    }
    p->nr_nodes = nr_nodes;
}

max_heap_t *new_fixed_heap(void *base, size_t nmemb, size_t size)
{
    max_heap_t *p;
    p = (max_heap_t*)malloc(sizeof(max_heap_t));
    p->list = base;
    p->nr_nodes = nmemb;
    p->max_nodes = nmemb;
    p->sz_node = size;
    return p;
}

void free_fixed_heap(max_heap_t *p)
{
    p->list = NULL;
    p->nr_nodes = 0;
    p->max_nodes = 0;
    p->sz_node = 0;
    free(p);
}

void hsort(void *base, size_t nmemb, size_t size,
                        int (*compar)(const void *, const void *))
{
    max_heap_t *p;
    p = new_fixed_heap(base, nmemb, size);
    sort_max_heap(p, compar);
    free_fixed_heap(p);
}
