#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "pqueue.h"
#include "huffmantree.h"

struct elements_wrapper* craft_freq_array(char* str, uint32_t str_length) {
    // starting with a single element array
    struct element* arr = malloc(sizeof(struct element));
    uint32_t idx = 0;

    // tmp buffer to avoid messing around with og input
    char* tmp = malloc(sizeof(char) * str_length + 1);
    strncpy(tmp, str, str_length);
     
    for (uint32_t i = 0; i < str_length; i++) {
        uint32_t c = 1;

        if (tmp[i] != '\0') {
            for (uint32_t  j = i + 1; j < str_length; j++) {
                if (tmp[i] == tmp[j]) {
                    c++;
                    tmp[j] = '\0';
                }
            }

            if (idx > 0)
                arr = realloc(arr, sizeof(struct element) * (idx + 1));

            struct element el = {
                .letter = tmp[i],
                .freq = c,
                .left = NULL,
                .right = NULL
            };

            arr[idx] = el;
            idx++;
        }
    }
    

    free(tmp);

    struct elements_wrapper* ret = malloc(sizeof(struct elements_wrapper));
    ret->array = arr;
    ret->len = idx;

    return ret;
}


int32_t main() {
    char input[] = "BCAADDDCCACACAC";
    uint32_t input_length = strlen(input);
    printf("input: %s\n  length: %d\n  size: %ld\n", input, input_length, sizeof(input));

    struct elements_wrapper* els = craft_freq_array(input, input_length);
    
    struct priority_queue q;
    make_heap(&q, els->len, els->array, els->len);
    
    struct element* tree = make_htree(&q);
    uint8_t arr[htree_height(tree)];
    encode(tree, arr, 0);
    // traverse_htree(tree);

    destroy_htree(tree);
    destroy_elements_wrapper(els);
    destroy_heap(&q); 

    return 0;
}
