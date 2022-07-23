#ifndef HUFFAMNTREE_H
#define HUFFMANTREE_H

#include "pqueue.h"


struct element* make_htree(struct priority_queue* q);
void traverse_htree(struct element* root);
void encode(struct element* root, uint8_t* arr, uint8_t top);

#endif
