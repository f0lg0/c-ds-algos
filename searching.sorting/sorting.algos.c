#include <stdio.h>
#include <stdlib.h>


/**
 * swap: swaps two variables
 * @param x pointer to the first variable
 * @param y pointer to the second variable
 * @return void
*/
void swap(int* x, int* y) {
    int temp = *y;
    *y = *x;
    *x = temp; 
}

/**
 * bubbleSort: bubble sort implementation
 * @param arr an array of integers
 * @param arrSize the size of that array
 * @return a pointer to that sorted array
*/
int* bubbleSort(int arr[], int arrSize) {
    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = i + 1;  j < arrSize; j++) {
            if (arr[i] > arr[j]) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
    return arr;
}

int main() {
    int arr[] = {8, 4, 1, 9, 7, 5};
    int* resultArray = bubbleSort(arr, 6);

    for (int i = 0; i < 6; i++) {
        printf("%d ", *(resultArray + i));
    }

    printf("\n");

    return 0;
}