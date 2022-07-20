#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
    
    struct element el0;
    strcpy(&(el0.letter), "A");
    el0.freq = 69;

    struct element el1;
    strcpy(&(el1.letter), "B");
    el1.freq = 5;

    struct element el2;
    strcpy(&(el2.letter), "C");
    el2.freq = 7;

    struct element data[3] = {el0, el1, el2};

    make_heap(&q, size, data, 3);

    for (int32_t i = 0; i < 3; i++)
        printf("%c:%d ", q.q[i].letter, q.q[i].freq);

    printf("\n");

    return 0;
}
