#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pqueue.h"

void pq_init(struct priority_queue* q, uint32_t pqsize) {
    q->q = malloc(sizeof(struct element*) * pqsize);
    q->n = 0;
}

int32_t pq_get_parent(uint32_t k) {
    if (k == 0) return -1;
    
    // floor(n/2)
    return ((int32_t) k/2); 
}

int32_t pq_get_young_child(uint32_t k) {
    return ((2 * k) + 1);
}

void pq_swap(struct priority_queue* q, uint32_t pos, int32_t parent) {
    struct element* tmp = q->q[pos];
    q->q[pos] = q->q[parent];
    q->q[parent] = tmp;
}

void bubble_up(struct priority_queue* q, uint32_t pos) {
    if (pq_get_parent(pos) == -1) return; // we are at the root of the heap

    if (q->q[pq_get_parent(pos)]->freq > q->q[pos]->freq) {
        pq_swap(q, pos, pq_get_parent(pos));
        bubble_up(q, pq_get_parent(pos));
    }
}

void bubble_down(struct priority_queue* q, uint32_t pos) {
    int32_t c = pq_get_young_child(pos);
    int32_t min_index = pos; // index of lightest child

    for (uint32_t i = 0; i <= 1; i++) {
        if ((c + i) <= q->n) {
            if (q->q[min_index]->freq > q->q[c + i]->freq)
                min_index = c + i;
        }
    }

    if (min_index != pos) {
        pq_swap(q, pos, min_index);
        bubble_down(q, min_index);
    }

}

void pq_insert(struct priority_queue* q, uint32_t pqsize, struct element* x) {
    if (q->n >= pqsize) {
        printf("Warning: priority queue overflow at insert x=%c\n", x->letter);
        return;
    }
    
    // placing at the end
    q->q[q->n] = x;
    
    // assigning correct position
    bubble_up(q, q->n);
    
    // incrementing pq size
    q->n = (q->n) + 1;
}

struct element* extract_min(struct priority_queue* q) {
    struct element* min = NULL;

    if (q->n <= 0) {
        printf("Warning: empty priority queue.\n");
    } else {
        min = q->q[0];
        
        q->q[0] = q->q[(q->n) - 1];
        q->n = q->n - 1;
    
        bubble_down(q, 0);
    }
    
    return min;
}

void make_heap(struct priority_queue* q, uint32_t pqsize, struct element* data, uint32_t n) {
    pq_init(q, pqsize);

    for (uint32_t i = 0; i < n; i++)
        pq_insert(q, pqsize, &(data[i]));
}

void heapsort(struct priority_queue* q) {
    uint32_t tmp = q->n;
    for (uint32_t i = 0; i < tmp; i++) {
        struct element* el = extract_min(q);
        printf("EXTRACTED: %c:%d\n", el->letter, el->freq);
    }
}

void destroy_heap(struct priority_queue* q) {
    free(q->q);
}
