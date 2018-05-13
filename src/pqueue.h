#ifndef PQUEUE_H_
#define PQUEUE_H_

#define LEFT(x)     ((x<<1)+1)
#define RIGHT(x)    ((x<<1)+2)
#define PARENT(x)   ((x-1)>>1)

#define SWAP(p,v1,v2)   {\
                            void *v = p->list[v1];\
                            p->list[v1] = p->list[v2];\
                            p->list[v2] = v;\
                        }

typedef struct pqueue{
    void **list;                //array of void pointers to nodes (data)
    size_t nnode;               //number of nodes present in the heap
    size_t capacity;            //max nr of nodes (heap capacity)
    size_t size;                //size of a node
    int (*compar)(const void* p1, const void* p2);
} pqueue_t;

pqueue_t *pq_new(size_t capacity, size_t size, int (*compar)(const void *, const void *));
void pq_free(pqueue_t *p);
static void pq_push_up(pqueue_t *p, size_t node);
static void pq_heapify(pqueue_t *p, size_t node);
void pq_insert(pqueue_t *p, void *node);
void *pq_extract(pqueue_t *p);
void *pq_peak(pqueue_t *p);
//void pq_build(pqueue_t *p);
//void pq_sort(pqueue_t *p);

#endif
