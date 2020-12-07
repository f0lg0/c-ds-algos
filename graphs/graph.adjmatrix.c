#include <stdio.h>
#include <stdlib.h>

#define V 4 // rows anc cols of the matrix

typedef int Matrix[V][V]; 

/**
 * initMatrix: initializes a matrix with all 0s
 * @param matrix a Matrix[V][V]
 * @return void
*/
void initMatrix(Matrix matrix) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            matrix[i][j] = 0;
        }
    }
}

/**
 * addEdge: creates a connection between two vertices
 * @param matrix a Matrix[V][V]
 * @param vertex1 a numeric value for the first vertex
 * @param vertex2 a numeric value for the second vertex
 * @return void
*/
void addEdge(Matrix matrix, int vertex1, int vertex2) {
    matrix[vertex1][vertex2] = 1;
    matrix[vertex2][vertex1] = 1;
}

/**
 * printMatrix: prints the given matrix by iterating through it
 * @param matrix a Matrix[V][V]
 * @return void
*/
void printMatrix(Matrix matrix) {
    for (int i = 0; i < V; i++) {
        printf("%d: ", i);
        for (int j = 0; j < V; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    return 0;
}