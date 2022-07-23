#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "huffmantree.h"
#include "pqueue.h"

void traverse_htree(struct element* root) {
    if (root == NULL) return;

    // printf("called on node (%c:%d) at %p with left: %p and right %p\n", root->letter, root->freq, root, root->left, root->right);
    traverse_htree(root->left);
    printf("node at %p:\n\tletter: %c\n\tfreq: %d\n\tleft: %p\n\tright: %p\n\n", root, root->letter, root->freq, root->left, root->right);
    traverse_htree(root->right);
}

int8_t check_size_one(struct priority_queue* q) {
    return (q->n == 1);
}

struct element* make_htree(struct priority_queue* q) {
    struct element* ret = NULL;

    while (!check_size_one(q)) {
        struct element* node = malloc(sizeof(struct element));
        node->left = extract_min(q);
        node->right = extract_min(q);
        // printf(">> extracted 2 (left: %p (%c:%d), right: %p (%c:%d)), now q->n is: %d\n", node->left, node->left->letter, node->left->freq, node->right, node->right->letter, node->right->freq, q->n);
        node->freq = node->left->freq + node->right->freq;
        node->letter = '\0';

        pq_insert(q, (q->n) + 1, node);
        // printf(">> insert (%c:%d with left %c:%d and right %c:%d), now q->n is: %d\n", node->letter, node->freq, node->left->letter, node->left->freq, node->right->letter, node->right->freq, q->n);
        ret = node;
    }
    
    return ret;
}

void encode(struct element* root, uint8_t* arr, uint8_t top) {
    if (root->left) {
        arr[top] = 0;
        encode(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        encode(root->right, arr, top + 1);
    }
    if (root->left == NULL && root->right == NULL) {
        printf("> %c  | ", root->letter);

        for (uint32_t i = 0; i < top; i++)
            printf("%d", arr[i]);

        printf("\n");
    }
}

void destroy_htree(struct element* root) {
    if (root == NULL) return;

    destroy_htree(root->left);
    destroy_htree(root->right);
    // only freeing allocated nodes (the ones with no letters in them)
    if (!root->letter) free(root);
}
