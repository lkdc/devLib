#ifndef HEAP_H_
#define HEAP_H_

void swap(void *v1, void *v2, size_t size);

/* MAX HEAP */

typedef struct max_heap{
    void *list;                 //pointer to array of elements
    size_t nr_nodes;            //number of elements
    size_t max_nodes;           //max nr of elements in the heap
    size_t sz_node;             //size of element
} max_heap_t;

max_heap_t *new_heap(size_t max_nodes, size_t sz_node);
void free_heap(max_heap_t *p);
static void push_up(max_heap_t *p, size_t node_idx, int (*compar)(const void *, const void *));
static void max_heapify(max_heap_t *p, size_t node, int (*compar)(const void *, const void *));
void max_heap_insert(max_heap_t *p, void *key, int (*compar)(const void *, const void *));
void build_max_heap(max_heap_t *p, int (*compar)(const void *, const void *));
void sort_max_heap(max_heap_t *p, int (*compar)(const void *, const void *));



max_heap_t *new_fixed_heap(void *base, size_t nmemb, size_t size);
void free_fixed_heap(max_heap_t *p);
void hsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

#endif
