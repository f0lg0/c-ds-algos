#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdint.h>

struct element {
    char letter;
    uint32_t freq;
};

struct priority_queue {
    struct element* q;
    uint32_t n;
};

void make_heap(struct priority_queue* q, uint32_t pqsize, struct element* data, uint32_t n);
void destroy_heap(struct priority_queue* q);

#endif
