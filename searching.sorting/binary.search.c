#include <stdio.h>
#define SIZE 12

/**
 * binarySearch: binary searches a given target in an array
 * @param arr the array
 * @param x the target
 * @return the found target position or -1
*/
int binarySearch(int arr[SIZE], int x) {
    int low = 0;
    int high = SIZE - 1;

    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        printf("mid: %d\n", mid);

        if (x < arr[mid]) {
            high = mid - 1;
        } else if (x > arr[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int main() {
    int arr[SIZE] = {4, 7, 8, 9, 16, 20, 24, 38, 39, 45, 54, 77};
    int result =  binarySearch(arr, 7);
    
    printf("%d\n", result);

    return 0;
}