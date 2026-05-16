#include<stdio.h>

int main()
{
    int arr[] = {2, 1, 5, 1, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    int result ;
    int windowSum = 0;

    for (int i =0; i < n; i++)
    {
        windowSum += arr[i];
        if (i >= k -1)
        {
            result = (result < windowSum) ? result : windowSum;
            windowSum -= arr[i -k + 1];
        }
    }

    printf("Minimum sum of subarray of size %d is: %d\n", k, result);
}