#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "huffmantree.h"
#include "pqueue.h"

void traverse_htree(struct element* root) {
    if (root == NULL) return;

    traverse_htree(root->left);
    printf("node at %p:\n\tletter: %c\n\tfreq: %d\n\tleft: %p\n\tright: %p\n\n", root, root->letter, root->freq, root->left, root->right);
    traverse_htree(root->right);
}

int8_t check_size_one(struct priority_queue* q) {
    return (q->n == 1);
}

uint32_t htree_height(struct element* root) {
    if (root == NULL) return 0;

    uint32_t left_height = htree_height(root->left);
    uint32_t right_height = htree_height(root->right);

    if (left_height >= right_height)
        return left_height + 1;
    else
        return right_height + 1;
}

struct element* make_htree(struct priority_queue* q) {
    struct element* ret = NULL;

    while (!check_size_one(q)) {
        struct element* node = malloc(sizeof(struct element));
        node->left = extract_min(q);
        node->right = extract_min(q);
        node->freq = node->left->freq + node->right->freq;
        node->letter = '\0';

        pq_insert(q, (q->n) + 1, node);
        ret = node;
    }
    
    return ret;
}

void decode(struct element* root, uint8_t* arr, uint8_t top) {
    struct element* target = root;

    for (uint32_t i = 0; i < top; i++) {
        if (arr[i] == 0) {
            target = target->left;
        } else {
            target = target->right;
        }
    }

    // we have reached the letter
    printf("%c\n", target->letter);
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
