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
        printf("traversing: node at %p with item %d\n", root, root->item);
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
        printf("node created at %p value %d and parent is at %p with item %d\n", tmp, tmp->item, tmp->parent, tmp->parent->item);
        
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

    struct node* target = search((*tree), x);
    
    // tmp pointer so we can call free on the deleted node
    struct node* tmp = target;
    
    // case 1: no children
    if (target->left == NULL && target->right == NULL) {
        // procede checking where the node is (right or left of parent)
        // since we have already found the node, checking if the child item matches x is redundant
        
        if (target->parent->left != NULL) {
            target->parent->left = NULL;
        } else {
            target->parent->right = NULL;
        }

        free(tmp);
    } else if (target->left != NULL && target->right != NULL) {
        // case 3: has 2 children

        // get to the leftmost node in the right branch (min node of right branch)
        struct node* lnrb = min(target->right);
        target->item = lnrb->item;

        delete(&lnrb, lnrb->item);
    } else {
        // case 2: has one child
        if (target->left != NULL) {
            // deciding where to link the grandchild node
            if (target->parent->left == target) {
                target->parent->left = target->left;
            } else {
                target->parent->right = target->left;
            }
        } else {
            // deciding where to link the grandchild node
            if (target->parent->left == target) {
                target->parent->left = target->right;
            } else {
                target->parent->right = target->right;
            }
        }

        free(tmp);
    }
}

int32_t main() {
    struct node* root = create_node(5);
    printf("root at %p with value %d\n", root, root->item);

    insert(&root, 12, NULL);
    insert(&root, 2, NULL);
    insert(&root, 3, NULL);
    insert(&root, 1, NULL);
    insert(&root, 21, NULL);
    insert(&root, 9, NULL);
    insert(&root, 25, NULL);
    insert(&root, 19, NULL);

    traverse(root);
    delete(&root, 12);
    traverse(root);

    return 0;
}

