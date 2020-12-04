#include <stdio.h>
#include <stdlib.h>

/**
 * item: a piece of data to be added to the queue
*/
struct item {
    int data;
    struct item *next;
};

typedef struct item Item;
Item *first = NULL;
Item *last = NULL;

/**
 * createItem: creates a new Item
 * @param val the value to be assigned to the Item
 * @return a pointer to that Item
*/
Item* createItem(int val) {
    Item *item = (Item *)malloc(sizeof(Item)); 
    item->data = val;

    return item;
}


/**
 * enqueue: inserts an Item into the queue
 * @param newItem a pointer to a new Item
 * @return void 
*/
void enqueue(Item *newItem) {
    if (!newItem) {
        printf("[ERR] Invalid item.\n");
        return;
    } 
    if (!first) {
        first = newItem;
        last = newItem;
    } else {
        last->next = newItem;
        last = newItem;
    }
}

/**
 * dequeue: removes the first in item from the queue
 * @return void
*/
void dequeue() {
    if (!first) {
        printf("Empty queue\n");
        return;
    } 
    Item *temp = first;
    first = first->next;
    free(temp);
}

/**
 * display: recursively prints the queue
 * @param first the pointer to the first Item in the queue
*/
void display(Item *first) {
    if (!first) {
        return;
    } else {
        printf("%2d ", first->data);
        display(first->next);
    }
}

int main() {
    return 0;
}