#ifndef HUFFAMNTREE_H
#define HUFFMANTREE_H

#include "pqueue.h"


void traverse_htree(struct element* root);
struct element* make_htree(struct priority_queue* q);

#endif
