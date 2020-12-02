# Linked Lists

A linked list is a non-sequential collection of data items. It is a dynamic data structure.
For every data item in a linked list, there is an associated pointer that would give the memory location of the next data item in the linked list.

**The data items in the linked list are not in consecutive memory locations.**

Linked lists are strong where arrays are weak.
Generally array's allocates the memory for all its elements in one block whereas linked lists use an entirely different strategy. Linked lists allocate memory for each element separately and only when necessary.

## Advantages

-   They are dynamic
-   They have efficient memory utilization.
-   Insertion and Deletions are easier and efficient.

## Disadvantages

-   They consume more space
-   Searching a particular element is difficult and time consuming

## Types of Linked Lists

-   Single
-   Double
-   Circular
-   Circular Double

<hr>
A linked list allocates space for each element separately in its own block of memory called a "node". The list gets an overall structure by using pointers to connect all its nodes together like the links in a chain. Each node contains two fields; a "data" field to store whatever element, and a "next" field which is a pointer used to link to the next node. Each node is allocated in the heap using malloc(), so the node memory continues to exist until it is explicitly de-allocated using free(). The front of the list is a
pointer to the “start” node.

![sll](./assets/sll.png)

The beginning of the linked list is stored in a "start" pointer which points to the first node.

### Basic operations

-   Creation
-   Insertion
-   Deletion
-   Traversing
