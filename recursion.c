#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RECURSION_H"
// ---------------- Structures ----------------

typedef struct {
    int id;
    char timestamp[20];
    char message[256];
    int severity;
} LogEntry;

typedef struct Node {
    LogEntry log;
    struct Node* next;
} Node;

// ---------------- Stack for Logs ----------------
#define MAX 100

typedef struct {
    LogEntry data[MAX];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

int push(Stack* stack, LogEntry log) {
    if (isFull(stack)) return 0;
    stack->data[++stack->top] = log;
    return 1;
}

int pop(Stack* stack, LogEntry* log) {
    if (isEmpty(stack)) return 0;
    *log = stack->data[stack->top--];
    return 1;
}

// ---------------- Recursive Stack Reversal ----------------
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

// ---------------- Recursive Linked List Reversal ----------------
Node* reverseLinkedList(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;
    Node* rest = reverseLinkedList(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
}

// ---------------- Recursive Factorial ----------------
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// ---------------- Recursive Fibonacci ----------------
int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ---------------- Recursive Max ID in Linked List ----------------
int findMaxID(Node* head, int currentMax) {
    if (head == NULL) return currentMax;
    if (head->log.id > currentMax)
        currentMax = head->log.id;
    return findMaxID(head->next, currentMax);
}

// ---------------- Recursive Binary Search ----------------
int binarySearch(LogEntry arr[], int left, int right, int targetID) {
    if (left > right) return -1;
    int mid = (left + right) / 2;
    if (arr[mid].id == targetID) return mid;
    if (arr[mid].id > targetID)
        return binarySearch(arr, left, mid - 1, targetID);
    else
        return binarySearch(arr, mid + 1, right, targetID);
}

// ---------------- Recursive Infix to Postfix ----------------
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix, int* index, int* pIndex, char stack[], int top) {
    if (infix[*index] == '\0') {
        while (top >= 0) postfix[(*pIndex)++] = stack[top--];
        postfix[*pIndex] = '\0';
        return;
    }
    char token = infix[*index];
    if ((token >= 'a' && token <= 'z') || (token >= '0' && token <= '9')) {
        postfix[(*pIndex)++] = token;
    } else if (token == '(') {
        stack[++top] = token;
    } else if (token == ')') {
        while (top >= 0 && stack[top] != '(')
            postfix[(*pIndex)++] = stack[top--];
        top--; // pop '('
    } else {
        while (top >= 0 && precedence(stack[top]) >= precedence(token))
            postfix[(*pIndex)++] = stack[top--];
        stack[++top] = token;
    }
    (*index)++;
    infixToPostfix(infix, postfix, index, pIndex, stack, top);
}

// ---------------- Utility Functions ----------------
Node* createNode(LogEntry log) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->log = log;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    while (head) {
        printf("Log ID: %d, Message: %s\n", head->log.id, head->log.message);
        head = head->next;
    }
}

void freeList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

// ---------------- Main Function ----------------
int main() {
    printf("=== Recursive Function Tests ===\n");

    // Factorial Test
    int f = 5;
    printf("Factorial(%d) = %d\n", f, factorial(f));

    // Fibonacci Test
    int fib_n = 7;
    printf("Fibonacci(%d) = %d\n", fib_n, fibonacci(fib_n));

    // Stack reversal test
    Stack stack;
    initStack(&stack);
    LogEntry logs[3] = {
        {1, "2024-01-01", "Log One", 3},
        {2, "2024-01-02", "Log Two", 2},
        {3, "2024-01-03", "Log Three", 1}
    };
    for (int i = 0; i < 3; i++) push(&stack, logs[i]);
    reverseStack(&stack);
    printf("\nReversed Stack (top to bottom):\n");
    LogEntry temp;
    while (pop(&stack, &temp)) {
        printf("ID: %d, Message: %s\n", temp.id, temp.message);
    }

    // Linked list creation
    Node* head = NULL;
    for (int i = 0; i < 3; i++) {
        Node* node = createNode(logs[i]);
        node->next = head;
        head = node;
    }
    printf("\nOriginal Linked List:\n");
    printList(head);

    // Linked list reversal test
    head = reverseLinkedList(head);
    printf("\nReversed Linked List:\n");
    printList(head);

    // Find max ID recursively
    int maxID = findMaxID(head, 0);
    printf("\nMax Log ID in linked list = %d\n", maxID);

    // Binary search test
    // Sort array first (simple bubble sort)
    for (int i = 0; i < 3 - 1; ++i) {
        for (int j = 0; j < 3 - i - 1; ++j) {
            if (logs[j].id > logs[j + 1].id) {
                LogEntry tmp = logs[j];
                logs[j] = logs[j + 1];
                logs[j + 1] = tmp;
            }
        }
    }
    int targetID = 2;
    int foundIndex = binarySearch(logs, 0, 2, targetID);
    printf("\nBinary Search for ID %d: %sfound at index %d\n", targetID, foundIndex == -1 ? "Not " : "", foundIndex);

    // Infix to postfix test
    char infix[] = "a+b*(c-d)";
    char postfix[50];
    int idx = 0, pidx = 0;
    char stackArray[50];
    infixToPostfix(infix, postfix, &idx, &pidx, stackArray, -1);
    printf("\nInfix: %s\nPostfix (recursive): %s\n", infix, postfix);

    // Clean up linked list
    freeList(head);

    return 0;
}


