#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "huffmantree.h"
#include "pqueue.h"

struct mapped_letter {
    const char* letter;
    char* code;
    uint32_t code_size;
    struct mapped_letter* next;
};

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

// lookup table to improve speed
const char *bit_rep[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};


void decompress(struct element* root, uint32_t e_len) {
    FILE* src = fopen("./compressed.b", "rb");
    ssize_t len;
    
    fseek(src, 0, SEEK_END);
    len = ftell(src);
    if (len == -1) {
        fprintf(stderr, "error: ftell() in decompress() returned -1.\n");
        return;
    }

    rewind(src);
    
    uint8_t* buf = malloc(sizeof(uint8_t) * (len + 1));
    if (buf == NULL) {
        fprintf(stderr, "error: malloc() in decompress() returned NULL pointer.\n");
        return;
    }

    size_t ret = fread(buf, sizeof(char), len, src);
    if (ret != (size_t)len) {
        if (feof(src)) {
            fprintf(stderr, "error: unexpected EOF while reading from file in decompress().\n");
        } else if (ferror(src)) {
            fprintf(stderr, "error: reading from file in decompress() failed.\n");
        }
    }

    fclose(src);
    
    uint32_t next_multiple_8 = ((e_len + 7) >> 3) << 3;

    char* bstring = malloc(sizeof(char) * (next_multiple_8 + 1));
    char* p = bstring;

    for (uint32_t i = 0; i < len; i++)
        p += sprintf(p, "%s%s", bit_rep[buf[i] >> 4], bit_rep[buf[i] & 0x0F]);

    struct element* target = root;
    FILE* out = fopen("./decompressed.b", "wb");

    for (uint32_t i = 0; i < e_len; i++) {
        if (target->letter) {
            // we have reached a letter
            fwrite(&target->letter, sizeof(char), 1, out);

            // starting again from the top
            target = root;
        }

        if (bstring[i] == '0')
            target = target->left;
        else
            target = target->right;
    }

    // writing last entered node
    fwrite(&target->letter, sizeof(char), 1, out);

    free(buf);
    free(bstring);
    fclose(out);
}

void encode(struct element* root, char* arr, uint8_t top, struct mapped_letter* start) {
    if (root->left) {
        arr[top] = '0';
        encode(root->left, arr, top + 1, start);
    }
    if (root->right) {
        arr[top] = '1';
        encode(root->right, arr, top + 1, start);
    }
    if (root->left == NULL && root->right == NULL) {
        struct mapped_letter* new = malloc(sizeof(struct mapped_letter));
        new->letter = &(root->letter);

        char* copy = malloc(sizeof(char) * top);
        if (copy == NULL) {
            fprintf(stderr, "error: malloc() in encode() returned NULL pointer.\n");
            return;
        }

        memcpy(copy, arr, sizeof(char) * top);
        new->code = copy;

        new->code_size = top;
        new->next = NULL;
        
        // reaching the end of the linked list and appending 
        struct mapped_letter* tmp = start; 
        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = new;
    }
}

// this is for tmp storing the encoded input
void dump_encoded(char* input, FILE* fptr, struct mapped_letter* start) {
    uint32_t len = strlen(input);
    for (uint32_t i = 0; i < len; i++) {
        struct mapped_letter* tmp = start;
        while (*(tmp->letter) != input[i])
            tmp = tmp->next;
        
        fwrite(tmp->code, sizeof(char), tmp->code_size, fptr);
    }
}

uint32_t compress_to_file(FILE* src) {
    uint32_t len;
    
    fseek(src, 0, SEEK_END);
    len = ftell(src);
    rewind(src);
    
    char* buf = malloc(sizeof(char) * (len + 1));
    if (buf == NULL) {
        fprintf(stderr, "error: malloc() in compress_to_file() returned NULL pointer.\n");
        return -1;
    }

    size_t ret = fread(buf, sizeof(char), len, src);
    if (ret != len) {
        if (feof(src)) {
            fprintf(stderr, "error: unexpected EOF while reading from file in compress_to_file().\n");
        } else if (ferror(src)) {
            fprintf(stderr, "error: reading from file in compress_to_file() failed.\n");
        }
    }

    FILE* out = fopen("./compressed.b", "wb");
    
    char dst[9];
    for (uint32_t i = 0; i < len; i++) {
        if (i % 8 == 0) {
            strncpy(dst, &buf[i], 8);

            // padding 
            size_t dst_len = strlen(dst); // can be optmized but we need to check if we need to pad
            if (dst_len < 8) {
                uint8_t start = 8 - dst_len;
                for (uint8_t j = start; j < 8; j++)
                    dst[j] = '0';
            }

            // we know the max will be 8bits since we are manually parsing 8 bits
            uint8_t v = (uint8_t)strtol(dst, NULL, 2);
            fwrite(&v, sizeof(v), 1, out);
        }
    }

    free(buf);
    remove("./tmp");
    fclose(out);

    return len;
}

int32_t compress(struct element* root, char* input) {
    char arr[htree_height(root)];
    FILE* fptr = fopen("./tmp", "wb+");

    // for conveinence, im going to store the letters mapped to their code (C:001) in a linked list
    // ofc, an hash table would be better but I don't have time to implement one
    
    struct mapped_letter* start = malloc(sizeof(struct mapped_letter));
    start->letter = '\0';
    start->code = NULL;
    start->code_size = 0;
    start->next = NULL;

    encode(root, arr, 0, start);
    // now we have a linked list of letters mapped to their code, we can use it to write to file
    dump_encoded(input, fptr, start->next); // skipping head
    int32_t e_len = compress_to_file(fptr);
    
    // free the linked list
    struct mapped_letter* tmp = NULL;
    while (start != NULL) {
        tmp = start;
        start = start->next;
        free(tmp->code);
        free(tmp);
    }

    fclose(fptr);
    return e_len;
}

void destroy_htree(struct element* root) {
    if (root == NULL) return;

    destroy_htree(root->left);
    destroy_htree(root->right);
    // only freeing allocated nodes (the ones with no letters in them)
    if (!root->letter) free(root);
}
