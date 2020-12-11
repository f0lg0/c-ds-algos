#include <stdio.h>
#include <stdlib.h>

/**
 * node: a piece of data containing a numeric value, a pointer to the right node and a pointer to the left one
*/
struct node {
    int data;
    struct node* left;
    struct node* right;
};

typedef struct node Node;

/**
 * createNode: creates a new Node
 * @param val the value to place into the Node's data
 * @return pointer to new Node
*/
Node* createNode(int val) {
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/**
 * initList: initialize a dll of size "size" with nodes containing a 0
 * @param size the size of the list
 * @return void 
*/
void initList(Node* start, int size) {
    Node* newNode;
    Node* tempNode;

    for (int i = 0; i < size; i++) {
        newNode = createNode(0);
        if (!start) {
            start = newNode;
        } else {
            tempNode = start;
            while (tempNode->right) {
                tempNode = tempNode->right;
            }
            tempNode->right = newNode;
            newNode->left = tempNode;
        }
    }
}

/**
 * countNodes: counts the number of nodes in a list
 * @param start the start of the list
 * @return number of nodes
*/
int countNodes(Node* start) {
    if (!start)
        return 0;

    return 1 + countNodes(start->right);
}

/**
 * insertAtBeginning: insert a node at the beginning of the list
 * @param value the value of the node 
 * @return void
*/
void insertAtBeginning(Node** start, int val) {
    Node* newNode = createNode(val);

    if (!(*start)) {
        *start = newNode;
    } else {
        newNode->right = *start;
        (*start)->left = newNode;
        *start = newNode;
    }
}

/**
 * insertAtEnd: insert a node at the end of the list
 * @param value the value of the node
 * @return void
*/
void insertAtEnd(Node** start, int val) {
    Node* newNode = createNode(val);

    if (!(*start)) {
        *start = newNode;
    } else {
        Node* tempNode = *start;
        while (tempNode->right) {
            tempNode = tempNode->right;
        }
        tempNode->right = newNode;
        newNode->left = tempNode;
    }
}

/**
 * insertAtMid: insert a node at a given position
 * @param value the node's value
 * @param pos the position you want the node to be in
 * @return void
*/
void insertAtMid(Node** start, int val, int pos) {
    int nodesCount = countNodes(*start);

    if (pos > 1 && pos < nodesCount) {
        Node* newNode = createNode(val);
        Node* tempNode;
        Node* prevNode;

        tempNode = prevNode = *start;

        int i = 1;
        while (i < pos) {
            prevNode = tempNode;
            tempNode = tempNode->right;
            i++;
        }
        
        newNode->left = tempNode;
        newNode->right = tempNode->right;
        tempNode->right->left = newNode;
        tempNode->right = newNode;

    } else {
        printf("[ERR] Invalid postion.\n");
    }

}

/**
 * deleteAtBeginning: deletes the first node of the list
 * @return void
*/
void deleteAtBeginning(Node** start) {
    if (!(*start)) {
        printf("[WARNING] Empty list\n");
    } else {
        Node* tempNode = *start;
        *start = (*start)->right;
        (*start)->left = NULL;

        free(tempNode);
    }
}

/**
 * deleteAtEnd: deletes the last node of the list
 * @return void
*/
void deleteAtEnd(Node** start) {
    if (!(*start)) {
        printf("[WARNING] Empty list\n");
    } else {
        Node* tempNode = *start;
        while (tempNode->right) {
            tempNode = tempNode->right;
        }
        tempNode->left->right = NULL;
        free(tempNode);
    }
}

/**
 * deleteAtMid: deletes a node at a given position
 * @param pos the node's  position
 * @return void
*/
void deleteAtMid(Node** start, int pos) {
    if (!(*start)) {
        printf("[WARNING] Empty list\n");
    } else {
        int nodesCount = countNodes(*start);

        if (pos > 1 && pos < nodesCount) {
            Node* tempNode = *start;

            int i = 1;
            while (i < pos) {
                tempNode = tempNode->right;
                i++;
            }
            tempNode->right->left = tempNode->left;
            tempNode->left->right = tempNode->right;
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
void deleteAll(Node** start) {
    if (!(*start)) {
        printf("\n[ERR] List was already empty.\n");
        return;
    } else {
        Node* tempNode;

        while (*start) {
            tempNode = *start;
            *start = (*start)->right;

            free(tempNode);
        }
    }
}

/**
 * traverse: traverse the list left to right with recursion
 * @param start the start node
 * @return void
*/
void traverse(Node* start) {
    if (!start) {
        return;
    } else {
        printf("%d<->", start->data);
        traverse(start->right);
    }
}

/**
 * traverse: traverse the list right to left with recursion
 * @param start the start node
 * @return void
*/
void reverseTraverse(Node* start) {
    if (!start) {
        return;
    } else {
        reverseTraverse(start->right);
        printf("%d<->", start->data);
    }
}

int main() {
    Node* start = createNode(1);
    initList(start, 10);
    traverse(start);
    printf("\n");

    /* here you can mess around by adding and deleting nodes */
    deleteAtBeginning(&start);
    traverse(start);
    printf("\n");

    insertAtBeginning(&start, 5);
    traverse(start);
    printf("\n");

    insertAtEnd(&start, 9);
    traverse(start);
    printf("\n");

    insertAtMid(&start, 7, 3);
    traverse(start);
    printf("\n");

    deleteAtEnd(&start);
    traverse(start);
    printf("\n");

    deleteAll(&start);
    traverse(start);
    printf("\n");

    return 0;
}