#include <stdio.h>
#include "recursion.h"

// Reverse a linked list using recursion
Node* reverseLinkedList(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;
    Node* rest = reverseLinkedList(head->next);
    head->next->next = head;
    head->next = NULL;
    return rest;
}

// Calculate factorial using recursion
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Calculate nth Fibonacci number using recursion
int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Find the maximum ID in the log list using recursion
int findMaxID(Node* head, int currentMax) {
    if (head == NULL) return currentMax;
    if (head->log.id > currentMax)
        currentMax = head->log.id;
    return findMaxID(head->next, currentMax);
}

// Recursive binary search in a sorted array of log entries by ID
int binarySearch(LogEntry arr[], int left, int right, int targetID) {
    if (left > right) return -1;
    int mid = (left + right) / 2;
    if (arr[mid].id == targetID) return mid;
    if (arr[mid].id > targetID)
        return binarySearch(arr, left, mid - 1, targetID);
    else
        return binarySearch(arr, mid + 1, right, targetID);
}

// Helper function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Recursive function to convert infix to postfix (simple version)
void infixToPostfix(char* infix, char* postfix, int* index, int* pIndex, char stack[], int top) {
    if (infix[*index] == '\0') {
        while (top >= 0) postfix[(*pIndex)++] = stack[top--];
        postfix[*pIndex] = '\0';
        return;
    }
    char token = infix[*index];
    if (token >= 'a' && token <= 'z') {
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

