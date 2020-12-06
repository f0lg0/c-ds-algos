#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * node: a piece of data containing a numeric value, a left child and a right one.
*/
struct node {
    int data;
    struct node *rightChild;
    struct node *leftChild;
};

typedef struct node Node;

Node *nodesQueue[50]; // queue of nodes that we need to do a breadth first search (level order)
int nodesCount = 0; // total number of nodes in the binary tree

/**
 * createNode: creates a node
 * @param val the numeric value of the node
 * @return a pointer to that newly created node
*/
Node* createNode(int val) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = val;
    temp->leftChild = NULL;
    temp->rightChild = NULL;

    return temp;
}

/**
 * createFullTree: recursively generate a FULL binary tree given a number of levels
 * @param root a pointer to the root of the node
 * @param levels number of levels of the tree
 * @return void
*/
void createFullTree(Node *root, int levels) {
    if (root) {
        if (levels > 0) {
            root->leftChild = createNode((rand() % 100) + 1);
            root->rightChild = createNode((rand() % 100) + 1);
            createFullTree(root->leftChild, --levels);
            createFullTree(root->rightChild, levels--);
        } else {
            return;
        }
    }
}

/**
 * makeQueue: build the queue of nodes for level order displaying
 * @param root the root of the tree
 * @param parent where to start building the queue (0 for root)
*/
void makeQueue(Node *root, int parent) {
    if (root) {
        nodesCount++;
        nodesQueue[parent] = root;
        makeQueue(root->leftChild, (parent * 2) + 1);
        makeQueue(root->rightChild, (parent * 2) + 2);
    }
}

/**
 * printTree: displays the tree in 2D, easy to understand 
 * @param root the root of the tree
 * @param space how much space from the left of the terminal
 * @return void
*/
void printTree(Node *root, int space) {
    if (!root) 
        return; 
  
    space += 5; 
  
    printTree(root->rightChild, space); 
    printf("\n"); 

    for (int i = 5; i < space; i++) 
        printf(" "); 

    printf("%d\n", root->data); 
  
    printTree(root->leftChild, space); 
}

/**
 * inorder: prints the tree with the inorder method (see explaination)
 * @param root the root of the tree
*/
void inorder(Node *root) {
    if (root) {
        inorder(root->leftChild);
        printf("%3d", root->data);
        inorder(root->rightChild);
    }
}

/**
 * preorder: prints the tree with the preorder method (see explaination)
 * @param root the root of the tree
*/
void preorder(Node *root) {
    if (root) {
        printf("%4d", root->data);
        preorder(root->leftChild);
        preorder(root->rightChild);
    }
}

/**
 * postorder: prints the tree with the postorder method (see explaination)
 * @param root the root of the tree
*/
void postorder(Node *root) {
    if (root) {
        postorder(root->leftChild);
        postorder(root->rightChild);
        printf("%4d", root->data);
    }
}

/**
 * level order: prints the tree with the breadth first search method (see explaination)
 * @param root the root of the tree
*/
void levelorder(Node *root, Node *nodesQueue[]) {
    for (int i = 0; i < nodesCount; i++) {
        if (nodesQueue[i]) {
            printf("%4d", nodesQueue[i]->data);
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    return 0;
}