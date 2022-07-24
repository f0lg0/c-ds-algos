#ifndef HUFFAMNTREE_H
#define HUFFMANTREE_H

#include <stdio.h>
#include "pqueue.h"


uint32_t htree_height(struct element* root);
void traverse_htree(struct element* root);
void compress(struct element* root, const char* outfile);
void decompress(struct element* root, const char* filename);
struct element* make_htree(struct priority_queue* q);
void destroy_htree(struct element* root);

#endif
