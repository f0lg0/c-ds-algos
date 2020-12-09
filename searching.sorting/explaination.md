# Searching and Sorting

Searching is used to find the location where an element is available. There are two types of search techniques:

-   linear search
-   binary search

Sorting allows an efficient arrangement of elements within a given data structure, there are two types of sorting techniques:

-   internal sorting
-   external sorting

If all the elements to be sorted are present in the main memory then such sorting is called internal sorting on the other hand, if some of the elements to be sorted are kept on the secondary storage, it is called external sorting. Here we study only internal sorting techniques.

## Linear Search

This is the simplest of all searching techniques. In this technique, an ordered or unordered list will be searched one by one from the beginning until the desired element is found. If the desired element is found in the list then the search is successful otherwise unsuccessful.

```c
#define N 10

// suppose that in the array there won't be negative numbers
int linsrch(int arr[N], int x) {
    int index = 0;

    while (index < N) {
        if (x == arr[index]) {
            return x;
            break;
        }
    }

    return -1; // element was not found
}
```

Time complexity of this algorithm is O(n).

We could even implement this with recursion.

## Binary Search

If we have ‘n’ records which have been ordered by keys so that x 1 < x 2 < ... < x n . When we are given a element ‘x’, binary search is used to find the corresponding element from the list. In case ‘x’ is present, we have to determine a value ‘j’ such that a[j] = x (successful search). If ‘x’ is not in the list then j is to set to zero (un successful search).

In Binary search we jump into the middle of the file, where we find key a[mid], and compare ‘x’ with a[mid]. If x = a[mid] then the desired record has been found.

If x < a[mid] then ‘x’ must be in that portion of the file that precedes a[mid]. Similarly, if a[mid] > x, then further search is only necessary in that part of the file which follows
a[mid].

If we use recursive procedure of finding the middle key a[mid] of the un-searched portion of a file, then every un-successful comparison of ‘x’ with a[mid] will eliminate roughly half the un-searched portion from consideration.

Since the array size is roughly halved after each comparison between ‘x’ and a[mid], and since an array of length ‘n’ can be halved only about log_2 n times before reaching a trivial length, the worst case complexity of Binary search is about log_2 n.

Pseudo code:

```
binsrch(a[], n, x) {
    low = 0; high = n-1;

    while (low <= high) {
        mid = (low + high) / 2
        if (x < a[mid]) {
            high = mid - 1;
        } else if (x > a[mid]) {
            low = mid + 1;
        } else {
            return mid
        }
    }
    return -1;
}
```

## Sorting Algos

### Bubble Sort

The bubble sort is easy to understand and program. The basic idea of bubble sort is to pass through the file sequentially several times. In each pass, we compare each element in the file with its successor i.e., X[i] with X[i+1] and interchange two element when they are not in proper order.

The larger elements will "bubble up" to the end of the array.
