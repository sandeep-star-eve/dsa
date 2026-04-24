#include<stdio.h>
#include<stdlib.h>

#define SIZE 5
void push(int *, int *, int);
void pop(int *, int *);
void display(int *);

int main(){
	int arr[SIZE];
	int top=-1;
	int choice, ele;

	for(int i=0; i<SIZE; i++)
		arr[i]=-99;
	while(1){
	printf("enter 1-> push 2->pop 3->display 4->exit\n");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1:
			printf("enter ele\n");
			scanf("%d", &ele);
			push(arr, &top, ele);// pass by add approach-3
			break;
		case 2:
			pop(arr, &top); // pass by add
			break;
		case 3:
			printf("stack status\n");
			printf("top->[%d]\n", top);
			display(arr);
			break;
		case 4:
			exit(1);
	}
	}
}

void pop(int a[], int *t){
	if(*t == -1){
		printf("stack is empty\n");
		return;
	}	
	int temp=a[(*t)];
	a[(*t)]=-99;
	(*t)--;
	printf("popped item is %d\n", temp);
}

void push(int a[], int *t, int ele){
	if(*t == SIZE-1){
		printf("stack is full\n");
		return;
	}

	(*t)++;
	a[(*t)]=ele;

}

void display(int a[]){
	for(int i=0; i<SIZE; i++)
		printf("[%d] ", a[i]);
	printf("\n");
}


