#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stacks.h"

#define MAX 100 // Maximum number of log entries the stack can hold

// Stack structure definition
// We use a fixed-size array to hold the log entries because it is simple and efficient for stack operations.
// This approach avoids dynamic memory allocation which keeps push/pop operations in constant time O(1).
typedef struct {
    LogEntry data[MAX]; // Array to store log entries
    int top;            // Index of the top element in the stack
} Stack;

// Initialize the stack by setting top to -1 (meaning it's empty)
void initStack(Stack* stack) {
    stack->top = -1;
}

// Check if the stack is empty (top == -1 means no elements)
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Check if the stack is full (top == MAX - 1 means no more space)
bool isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

// Push a new log entry to the top of the stack
bool push(Stack* stack, LogEntry log) {
    if (isFull(stack)) return false; // Do not push if stack is full
    stack->data[++stack->top] = log; // Increment top and assign the new log
    return true;
}

// Pop the top log entry from the stack
bool pop(Stack* stack, LogEntry* log) {
    if (isEmpty(stack)) return false; // Do not pop if stack is empty
    *log = stack->data[stack->top--]; // Return the top log and decrement top
    return true;
}

// Peek at the top log entry without removing it
bool peek(Stack* stack, LogEntry* log) {
    if (isEmpty(stack)) return false; // Nothing to peek at
    *log = stack->data[stack->top];
    return true;
}

// Recursive function to insert an element at the bottom of the stack
// This is used in the reverseStack function
void insertAtBottom(Stack* stack, LogEntry log) {
    if (isEmpty(stack)) {
        push(stack, log); // If stack is empty, insert at top (which is the bottom in original order)
    } else {
        LogEntry temp;
        pop(stack, &temp);           // Pop the top
        insertAtBottom(stack, log);  // Recursive call to insert log deeper
        push(stack, temp);           // Push back the popped element
    }
}

// Reverse the stack using recursion
// This uses insertAtBottom to re-insert elements in reverse order
void reverseStack(Stack* stack) {
    if (!isEmpty(stack)) {
        LogEntry temp;
        pop(stack, &temp);       // Pop the top
        reverseStack(stack);     // Reverse the rest of the stack
        insertAtBottom(stack, temp); // Insert the popped item at the bottom
    }
}

