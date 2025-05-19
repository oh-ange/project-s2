#ifndef STACKS_H
#define STACKS_H

#include <stdbool.h>

// Structure to represent a log entry
typedef struct {
    int id;                  // Unique log ID
    char timestamp[20];      // Timestamp of the log
    char message[256];       // Message or content of the log
    int severity;            // Severity level (e.g., 1-5)
} LogEntry;

// Stack structure (defined in stacks.c)
typedef struct {
    LogEntry data[100];
    int top;
} Stack;

// Function declarations
void initStack(Stack* stack);
bool isEmpty(Stack* stack);
bool isFull(Stack* stack);
bool push(Stack* stack, LogEntry log);
bool pop(Stack* stack, LogEntry* log);
bool peek(Stack* stack, LogEntry* log);
void reverseStack(Stack* stack);

#endif // STACKS_H

