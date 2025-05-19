#include "queues.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked List Queue Implementation 

void initLinkedListQueue(LinkedListQueue* q) {
    q->front = q->rear = NULL;
}

void enqueueLog(LinkedListQueue* q, LogEntry newLog) {
    LogEntry* newNode = (LogEntry*)malloc(sizeof(LogEntry));
    if (!newNode) {
        printf("Memory allocation failed!\n");
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
        printf("The queue is empty.\n");
        return;
    }

    LogEntry* temp = q->front;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
}

void peekLog(LinkedListQueue* q) {
    if (isEmptyLinkedList(q)) {
        printf("The queue is empty.\n");
        return;
    }

    LogEntry* firstLog = q->front;
    printf("First Log Entry:\n");
    printf("ID: %d\n", firstLog->id);
    printf("Message: %s\n", firstLog->message);
    printf("Timestamp: %s\n", firstLog->timestamp);
    printf("Severity: %d\n", firstLog->severity);
}

bool isEmptyLinkedList(LinkedListQueue* q) {
    return q->front == NULL;
}

bool isFullLinkedList(LinkedListQueue* q) {
    // Linked list implementation is theoretically never full
    // unless we run out of memory
    return false;
}

// Circular Queue Implementation

void initCircularQueue(CircularQueue* q) {
    q->front = q->rear = -1;
}

void enqueueCircular(CircularQueue* q, LogEntry value, int size) {
    if (isFullCircular(q, size)) {
        printf("The queue is full!\n");
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
        printf("Queue is empty!\n");
        return;
    }

    LogEntry removed = q->items[q->front];
    printf("Removed Log Entry:\n");
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

bool isEmptyCircular(CircularQueue* q) {
    return q->front == -1;
}

bool isFullCircular(CircularQueue* q, int size) {
    return (q->rear + 1) % size == q->front;
}
