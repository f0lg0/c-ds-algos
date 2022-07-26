#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "huffmantree.h"
#include "pqueue.h"

struct mapped_letter {
    const char* letter;
    uint8_t* code;
    uint32_t code_size;
    struct mapped_letter* next;
};

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

void decompress(struct element* root, const char* filename) {
    FILE* src = fopen(filename, "rb");
    ssize_t len;
    
    fseek(src, 0, SEEK_END);
    len = ftell(src);
    rewind(src);

    uint8_t* buf = malloc(sizeof(uint8_t) * len);
    fread(buf, len, 1, src);
    fclose(src);

    for (uint32_t i = 0; i < len; i++)
        printf("%d", buf[i]);

    printf("\n");
    
    /*
    struct element* target = root;

    for (uint32_t i = 0; i < len; i++) {
        if (target->letter) {
            // we have reached the letter
            for (uint32_t j = 0; j < target->freq; j++)
                printf("%c", target->letter);

            // starting again from the top
            target = root;
        }
        if (buf[i] == 0) {
            target = target->left;
        } else {
            target = target->right;
        }
    }
    
    printf("\n");
    */
}

void encode(struct element* root, uint8_t* arr, uint8_t top, struct mapped_letter* start) {
    if (root->left) {
        arr[top] = 0;
        encode(root->left, arr, top + 1, start);
    }
    if (root->right) {
        arr[top] = 1;
        encode(root->right, arr, top + 1, start);
    }
    if (root->left == NULL && root->right == NULL) {
        printf("> %c  | ", root->letter);

        for (uint32_t i = 0; i < top; i++)
            printf("%d", arr[i]);
        
        printf("\n");

        struct mapped_letter* new = malloc(sizeof(struct mapped_letter));
        new->letter = &(root->letter);
        new->code = arr;
        new->code_size = top;
        new->next = NULL;
        
        // reaching the end of the linked list and appending 
        struct mapped_letter* tmp = start; 
        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = new;
    }
}

void compress(struct element* root, const char* outfile) {
    uint8_t arr[htree_height(root)];
    FILE* fptr = fopen(outfile, "wb");

    // for conveinence, im going to store the letters mapped to their code (C:001) in a linked list
    // ofc, an hash table would be better but I don't have time to implement one
    
    struct mapped_letter* start = malloc(sizeof(struct mapped_letter));
    start->letter = '\0';
    start->code = NULL;
    start->code_size = 0;
    start->next = NULL;

    encode(root, arr, 0, start);

    // now we have a linked list of letters mapped to their code, we can use it to write to file
    // TODO: write to file
    
    // free the linked list
    struct mapped_letter* tmp = NULL;
    while (start != NULL) {
        tmp = start;
        start = start->next;
        free(tmp);
    }

    fclose(fptr);
}

void destroy_htree(struct element* root) {
    if (root == NULL) return;

    destroy_htree(root->left);
    destroy_htree(root->right);
    // only freeing allocated nodes (the ones with no letters in them)
    if (!root->letter) free(root);
}
