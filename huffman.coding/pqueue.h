#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdint.h>

struct priority_queue {
    int32_t* q;
    uint32_t n;
};

void make_heap(struct priority_queue* q, uint32_t pqsize, int32_t* data, uint32_t n);
void destroy_heap(struct priority_queue* q);

#endif
