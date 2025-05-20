#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "QUEUES_H"

#define MAX_QUEUE_SIZE 100

typedef struct LogEntry {
    int id;
    char message[100];
    char timestamp[20];
    int severity;
    struct LogEntry* next;
} LogEntry;

typedef struct {
    LogEntry* front;
    LogEntry* rear;
} LinkedListQueue;

typedef struct {
    LogEntry items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} CircularQueue;

// --- Linked List Queue Implementation ---

bool isEmptyLinkedList(LinkedListQueue* q) {
    return q->front == NULL;
}

bool isFullLinkedList(LinkedListQueue* q) {
    // Theoretically unlimited unless memory runs out
    return false;
}

void initLinkedListQueue(LinkedListQueue* q) {
    q->front = q->rear = NULL;
}

void enqueueLog(LinkedListQueue* q, LogEntry newLog) {
    LogEntry* newNode = (LogEntry*)malloc(sizeof(LogEntry));
    if (!newNode) {
        printf("? Memory allocation failed!\n");
        return;
    }

    *newNode = newLog;
    newNode->next = NULL;

    if (isEmptyLinkedList(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeueLog(LinkedListQueue* q) {
    if (isEmptyLinkedList(q)) {
        printf("?? The Linked List queue is empty.\n");
        return;
    }

    LogEntry* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    printf("? Removed from Linked List Queue: ID = %d, Message = %s\n", temp->id, temp->message);
    free(temp);
}

void peekLog(LinkedListQueue* q) {
    if (isEmptyLinkedList(q)) {
        printf("?? The Linked List queue is empty.\n");
        return;
    }

    LogEntry* firstLog = q->front;
    printf("?? First Log Entry (Linked List):\n");
    printf("ID: %d\n", firstLog->id);
    printf("Message: %s\n", firstLog->message);
    printf("Timestamp: %s\n", firstLog->timestamp);
    printf("Severity: %d\n", firstLog->severity);
}

// --- Circular Queue Implementation ---

bool isEmptyCircular(CircularQueue* q) {
    return q->front == -1;
}

bool isFullCircular(CircularQueue* q, int size) {
    return (q->rear + 1) % size == q->front;
}

void initCircularQueue(CircularQueue* q) {
    q->front = q->rear = -1;
}

void enqueueCircular(CircularQueue* q, LogEntry value, int size) {
    if (isFullCircular(q, size)) {
        printf("?? Circular Queue is full!\n");
        return;
    }

    if (isEmptyCircular(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % size;
    }

    q->items[q->rear] = value;
}

void dequeueCircular(CircularQueue* q, int size) {
    if (isEmptyCircular(q)) {
        printf("?? Circular Queue is empty!\n");
        return;
    }

    LogEntry removed = q->items[q->front];
    printf("? Removed from Circular Queue:\n");
    printf("ID: %d\n", removed.id);
    printf("Message: %s\n", removed.message);
    printf("Timestamp: %s\n", removed.timestamp);
    printf("Severity: %d\n", removed.severity);

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % size;
    }
}

// --- Utility Functions ---

LogEntry createLogEntry() {
    LogEntry log;
    printf("?? Enter Log ID: ");
    scanf("%d", &log.id);
    getchar(); // consume newline
    printf("?? Enter Message: ");
    fgets(log.message, sizeof(log.message), stdin);
    log.message[strcspn(log.message, "\n")] = '\0';
    printf("?? Enter Timestamp: ");
    fgets(log.timestamp, sizeof(log.timestamp), stdin);
    log.timestamp[strcspn(log.timestamp, "\n")] = '\0';
    printf("?? Enter Severity: ");
    scanf("%d", &log.severity);
    getchar(); // consume newline
    log.next = NULL;
    return log;
}

void printMenu() {
    printf("\n===== ?? Log Queue Management Menu =====\n");
    printf("1. Enqueue (Linked List Queue)\n");
    printf("2. Dequeue (Linked List Queue)\n");
    printf("3. Peek   (Linked List Queue)\n");
    printf("4. Enqueue (Circular Queue)\n");
    printf("5. Dequeue (Circular Queue)\n");
    printf("0. Exit\n");
    printf("?? Enter your choice: ");
}

// --- Main Function ---

int main() {
    LinkedListQueue llQueue;
    CircularQueue cQueue;
    int choice;
    int circularSize = MAX_QUEUE_SIZE;

    initLinkedListQueue(&llQueue);
    initCircularQueue(&cQueue);

    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: {
                LogEntry log = createLogEntry();
                enqueueLog(&llQueue, log);
                printf("? Log added to Linked List Queue.\n");
                break;
            }
            case 2:
                dequeueLog(&llQueue);
                break;
            case 3:
                peekLog(&llQueue);
                break;
            case 4: {
                LogEntry log = createLogEntry();
                enqueueCircular(&cQueue, log, circularSize);
                printf("? Log added to Circular Queue.\n");
                break;
            }
            case 5:
                dequeueCircular(&cQueue, circularSize);
                break;
            case 0:
                printf("?? Exiting program. Goodbye!\n");
                break;
            default:
                printf("? Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}

