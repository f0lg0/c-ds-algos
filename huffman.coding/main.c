#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pqueue.h"

/**
 *  input: BCAADDDCCACACAC
 *  input_size = 120 bits
 *
 *  B_frequency: 1
 *  C_frequency: 6
 *  A_frequency: 5
 *  D_frequency: D
 *
 *  q = [B, D, A, C] increasing order of frequency
 * */

int32_t main() {
    uint32_t size = 256;
    struct priority_queue q;

    int32_t data[5] = {69, 4, 8, 1, -7};

    make_heap(&q, size, data, 5);

    for (int32_t i = 0; i < 5; i++)
        printf("%d ", q.q[i]);

    printf("\n");

    return 0;
}
