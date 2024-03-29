#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdint.h>

struct element {
    char letter;
    uint32_t freq;

    // fields needed in the htree
    struct element* left;
    struct element* right;
};

struct elements_wrapper {
    struct element* array;
    uint32_t len;
};

struct priority_queue {
    struct element** q;
    uint32_t n;
};

void pq_insert(struct priority_queue* q, uint32_t pqsize, struct element* x);
void make_heap(struct priority_queue* q, uint32_t pqsize, struct element* data, uint32_t n);
struct elements_wrapper* heapsort(struct priority_queue* q);
struct element* extract_min(struct priority_queue* q);
void destroy_elements_wrapper(struct elements_wrapper* elw);
void destroy_heap(struct priority_queue* q);

#endif
