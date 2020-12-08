/**
 * NOTE: this is another implementation of a queue.
 * This version is more suited for the DFS of a graph, basically we store the nodes in an array and the 
 * front and rear integers are basically indeces
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

struct queue {
    int items[SIZE];
    int front;
    int rear;
};

typedef struct queue Queue;

Queue* createQueue() {
    Queue* q = (Queue *)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;

    return q;
}

int isEmpty(Queue* q) {
    if (q->rear == -1) {
        return -1;
    } else {
        return 0;
    }
}

void enqueue(Queue* q, int value) {
    if (q->rear == SIZE - 1) {
        printf("[ERROR] Queue is full.\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;

    if (isEmpty(q)) {
        printf("[ERROR] Queue is empty.\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;

        if (q->front > q->rear) {;
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for (int i = q->front; i < q->rear + 1; i++) {
            printf("%d ", q->items[i]);
        }
    }
}