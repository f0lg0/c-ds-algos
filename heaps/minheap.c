// MINHEAP IMPLEMENTATION + HEAPSORT

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define PQ_SIZE 256

struct priority_queue {
    int32_t q[PQ_SIZE];
    uint32_t n;
};

void pq_init(struct priority_queue* q) {
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
    int32_t tmp = q->q[pos];
    q->q[pos] = q->q[parent];
    q->q[parent] = tmp;
}

void bubble_up(struct priority_queue* q, uint32_t pos) {
    if (pq_get_parent(pos) == -1) return; // we are at the root of the heap

    if (q->q[pq_get_parent(pos)] > q->q[pos]) {
        pq_swap(q, pos, pq_get_parent(pos));
        bubble_up(q, pq_get_parent(pos));
    }
}

// heapify
void bubble_down(struct priority_queue* q, uint32_t pos) {
    int32_t c = pq_get_young_child(pos);
    int32_t min_index = pos; // index of lightest child

    for (uint32_t i = 0; i <= 1; i++) {
        if ((c + i) <= q->n) {
            if (q->q[min_index] > q->q[c + i])
                min_index = c + i;
        }
    }

    if (min_index != pos) {
        pq_swap(q, pos, min_index);
        bubble_down(q, min_index);
    }

}

void pq_insert(struct priority_queue* q, int32_t x) {
    if (q->n >= PQ_SIZE) {
        printf("Warning: priority queue overflow at insert x=%d\n", x);
        return;
    }
    
    // placing at the end
    q->q[q->n] = x;
    
    // assigning correct position
    bubble_up(q, q->n);
    
    // incrementing pq size
    q->n = (q->n) + 1;
}

int32_t extract_min(struct priority_queue* q) {
    int32_t min = -1;

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

void make_heap(struct priority_queue* q, int32_t* data, uint32_t n) {
    pq_init(q);

    for (uint32_t i = 0; i < n; i++)
        pq_insert(q, data[i]);
}

// bonus: heap sort algorithm
void heapsort(int32_t* data, uint32_t size) {
    struct priority_queue q;
    make_heap(&q, data, size);

    for (uint32_t i = 0; i < size; i++)
        data[i] = extract_min(&q);
}

int32_t main() {
    // testing heapsort
    srand(time(NULL));
    
    int32_t* data = malloc(sizeof(int32_t) * PQ_SIZE);
 

    for (uint32_t i = 0; i < PQ_SIZE; i++) {
        data[i] = rand() % 1000;
        printf("%d ", data[i]);
    }

    printf("\n");

    heapsort(data, PQ_SIZE);

    for (uint32_t i = 0; i < PQ_SIZE; i++)
        printf("%d ", data[i]);

    printf("\n");

    return 0;
}
