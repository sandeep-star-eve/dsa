// (a) Allocating 1D array dynamically and access the elements
// (b) Allocating 2D array dynamically
// (1) contiguous rows with fixed no.of cols,
// (2) Non contiguous rows with variable no.of columns
// (c) Allocate memory for array of structure variables dynamically and
// access members of each element*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5
struct Student {
    int rollNo;
    char name[50];
    float marks;
};


struct Student classA[SIZE];

//float arr1[];// ={88.5,92.0};


int Array1D(){


    float *arr1;


    arr1 = malloc(SIZE*sizeof(float));

    
    for(int i = 0; i < SIZE; i++) {
        scanf("%f",arr1 + i);

    }

    for(int i = 0; i < SIZE; i++) 
        printf(" Marks: %.2f\n", arr1[i]);

    free(arr1);
    return 0;

    
    }


int Array2D() {
    float **arr2 = (float **)malloc(SIZE * sizeof(float *));
    
    if (arr2 == NULL) return 1;

    for (int i = 0; i < SIZE; i++) {
        arr2[i] = (float *)malloc(SIZE * sizeof(float));
    }

    printf("Enter marks for %dx%d matrix:\n", SIZE, SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%f", &arr2[i][j]);
        }
    }

    printf("\nThe Marks Matrix is:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%.2f ", arr2[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < SIZE; i++) {
        free(arr2[i]); 
    }
    free(arr2); 
    return 0;
}


int Arraystruct() {
    struct Student *temp = (struct Student*)malloc(sizeof(struct Student));
    if (temp == NULL) {
        return 1; 
    }


    classA[0] = *temp;

    printf("\nEnter details for %d students:\n", SIZE);
    for(int i = 0; i < SIZE; i++) {
        printf("Student %d (Roll, Name, Marks): ", i + 1);
        
        scanf("%d", &classA[i].rollNo);
        scanf("%s", classA[i].name);
        scanf("%f", &classA[i].marks);
    }

    for(int i = 0; i < SIZE; i++) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", classA[i].rollNo, classA[i].name, classA[i].marks);
    }

    free(temp);
    return 0;
}

int main() {
    char choice;
    
    while(1){
        printf("enter choice ");
        scanf(" %c",&choice);
        switch(choice)
        
    {
        case 'a':
                Array1D();
                break;

        case 'b':
                Array2D();
                break;


        case 'c':

                Arraystruct();
                break;
        }

    }    
    return 0;
}