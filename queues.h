#ifndef QUEUES_H
#define QUEUES_H

#include <stdbool.h>

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

// Linked List Queue Functions
void initLinkedListQueue(LinkedListQueue* q);
void enqueueLog(LinkedListQueue* q, LogEntry newLog);
void dequeueLog(LinkedListQueue* q);
void peekLog(LinkedListQueue* q);
bool isEmptyLinkedList(LinkedListQueue* q);
bool isFullLinkedList(LinkedListQueue* q);

// Circular Queue Functions
void initCircularQueue(CircularQueue* q);
void enqueueCircular(CircularQueue* q, LogEntry value, int size);
void dequeueCircular(CircularQueue* q, int size);
bool isEmptyCircular(CircularQueue* q);
bool isFullCircular(CircularQueue* q, int size);

#endif
