 #include <stdio.h>

int insertSorted(int array[], int *n, int ele) {
    int i, pos=0;

    // 1. Check if duplicate exists
    for (i = 0; i < *n; i++) {
        if (array[i] == ele) {
            printf("Element %d is a duplicate. Discarding input.\n", ele);
            return 0; 
        }
    }

    // 2. Find the right position (index) to maintain sorted order
    while (pos < *n && array[pos] < ele) 
        pos++;
    
    // 3. Shift elements and insert the element and increment size

    for (i =*n ; i > pos; i--) {
        array[i] = array[i - 1];
    }

    array[pos] = ele;
    (*n)++;
    return 1;
}

// (a) Binary Search - Iterative Approach
int iterative(int array[], int n, int ele) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == ele) 
		return mid;
        if (array[mid] < ele)
	       	low = mid + 1;
        else 
		high = mid - 1;
    }
    return -1;
}

// (b) Binary Search - Recursive Approach
int recursive(int array[], int low, int high, int ele) {
    if (low <= high){ 
	  //  return -1;

    int mid = low + (high - low) / 2;
    if (array[mid] == ele)
	    return mid;
    
    if (array[mid] < ele)
        return recursive(array, mid + 1, high, ele);
    
    return recursive(array, low, mid - 1, ele);
    }
    else return -1;
}

int main() {
    int array[100], n = 0, numElements, ele, searchEle, result;

    printf("enter number of elements to insert:\n ");
    scanf("%d", &numElements);

    for (int i = 0; i < numElements; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &ele);
        insertSorted(array, &n, ele);
    }

    // Display the array
    printf("\nCurrent Sorted Array: ");
    for (int i = 0; i < n; i++)
	    printf("%d ", array[i]);

    printf("\n\nEnter element to search: ");
    scanf("%d", &searchEle);

    // Testing Iterative
    result = iterative(array, n, searchEle);
    if (result != -1)
        printf("(Iterative) Element found at index: %d\n", result);
    else
        printf("(Iterative) Element not found.\n");

    // Testing Recursive
    result = recursive(array, 0, n - 1, searchEle);
    if (result != -1)
        printf("(Recursive) Element found at index: %d\n", result);
    else
        printf("(Recursive) Element not found.\n");

    return 0;
}
