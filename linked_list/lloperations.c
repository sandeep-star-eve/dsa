/*C program to implement single linked list.
Implement below metioned functions. Apply all required condition
check & validation like list empty or not, while inserting/deleting by
position validate the position.
a)insertAtEnd
b) insertAtBeg
c) insertAtPos
d) displayList
e)listNodeCount
f) deleteFromEnd
g) deleteFromBeg
h)deleteFromPos
i) deleteByElement
j) reverseDisplay
k)freeAllNode
l) reverseList
m)sortedList*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

/*
Structure
```
┌──────────────────────┐
│  struct node         │
├──────────────────────┤
│  int data            │
│  struct node *next   │
└──────────────────────┘

head = NULL initially
*/

// 1. INSERT AT END

/* BEFORE:  head → [10|•] → [20|•] → [30|NULL]

AFTER insertAtEnd(40):
         head → [10|•] → [20|•] → [30|•] → [40|NULL]
                                            │
                                            └─ new node
                                               (traverse to end)
- If list empty: head = new node
- Else: traverse to last node (where next == NULL)
- Attach new node at end

Before malloc:
temp = NULL (points to nothing)

After malloc:
temp = 1000 (points to address 1000)

Memory at address 1000:
┌──────────────┐
│ data: ?      │
│ next: NULL   │
└──────────────┘

After temp->data = 10:
┌──────────────┐
│ data: 10     │  ← temp->data gives us 10
│ next: NULL   │
└──────────────┘
Start:  head = NULL

Insert 10:
  ├─ Create temp with data=10
  ├─ if (head == NULL) TRUE
  └─ head = temp
     Result: head → [10|NULL]

Insert 20:
  ├─ Create temp with data=20
  ├─ if (head == NULL) FALSE
  ├─ Find last node (10)
  ├─ t1->next = temp
  └─ Result: head → [10|•] → [20|NULL]

  insertAtEnd(value):
    
    Step 1: CREATE & VALIDATE
    ├─ temp = malloc(...)     ← Allocate memory
    ├─ if (temp == NULL)      ← Check allocation
    └─ temp->data = value     ← Store value
    
    Step 2: FIND POSITION
    ├─ if (head == NULL)      ← First insert?
    │  └─ head = temp         ← Yes, make it head
    │
    └─ else                   ← No, find last
       ├─ t1 = head           ← Start from head
       ├─ while (t1->next != NULL)
       │  └─ t1 = t1->next    ← Walk to end
       └─ t1->next = temp     ← Attach temp
 */

void insertAtEnd(int ele) {
    struct node *temp = malloc(sizeof(struct node));
    if (temp == NULL) {
        perror("malloc");
        return;
    }
    temp->data = ele;
    temp->next = NULL;
    
    if (head == NULL) {
        head = temp;
    } else {
        struct node *t1 = head;
        while (t1->next != NULL)
            t1 = t1->next;
        t1->next = temp;
    }
}

// 2. INSERT AT BEGINNING
/*BEFORE:  head → [10|•] → [20|•] → [30|NULL]

AFTER insertAtBegin(5):
         head → [5|•] → [10|•] → [20|•] → [30|NULL]
                │
                └─ new node created
                   point to old head
				   
- Create node with data
- Point new node's next to current head
- Update head to new node  */
void insertAtBegin(int ele) {
    struct node *temp = malloc(sizeof(struct node));
    if (temp == NULL) {
        perror("malloc");
        return;
    }
    temp->data = ele;
    temp->next = head;
    head = temp;
}

// 3. INSERT AT POSITION (1-indexed, validate position)
void insertAtPos(int ele, int pos) {
    if (pos < 1) {
        printf("Invalid position\n");
        return;
    }
    
    if (pos == 1) {
        insertAtBegin(ele);
        return;
    }
    
    struct node *t1 = head;
    int count = 1;
    
    while (t1 != NULL && count < pos - 1) {
        t1 = t1->next;
        count++;
    }
    
    if (t1 == NULL) {
        printf("Position out of range\n");
        return;
    }
    
    struct node *temp = malloc(sizeof(struct node));
    if (temp == NULL) {
        perror("malloc");
        return;
    }
    temp->data = ele;
    temp->next = t1->next;
    t1->next = temp;
}

// 4. DISPLAY LIST
void displayList(void) {
    struct node *t1 = head;
    
    if (t1 == NULL) {
        printf("List is empty\n");
        return;
    }
    
    printf("List: ");
    while (t1 != NULL) {
        printf("%d -> ", t1->data);
        t1 = t1->next;
    }
    printf("NULL\n");
}

// 5. COUNT NODES
int listNodeCount(void) {
    struct node *t1 = head;
    int count = 0;
    
    while (t1 != NULL) {
        count++;
        t1 = t1->next;
    }
    return count;
}

// 6. DELETE FROM END
void deleteFromEnd(void) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if (head->next == NULL) {
        free(head);
        head = NULL;
        printf("Deleted last node\n");
        return;
    }
    
    struct node *t1 = head;
    while (t1->next->next != NULL)
        t1 = t1->next;
    
    free(t1->next);
    t1->next = NULL;
}

// 7. DELETE FROM BEGINNING
void deleteFromBegin(void) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct node *temp = head;
    head = head->next;
    free(temp);
}

// 8. DELETE FROM POSITION
void deleteFromPos(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if (pos < 1) {
        printf("Invalid position\n");
        return;
    }
    
    if (pos == 1) {
        deleteFromBegin();
        return;
    }
    
    struct node *t1 = head;
    int count = 1;
    
    while (t1->next != NULL && count < pos - 1) {
        t1 = t1->next;
        count++;
    }
    
    if (t1->next == NULL) {
        printf("Position out of range\n");
        return;
    }
    
    struct node *temp = t1->next;
    t1->next = temp->next;
    free(temp);
}

// 9. DELETE BY ELEMENT
void deleteByElement(int ele) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if (head->data == ele) {
        deleteFromBegin();
        return;
    }
    
    struct node *t1 = head;
    while (t1->next != NULL && t1->next->data != ele)
        t1 = t1->next;
    
    if (t1->next == NULL) {
        printf("Element not found\n");
        return;
    }
    
    struct node *temp = t1->next;
    t1->next = temp->next;
    free(temp);
}

// 10. REVERSE DISPLAY (recursive)
void reverseDisplay_helper(struct node *t1) {
    if (t1 == NULL)
        return;
    reverseDisplay_helper(t1->next);
    printf("%d -> ", t1->data);
}

void reverseDisplay(void) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("Reverse: ");
    reverseDisplay_helper(head);
    printf("NULL\n");
}

// 11. FREE ALL NODES
void freeAllNodes(void) {
    struct node *t1 = head;
    while (t1 != NULL) {
        struct node *temp = t1;
        t1 = t1->next;
        free(temp);
    }
    head = NULL;
    printf("List freed\n");
}

// 12. REVERSE LIST (modify pointers)
void reverseList(void) {
    if (head == NULL || head->next == NULL)
        return;
    
    struct node *prev = NULL, *curr = head, *next;
    
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

// 13. SORTED INSERT
void sortedInsert(int ele) {
    struct node *temp = malloc(sizeof(struct node));
    if (temp == NULL) {
        perror("malloc");
        return;
    }
    temp->data = ele;
    temp->next = NULL;
    
    if (head == NULL || head->data >= ele) {
        temp->next = head;
        head = temp;
        return;
    }
    
    struct node *t1 = head;
    while (t1->next != NULL && t1->next->data < ele)
        t1 = t1->next;
    
    temp->next = t1->next;
    t1->next = temp;
}
void menu(void) {
	printf("Menu:\n");
	printf("a) Insert at end\n");
	printf("b) Insert at beginning\n");
	printf("c) Insert at position\n");
	printf("d) Display list\n");
	printf("e) Count nodes\n");
	printf("f) Delete from end\n");
	printf("g) Delete from beginning\n");
	printf("h) Delete from position\n");
	printf("i) Delete by element\n");
	printf("j) Reverse display\n");
	printf("k) Free all nodes\n");
	printf("l) Reverse list\n");
	printf("m) Sorted insert\n");
}	

int main(void)
{
	char choice;
    int ele;
	int pos;
	


	while(1)
	{
		printf("Enter choice\n");
		scanf(" %c",    &choice);
        switch(choice)
	 {
 		 case 'a':

             printf("Enter element to insert at end\n");
   			 scanf("%d", &ele);
			 insertAtEnd(ele);
			 break;
	        case'b':
			printf("Enter element to insert at beginning\n");
   			 scanf("%d", &ele);
			 insertAtBegin(ele);
			  break;

	        case'c':
			printf("Enter position to insert\n");
   			 scanf("%d", &pos);
			 printf("Enter element to insert at beginning\n");
   			 scanf("%d", &ele);
			 insertAtPos(ele, pos);
			  break;

	       case'd':
		        displayList();
			 break;

			case'e':
			listNodeCount();
			 break;

			case'f':
			deleteFromEnd();
			 break;

			case'g':
			deleteFromBegin();
			 break;

			case'h':
			printf("Enter position to delete\n");
   			 scanf("%d", &pos);
			deleteFromPos(pos);
			 break;

			case'i':
			printf("Enter element to delete\n");
   			 scanf("%d", &ele);
			deleteByElement(ele);
			 break;

			case'j':
			reverseDisplay();
			 break;
		case'k':
			freeAllNodes();
			 break;
		case'l':
			 reverseList();
			 break;

		case'm':
			 printf("Enter element to insert in sorted order\n");
   			 scanf("%d", &ele);
			 sortedInsert(ele);
			 break;
		 default:
			 menu();
			 break;
	 }
	

}
return 0;

}
