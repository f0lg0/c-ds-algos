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

/**
 * selectionSort: selection sort implementation
 * @param arr an array of integers
 * @param arrSize the size of that array
 * @return a pointer to that sorted array
*/
int* selectionSort(int arr[], int arrSize) {
    int minIndex; 
  
    for (int i = 0; i < arrSize - 1; i++) { 
        minIndex = i; 
        for (int j = i + 1; j < arrSize; j++) 
          if (arr[j] < arr[minIndex]) 
            minIndex = j; 
  
        swap(&arr[minIndex], &arr[i]); 
    } 
    return arr;
}

/**
 * pivot: utility function for quick sort, it splits the given array in two small subarrays and swaps elements
 * @param arr the array 
 * @param arrSize length of the array
 * @param start starting index point of the array
 * @param end ending index point of the array 
*/
int pivot(int arr[], int arrSize, int start, int end) {
    int pivot = arr[start];
    int swapIndex = start;

    for (int i = start + 1; i < arrSize; i++) {
        if (pivot > arr[i]) {
            swapIndex++; // keeping track of how many elements we find so we will know the right index of the pivot
            swap(&arr[swapIndex], &arr[i]);
        }
    }

    swap(&arr[start], &arr[swapIndex]);

    return swapIndex;
}

/**
 * quickSort: quick sort implementation
 * @param arr an array of integers
 * @param arrSize length of the array
 * @param left the left index point of the array, at the first iteration this is going to be 0 
 * @param right the right index point of the array, athe the first iteration this is going to be arrSize - 1
 * @return a pointer to the sorted array
*/
int* quickSort(int arr[], int arrSize, int left, int right) {
    /* NOTE: we could avoid passing the array length everytime but I was too lazy */

    if (left < right) {
        int pivotIndex = pivot(arr, arrSize, left, right);

        // left
        quickSort(arr, arrSize, left, pivotIndex - 1);

        // right
        quickSort(arr, arrSize, pivotIndex + 1, right);
    }

    return arr;
}

int main() {
    return 0;
}