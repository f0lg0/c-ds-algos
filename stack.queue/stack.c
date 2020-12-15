#include <stdio.h>
#include <stdlib.h>

/**
 * item: a piece of data to be added to the stack
*/
struct item {
    int data;
    struct item *next;
};

typedef struct item Item;
Item *start = NULL;
Item *top = NULL;

/**
 * createItem: creates a new Item
 * @param val the value to be assigned to the Item
 * @return a pointer to that Item
*/
Item* createItem(int val) {
    Item *item = malloc(sizeof(Item)); 
    item->data = val;

    return item;
}

/**
 * push: pushes (inserts) an item to the stack (you get the item with the createItem function)
 * @param newItem a pointer to new Item to be pushed
 * @return void
*/
void push(Item *newItem) {
    if (!newItem) {
        printf("[ERR] Invalid item.\n");
        return;
    } else if (!start) {
        start = newItem;
        top = newItem;
    } else {
        Item *temp;
        temp = start;

        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newItem;
        top = newItem;
    }
}

/**
 * pop: remove the last in item of the stack
 * @return void
*/
void pop() {
    if (!top) {
        printf("[ERR] Stuck underflow.\n");
        return;
    }

    Item *temp = start;
    if (!(start->next)) {
        start = NULL;
        free(top);
        top = NULL;
    } else {
        while (temp->next != top) {
            temp = temp->next;
        }
        temp->next = NULL;
        free(top);
        top = temp;
    }
}

/**
 * display: recursively prints the stack
 * @param start the pointer to the Item at the bottom of the stack
 * @return void 
*/
void display(Item *start) {
    if (!top) {
        printf("Stack is empty.\n");
    } else if (!(start)) {
        return;
    } else {
        printf("%2d ", start->data);
        display(start->next);
    }
}

int main() {
    return 0;
}