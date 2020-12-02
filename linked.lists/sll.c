#include <stdlib.h>
#include <stdio.h>

/**
 * node: a piece of data containing a numeric value and a pointer to the next node
*/
struct node {
    int data;
    struct node* next;
};

typedef struct node Node;
Node *start = NULL; // at the beginning the list is empty, this is a pointer that points to the first element

/**
 * createNode: creates a new Node
 * @param value the value to place into the Node's data
 * @return pointer to new Node
*/
Node* createNode(int value) {
    Node* newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

/**
 * countNodes: counts the number of nodes in a list
 * @param start the start of the list
 * @return number of nodes
*/
int countNodes(Node *start) {
    if (!start)
        return 0;

    return 1 + countNodes(start->next);
}


/**
 * initList: initialize a sll of size "size" with nodes containing a 0
 * @param size the size of the list
 * @return void 
*/
void initList(int size) {
    Node *newNode;
    Node *tempNode;

    for (int i = 0; i < size; i++) {
        newNode = createNode(0);

        if (!start) {
            start = newNode;
        } else {
            tempNode = start;
            // traversing the list till the end
            while(tempNode->next) {
                tempNode = tempNode->next;
            }
            tempNode->next = newNode;
        }
    }
}

/**
 * insertAtBeginning: insert a node at the beginning of the list
 * @param value the value of the node 
 * @return void
*/
void insertAtBeginning(int value) {
    Node *newNode = createNode(value);

    if (!start) {
        start = newNode;
    } else {
        newNode->next = start;
        start = newNode;
    }
}

/**
 * insertAtMid: insert a node at a given position
 * @param value the node's value
 * @param pos the position you want the node to be in
 * @return void
*/
void insertAtMid(int value, int pos) {
    Node *newNode = createNode(value);
    Node *tempNode, *prevNode;

    int nodesCount = countNodes(start);

    if (pos > 1 && pos < nodesCount) {
        tempNode = prevNode = start;

        int i = 1;
        while (i < pos) {
            prevNode = tempNode;
            tempNode = tempNode->next;
            i++;
        }

        prevNode->next = newNode;
        newNode->next = tempNode;
    } else {
        printf("[ERR] Invalid postion: %d.\n", pos);
    }
}

/**
 * insertAtEnd: insert a node at the end of the list
 * @param value the value of the node
 * @return void
*/
void insertAtEnd(int value) {
    Node *newNode = createNode(value);
    Node *tempNode;

    if (!start) {
        start = newNode;
    } else {
        tempNode = start;

        while(tempNode->next) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}

/**
 * deleteAtBeginning: deletes the first node of the list
 * @return void
*/
void deleteAtBeginning() {
    if (!start) {
        printf("[WARNING] Empty list.\n");
    } else {
        Node *tempNode = start;
        start = start->next;
        free(tempNode);
    }
    
}

/**
 * deleteAtEnd: deletes the last node of the list
 * @return void
*/
void deleteAtEnd() {
    if (!start) {
        printf("[WARNING] Empty list.\n");
    } else {
        Node *tempNode, *prevNode;
        tempNode = prevNode = start;

        while (tempNode->next) {
            prevNode = tempNode;
            tempNode = tempNode->next;
        }

        prevNode->next = NULL;
        free(tempNode);
    }
}

/**
 * deleteAtMid: deletes a node at a given position
 * @param pos the node's  position
 * @return void
*/
void deleteAtMid(int pos) {
    if (!start) {
        printf("[WARNING] Empty list.\n");
    } else {
        Node *tempNode, *prevNode;
        int nodesCount = countNodes(start);
        if (pos > nodesCount) {
            printf("[ERR] Node doesn't exist.\n");
        } else if (pos > 1 && pos < nodesCount) {
            tempNode = prevNode = start;
            
            int i = 1;
            while (i < pos) {
                prevNode = tempNode;
                tempNode = tempNode->next;
                i++;
            }
            prevNode->next = tempNode->next;
            free(tempNode);
        } else {
            printf("[ERR] Invalid position.\n");
        }
    }
}

/**
 * deleteAll: delete entire list
 * @return void
*/
void deleteAll() {
    if (!start) {
        printf("\n[ERR] List was already empty.\n");
        return;
    } else {
        Node *tempNode;

        while (start) {
            tempNode = start;
            start = start->next;

            free(tempNode);
        }

        printf("Deleted entire list.\n");
    }
}

/**
 * traverse: traverse the list left to right with recursion
 * @param start the start node
 * @return void
*/
void traverse(Node *start) {
    if (!start) {
        return;
    } else {
        printf("%d->", start->data);
        traverse(start->next);
    }
}

/**
 * traverse: traverse the list right to left with recursion
 * @param start the start node
 * @return void
*/
void reverseTraverse(Node *start) {
    if (!start) {
        return;
    } else {
        reverseTraverse(start->next);
        printf("%d->", start->data);
    }
}

int main() {
    return 0;
}