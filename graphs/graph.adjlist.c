#include <stdio.h>
#include <stdlib.h>
#include "helper/queue.h"

/**
 * node: piece of data containing a data field and a pointer to the next node of the list
*/
struct node {
    int data;
    struct node* next;
};

typedef struct node Node;

/**
 * graph: a graph with a set number of vertices, a pointer to a linked list and a pointer to an helper array used to traverse the graph
*/
struct graph {
    int numVertices;
    int* visited;
    Node** adjList; // pointer to struct node*
};

typedef struct graph Graph;

/**
 * createNode: creates a node given a numeric value
 * @param val numeric value
 * @return pointer to the newly created node
*/
Node* createNode(int val) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;

    return newNode;
}

/**
 * createGraph: creates a graph given a number of vertices where, for simplicity, vertices are identified by their indices
 * @param vertices number of vertices
 * @return pointer to the newly created graph
*/
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = malloc(vertices * sizeof(Node));
    graph->visited = malloc(vertices * sizeof(int));

    /*
        For simplicity, we use an unlabeled graph as opposed to a labeled one 
        i.e. the vertices are identified by their indices 0,1,2,3.
    */
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

/**
 * addEdge: creates a conection between two vertices
 * @param graph a graph structure
 * @param vertex1 a numeric value for the first vertex
 * @param vertex2 a numeric value for the second vertex
 * @return void
*/
void addEdge(Graph* graph, int vertex1, int vertex2) {
    Node* newNode = createNode(vertex1);

    // add edge from vertex1 to vertex2
    newNode->next = graph->adjList[vertex2];
    graph->adjList[vertex2] = newNode;

    newNode = createNode(vertex2);

    // add edge from vertex2 to vertex1
    newNode->next = graph->adjList[vertex1];
    graph->adjList[vertex1] = newNode;
}

/**
 * printGraph: prints the given graph by iterating trough it
 * @param graph a graph structure
 * @return void
*/
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjList[v];
        printf("\n Vertex %d: \n", v);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

/**
 * DFS: recursive depth first search implementation
 * @param graph a graph structure
 * @param vertex the numeric value of the node you want to start traversin from
 * @return void
*/
void DFS(Graph* graph, int startVertex) {
    Node* nodeAndNeighbors = graph->adjList[startVertex];
    Node* temp = nodeAndNeighbors;

    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    while (temp) {
        int connectedVertex = temp->data;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }

}

/**
 * BFS: iterative breadth first search implementation
 * @param graph a graph structure
 * @param startVertex the starting vertex
 * @return void 
*/
void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        // printQueue(q);
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int neighbor = temp->data;

            if (graph->visited[neighbor] == 0) {
                graph->visited[neighbor] = 1;
                enqueue(q, neighbor);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

/**
 * cleanVisitedArray: re-set the values back to 0 so we can DFS again
 * @param graph a graph structure
 * @return void
*/
void cleanVisitedArray(Graph* graph) {
    for (int i = 0; i < graph->numVertices + 1; i++) {
        graph->visited[i] = 0; 
    }
}

int main() {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);

    addEdge(graph, 1, 2);
    addEdge(graph, 2, 4);

    printGraph(graph);
    
    printf("\nDFS: ");
    DFS(graph, 0);
    printf("\n");

    cleanVisitedArray(graph);

    printf("BFS: ");
    BFS(graph, 0);

    return 0;
}