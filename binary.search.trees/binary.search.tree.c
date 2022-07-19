#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct node {
    uint32_t item;
    struct node* parent;
    struct node* left;
    struct node* right;
};

struct node* create_node(uint32_t item) {
    struct node* tmp = malloc(sizeof(struct node));
    if (tmp == NULL) return NULL;

    tmp->item = item;
    tmp->parent = NULL;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

// O(h) where h is the height of the tree
struct node* search(struct node* root, uint32_t x) {
    if (root == NULL) return NULL;

    // base case
    if (root->item == x) return root;

    if (x < root->item) 
        return search(root->left, x);
    else 
        return search(root->right, x);
}

// leftmost node in the tree
struct node* min(struct node* root) {
    if (root == NULL) return NULL;

    struct node* min = root;

    while (min->left != NULL)
        min = min->left;

    return min;
}

// rightmost node in the tree
struct node* max(struct node* root) {
    if (root == NULL) return NULL;

    struct node* max = root;
    while (max->right != NULL)
        max = max->right;

    return max;
}

void traverse(struct node* root) {
    if (root != NULL) {
        traverse(root->left);
        printf("node at %p with item %d\n", root, root->item);
        traverse(root->right);
    }
}

void insert(struct node** tree, uint32_t x, struct node* parent) {
    struct node* tmp = NULL;

    if (*tree == NULL) {
        tmp = malloc(sizeof(struct node));
        tmp->item = x;
        tmp->left = tmp->right = NULL;
        tmp->parent = parent;
        
        // link into parent's record
        *tree = tmp;
        return;
    }

    if (x < (*tree)->item)
        insert(&((*tree)->left), x, *tree);
    else
        insert(&((*tree)->right), x, *tree);
}

void delete(struct node** tree, uint32_t x) {
    printf("looking for %d...\n", x);

    /*
     * 3 cases:
     *  1. node has no children --> clear the pointer to this node, free mem
     *  2. node has one child --> link grandchild to the given node parent (grand-node)
     *  3. node has 2 children --> relabel the given node with the key of its immediate successor in sorted order
     *                             This successor must be the leftmost descendant in the right subtree. 
     *                             Moving this to the point of deletion results in a properly-labeled binary search tree.
     *
     * steps:
     *  - traverse until we get to the node we want to delete
     *  - check children amount
     *  - procede with specified deletion method
     * */
    
    if ((*tree)->item == x) {
        // found the node
        printf("found note at %p with value %d\n", *tree, (*tree)->item);
        
        // tmp pointer so we can call free on the deleted node
        struct node* tmp = *tree;
        
        // case 1: no children
        if ((*tree)->left == NULL && (*tree)->right == NULL) {
            // procede checking where the node is (right or left of parent)
            // since we have already found the node, checking if the child item matches x is redundant
            
            if ((*tree)->parent->left != NULL) {
                (*tree)->parent->left = NULL;
            } else {
                (*tree)->parent->right = NULL;
            }
        } else if ((*tree)->left != NULL && (*tree)->right != NULL) {
            // case 3: has 2 children
            printf("node has 2 children: right at %p and left at %p\n", (*tree)->right, (*tree)->left);
            
        } else {
            // case 2: has one child
            
            if ((*tree)->left != NULL) {
                printf("node has a child on the left at %p\n", (*tree)->left);

                // deciding where to link the grandchild node
                if ((*tree)->parent->left == *tree) {
                    printf("the to be deleted node was on the left\n");
                    (*tree)->parent->left = (*tree)->left;
                } else {
                    printf("the to be deleted node was on the left\n");
                    (*tree)->parent->right = (*tree)->left;
                }
                printf("now node parent has left %p and rigth %p\n", (*tree)->parent->left, (*tree)->parent->right);
            } else {
                printf("node has a child on the right at %p\n", (*tree)->right);
            }
        }

        printf("freeing node at %p\n", (tmp));
        free(tmp);

        return;
    }

    if (x < (*tree)->item)
        delete(&((*tree)->left), x);
    else
        delete(&((*tree)->right), x);
}

int32_t main() {
    struct node* root = create_node(10);
    printf("root at %p with value %d\n", root, root->item);

    insert(&root, 12, root);
    insert(&root, 6, root);
    insert(&root, 3, root);
    insert(&root, 1, root);
    insert(&root, 99, root);
    // insert(&root, 5, root);

    traverse(root);

    delete(&root, 3);

    traverse(root);

    return 0;
}

