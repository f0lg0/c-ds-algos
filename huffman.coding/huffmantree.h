#ifndef HUFFAMNTREE_H
#define HUFFMANTREE_H

#include "pqueue.h"


uint32_t htree_height(struct element* root);
void traverse_htree(struct element* root);
void encode(struct element* root, uint8_t* arr, uint8_t top);
struct element* make_htree(struct priority_queue* q);
void destroy_htree(struct element* root);

#endif
