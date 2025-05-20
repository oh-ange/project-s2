#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "STACKS_H"


#define MAX 100 // Maximum number of log entries the stack can hold

// Structure to represent a log entry
typedef struct {
    int id;
    char timestamp[20];
    char message[256];
    int severity;
} LogEntry;

// Stack structure
typedef struct {
    LogEntry data[MAX];
    int top;
} Stack;

// Stack operations
void initStack(Stack* stack) {
    stack->top = -1;
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

bool push(Stack* stack, LogEntry log) {
    if (isFull(stack)) return false;
    stack->data[++stack->top] = log;
    return true;
}

bool pop(Stack* stack, LogEntry* log) {
    if (isEmpty(stack)) return false;
    *log = stack->data[stack->top--];
    return true;
}

bool peek(Stack* stack, LogEntry* log) {
    if (isEmpty(stack)) return false;
    *log = stack->data[stack->top];
    return true;
}

void insertAtBottom(Stack* stack, LogEntry log) {
    if (isEmpty(stack)) {
        push(stack, log);
    } else {
        LogEntry temp;
        pop(stack, &temp);
        insertAtBottom(stack, log);
        push(stack, temp);
    }
}

void reverseStack(Stack* stack) {
    if (!isEmpty(stack)) {
        LogEntry temp;
        pop(stack, &temp);
        reverseStack(stack);
        insertAtBottom(stack, temp);
    }
}

// Helper to input a new LogEntry
LogEntry createLogEntry() {
    LogEntry log;
    printf("Enter Log ID: ");
    scanf("%d", &log.id);
    getchar(); // Consume newline

    printf("Enter Timestamp: ");
    fgets(log.timestamp, sizeof(log.timestamp), stdin);
    log.timestamp[strcspn(log.timestamp, "\n")] = '\0';

    printf("Enter Message: ");
    fgets(log.message, sizeof(log.message), stdin);
    log.message[strcspn(log.message, "\n")] = '\0';

    printf("Enter Severity (1-5): ");
    scanf("%d", &log.severity);
    getchar();

    return log;
}

// Helper to display a log
void printLogEntry(LogEntry log) {
    printf("\nLog Entry:\n");
    printf("ID: %d\n", log.id);
    printf("Timestamp: %s\n", log.timestamp);
    printf("Message: %s\n", log.message);
    printf("Severity: %d\n", log.severity);
}

void printMenu() {
    printf("\n===== Log Stack Menu =====\n");
    printf("1. Push Log\n");
    printf("2. Pop Log\n");
    printf("3. Peek Top Log\n");
    printf("4. Reverse Stack\n");
    printf("0. Exit\n");
    printf("Select an option: ");
}

int main() {
    Stack stack;
    initStack(&stack);

    int choice;
    LogEntry log;

    do {
        printMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                log = createLogEntry();
                if (push(&stack, log)) {
                    printf("? Log pushed successfully.\n");
                } else {
                    printf("? Stack is full. Cannot push log.\n");
                }
                break;

            case 2:
                if (pop(&stack, &log)) {
                    printf("? Popped the following log:");
                    printLogEntry(log);
                } else {
                    printf("? Stack is empty. Nothing to pop.\n");
                }
                break;

            case 3:
                if (peek(&stack, &log)) {
                    printf("?? Top of the stack:");
                    printLogEntry(log);
                } else {
                    printf("? Stack is empty. Nothing to peek.\n");
                }
                break;

            case 4:
                reverseStack(&stack);
                printf("?? Stack reversed.\n");
                break;

            case 0:
                printf("?? Exiting program.\n");
                break;

            default:
                printf("?? Invalid option. Try again.\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

