#ifndef RECURSION_H
#define RECURSION_H

// Structure for a log entry
typedef struct {
    int id;                  // Unique log ID
    char timestamp[20];      // Timestamp of the log
    char message[256];       // Log message
    int severity;            // Severity level
} LogEntry;

// Node structure for a singly linked list
typedef struct Node {
    LogEntry log;
    struct Node* next;
} Node;

// Function declarations

// Reverse a singly linked list using recursion
Node* reverseLinkedList(Node* head);

// Calculate factorial of a number using recursion
int factorial(int n);

// Calculate nth Fibonacci number using recursion
int fibonacci(int n);

// Find the maximum log ID in a linked list using recursion
int findMaxID(Node* head, int currentMax);

// Perform recursive binary search in a sorted array of log entries by ID
int binarySearch(LogEntry arr[], int left, int right, int targetID);

// Convert infix expression to postfix using recursion
void infixToPostfix(char* infix, char* postfix, int* index, int* pIndex, char stack[], int top);

#endif // RECURSION_H

