#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/wait.h>
#endif


#define MAX_APPS 100
#define MAX_LEN 100
#define RR_QUANTUM 5
// Define the structure for a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Define the structure for the linked list (execution queue)
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

// Initialize a linked list
LinkedList* initList() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Insert a node into the linked list (at the end)
void insertNode(LinkedList* list, int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = list->tail;
    if (list->tail != NULL) {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    if (list->head == NULL) {
        list->head = newNode;
    }
    list->size++;
}

// Remove a node from the linked list (from the beginning)
void removeNode(LinkedList* list) {
    Node* nodeToRemove = list->head;
    if (nodeToRemove != NULL) {
        list->head = nodeToRemove->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
        if (nodeToRemove == list->tail) {
            list->tail = NULL;
        }
        list->size--;
        free(nodeToRemove);
    }
}

// Print the contents of the linked list
void printList(LinkedList* list) {
    Node* currentNode = list->head;
    printf("Linked List: ");
    while (currentNode != NULL) {
        printf("%d ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

//sigstop-start
pid_t process_pid;

void stop_process(int signo) {
    if (signo == SIGSTOP) {
        kill(process_pid, SIGSTOP);
        printf("Process %d suspended\n", process_pid);
    }
}

void continue_process(int signo) {
    if (signo == SIGCONT) {
        kill(process_pid, SIGCONT);
        printf("Process %d resumed\n", process_pid);
    }
}
//sigstop-end

int main(int argc, char *argv[]) {
    LinkedList* list = initList();
    insertNode(list, 1);
    insertNode(list, 2);
    insertNode(list, 3);
    printList(list);
    removeNode(list);
    printList(list);
        if (argc != 2) {
        printf("Usage: %s [pid]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    process_pid = atoi(argv[1]);
    signal(SIGSTOP, stop_process);
    signal(SIGCONT, continue_process);

    while (1) {
        sleep(1);
    }
    return 0;
}
