#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;              // Data
    struct node* next;      // Pointer to next node in chain
} node;

// Forward declaration of functions used
void printList(node *head);
void printMenu();
node* nodeInsert(node *head);
void freeList(node *head);
node* nodeRemove(node *head);
node* insertHead(node *head);
node* deleteFromHead(node *head);

int main()
{
    int choice = 0;
    int loop = 1;

    // Initialize the head as NULL
    node *head = NULL;

    while(loop == 1) {
        printf("The linked list is:\n");
        printList(head);
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1: // Insert a node to the end of the list
            head = nodeInsert(head);
            break;
        case 2: // Remove a node from the end of the list
            head = nodeRemove(head);
            break;
        case 3: // Add a node to the head of the list
            head = insertHead(head);
            break;
        case 4: // Delete a node from the head of the list
            head = deleteFromHead(head);
            break;

        case 5: // Break out of the loop
            // A rather rudimentary way to break out of a loop, but I like it
            loop++;
            break;
        default:
            printf("Please enter a number 1-5:\n");
            break;
        }
    }
    freeList(head);
    return 0;
}

node* deleteFromHead(node *head) {
    node *temp = NULL;
    if (head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    temp = head->next;
    free(head);
    return temp;
}

node* insertHead(node *head) {
    // Grab data
    int data;
    printf("Enter the value to add at the beginning of the list: ");
    scanf("%d", &data);

    // If the list is empty, create the head
    if (head == NULL) {
        head = malloc(sizeof(node));
        head->value = data;
        head->next = NULL;
        return head;
    }

    // Otherwise, we create a node and point it to head
    // This is often done with a double pointer

    node *newHead = malloc(sizeof(node));
    newHead->value = data;
    newHead->next = head;
    head = newHead;
    return head;
}

node* nodeRemove(node *head) {

    // Check if the list is empty
    if (head == NULL) {
        printf("The list is empty. Please press another number.\n");
        return head;
    }

    // If the head is the only element
    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    node *temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;

    return head;
}

void freeList(node *head) {
    node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

node* nodeInsert(node *head) {
    // Grab data
    int data;
    printf("Enter the value to add to the end of the list: ");
    scanf("%d", &data);

    // If the list is empty, create the head
    if (head == NULL) {
        head = malloc(sizeof(node));
        head->value = data;
        // This is VERY important
        head->next = NULL;
        return head;
    }
    // Otherwise, the list is not empty and we traverse to the end
    node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    // Once this loop breaks, we are at the end of the list
    temp->next = malloc(sizeof(node));
    temp->next->value = data;
    // VERY important
    temp->next->next = NULL;

    return head;
}

void printList(node *head) {
    node *current = head;

    if(current == NULL) {
        printf("The list is empty.\n");
        return;
    }

    while(current != NULL) {
        if (current->next == NULL) {
            printf("%d\n", current->value);
            return;
        }
        else {
            printf("%d -> ", current->value);
            current = current->next;
        }
    }
}

void printMenu() {
    printf("Enter 1 to add a node to the end of the list\n");
    printf("Enter 2 to delete a node from the end of the list\n");
    printf("Enter 3 to add a node to the head of the list\n");
    printf("Enter 4 to delete a node from the head of the list\n");
    printf("Enter 5 to exit the program\n");
}
