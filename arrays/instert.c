#include <stdio.h>

int main(){
    int arr[4];
    int n;
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("Enter the array: ");
    for(int i = 0; i < size; i++){
        scanf("%d", &n);
        arr[i] = n;
    }
    printf("The array is: ");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}