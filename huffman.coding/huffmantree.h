#ifndef HUFFAMNTREE_H
#define HUFFMANTREE_H

#include <stdio.h>
#include "pqueue.h"


uint32_t htree_height(struct element* root);
void traverse_htree(struct element* root);
int32_t compress(struct element* root, char* input);
void decompress(struct element* root, uint32_t e_len);
struct element* make_htree(struct priority_queue* q);
void destroy_htree(struct element* root);

#endif
