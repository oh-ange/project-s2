#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedLists.h"
#include "circularLists.h"
#include "log_tree.h"
#include "stacks.h"
#include "bidirectionalLinkedLists.h"
#include "recursion.h"

// Helper function to display a log entry
void displayLogEntry(LogEntry log) {
    printf("ID: %d | Timestamp: %s | Message: %s | Severity: %d\n", 
           log.id, log.timestamp, log.message, log.severity);
}

// Helper function to display a tree log entry
void displayTreeLog(Log log) {
    printf("Timestamp: %d | Message: %s\n", log.timestamp, log.message);
}

// Helper function to input a log entry
LogEntry inputLogEntry() {
    LogEntry newLog;
    printf("Enter log details:\n");
    printf("ID: ");
    scanf("%d", &newLog.id);
    
    // Allocate memory for strings
    newLog.timestamp = (char*)malloc(20 * sizeof(char));
    newLog.message = (char*)malloc(256 * sizeof(char));
    
    printf("Timestamp: ");
    scanf("%19s", newLog.timestamp);
    printf("Message: ");
    scanf(" %255[^\n]", newLog.message); // Read until newline
    printf("Severity (1-10): ");
    scanf("%d", &newLog.severity);
    return newLog;
}

// Helper function to input a bidirectional log entry
LogEntry inputBidirectionalLogEntry() {
    LogEntry newLog;
    printf("Enter log details:\n");
    printf("ID: ");
    scanf("%d", &newLog.id);
    printf("Keyword: ");
    scanf("%99s", newLog.keyword);
    printf("Timestamp (YYYY-MM-DD HH:MM:SS): ");
    scanf("%19s", newLog.timestamp);
    printf("Severity (1-5): ");
    scanf("%d", &newLog.severity);
    return newLog;
}

// Helper function to input a tree log entry
Log inputTreeLog() {
    Log newLog;
    printf("Enter log details:\n");
    printf("Timestamp (as integer): ");
    scanf("%d", &newLog.timestamp);
    printf("Message: ");
    scanf(" %255[^\n]", newLog.message);
    return newLog;
}

// Function to free linked list memory
void freeLinkedList(LogEntry* head) {
    LogEntry* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->timestamp);
        free(temp->message);
        free(temp);
    }
}

// Function to free circular linked list memory
void freeCircularList(LogEntry* head) {
    if (head == NULL) return;
    
    LogEntry* current = head;
    LogEntry* temp;
    
    do {
        temp = current;
        current = current->next;
        free(temp);
    } while (current != head);
}

// Function to free tree memory
void freeTree(TTree* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Function to free bidirectional list memory
void freeBidirectionalList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Initialize all data structures
    LogEntry* linkedListHead = NULL;
    LogEntry* circularListHead = NULL;
    TTree* treeRoot = NULL;
    Stack logStack;
    initStack(&logStack);
    Node* bidirectionalHead = NULL;
    
    int choice, subChoice, id, pos, severity, timestamp;
    char timestampStr[20], keyword[100];
    LogEntry log;
    LogEntry* foundLog;
    Node* foundNode;
    TTree* foundTreeNode;
    
    printf("=== Log Management System ===\n");
    
    do {
        printf("\nMain Menu:\n");
        printf("1. Linked List Operations\n");
        printf("2. Circular Linked List Operations\n");
        printf("3. Binary Search Tree Operations\n");
        printf("4. Stack Operations\n");
        printf("5. Bidirectional Linked List Operations\n");
        printf("6. Recursion Examples\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Linked List Operations
                do {
                    printf("\nLinked List Operations:\n");
                    printf("1. Insert at beginning\n");
                    printf("2. Insert at end\n");
                    printf("3. Insert after position\n");
                    printf("4. Delete by ID\n");
                    printf("5. Delete by timestamp\n");
                    printf("6. Delete first\n");
                    printf("7. Delete last\n");
                    printf("8. Search by ID\n");
                    printf("9. Search by keyword\n");
                    printf("10. Search by timestamp\n");
                    printf("11. Sort by date\n");
                    printf("12. Sort by severity\n");
                    printf("13. Reverse list\n");
                    printf("14. Count logs\n");
                    printf("15. Display all logs\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            log = inputLogEntry();
                            insertAtBeginning(&linkedListHead, log);
                            break;
                        case 2:
                            log = inputLogEntry();
                            insertAtEnd(&linkedListHead, log);
                            break;
                        case 3:
                            log = inputLogEntry();
                            printf("Enter position to insert after: ");
                            scanf("%d", &pos);
                            insertAfterPosition(&linkedListHead, log, pos);
                            break;
                        case 4:
                            printf("Enter ID to delete: ");
                            scanf("%d", &id);
                            deleteById(&linkedListHead, id);
                            break;
                        case 5:
                            printf("Enter timestamp to delete: ");
                            scanf("%s", timestampStr);
                            deleteByTimestamp(&linkedListHead, timestampStr);
                            break;
                        case 6:
                            deleteFirst(&linkedListHead);
                            break;
                        case 7:
                            deleteLast(&linkedListHead);
                            break;
                        case 8:
                            printf("Enter ID to search: ");
                            scanf("%d", &id);
                            foundLog = searchByID(linkedListHead, id);
                            if (foundLog) displayLogEntry(*foundLog);
                            else printf("Log not found.\n");
                            break;
                        case 9:
                            printf("Enter keyword to search: ");
                            scanf("%s", keyword);
                            foundLog = searchByKeyword(linkedListHead, keyword);
                            if (foundLog) displayLogEntry(*foundLog);
                            else printf("Log not found.\n");
                            break;
                        case 10:
                            printf("Enter timestamp to search: ");
                            scanf("%s", timestampStr);
                            foundLog = searchByTimestamp(linkedListHead, timestampStr);
                            if (foundLog) displayLogEntry(*foundLog);
                            else printf("Log not found.\n");
                            break;
                        case 11:
                            sortByDate(&linkedListHead);
                            printf("List sorted by date.\n");
                            break;
                        case 12:
                            sortBySeverity(&linkedListHead);
                            printf("List sorted by severity.\n");
                            break;
                        case 13:
                            reverseList(&linkedListHead);
                            printf("List reversed.\n");
                            break;
                        case 14:
                            printf("Total logs: %d\n", totalLogs(linkedListHead));
                            break;
                        case 15:
                            printf("\nAll Logs:\n");
                            LogEntry* temp = linkedListHead;
                            while (temp != NULL) {
                                displayLogEntry(*temp);
                                temp = temp->next;
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 2: // Circular Linked List Operations
                do {
                    printf("\nCircular Linked List Operations:\n");
                    printf("1. Insert at beginning\n");
                    printf("2. Insert at end\n");
                    printf("3. Insert after position\n");
                    printf("4. Delete by ID\n");
                    printf("5. Delete by timestamp\n");
                    printf("6. Delete first\n");
                    printf("7. Delete last\n");
                    printf("8. Search by ID\n");
                    printf("9. Search by keyword\n");
                    printf("10. Search by timestamp\n");
                    printf("11. Sort by date\n");
                    printf("12. Sort by severity\n");
                    printf("13. Reverse list\n");
                    printf("14. Count logs\n");
                    printf("15. Display all logs\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            log = inputLogEntry();
                            insertAtBeginning(&circularListHead, log);
                            break;
                        case 2:
                            log = inputLogEntry();
                            insertAtEnd(&circularListHead, log);
                            break;
                        case 3:
                            log = inputLogEntry();
                            printf("Enter position to insert after: ");
                            scanf("%d", &pos);
                            insertAfterPosition(&circularListHead, log, pos);
                            break;
                        case 4:
                            printf("Enter ID to delete: ");
                            scanf("%d", &id);
                            deleteById(&circularListHead, id);
                            break;
                        case 5:
                            printf("Enter timestamp to delete: ");
                            scanf("%s", timestampStr);
                            deleteByTimestamp(&circularListHead, timestampStr);
                            break;
                        case 6:
                            deleteFirst(&circularListHead);
                            break;
                        case 7:
                            deleteLast(&circularListHead);
                            break;
                        case 8:
                            printf("Enter ID to search: ");
                            scanf("%d", &id);
                            foundLog = searchByID(circularListHead, id);
                            if (foundLog) displayLogEntry(*foundLog);
                            else printf("Log not found.\n");
                            break;
                        case 9:
                            printf("Enter keyword to search: ");
                            scanf("%s", keyword);
                            foundLog = searchByKeyword(circularListHead, keyword);
                            if (foundLog) displayLogEntry(*foundLog);
                            else printf("Log not found.\n");
                            break;
                        case 10:
                            printf("Enter timestamp to search: ");
                            scanf("%s", timestampStr);
                            foundLog = searchByTimestamp(circularListHead, timestampStr);
                            if (foundLog) displayLogEntry(*foundLog);
                            else printf("Log not found.\n");
                            break;
                        case 11:
                            sortByDate(&circularListHead);
                            printf("List sorted by date.\n");
                            break;
                        case 12:
                            sortBySeverity(&circularListHead);
                            printf("List sorted by severity.\n");
                            break;
                        case 13:
                            reverseList(&circularListHead);
                            printf("List reversed.\n");
                            break;
                        case 14:
                            printf("Total logs: %d\n", totalLogs(&circularListHead));
                            break;
                        case 15:
                            printf("\nAll Logs:\n");
                            if (circularListHead != NULL) {
                                LogEntry* temp = circularListHead;
                                do {
                                    displayLogEntry(*temp);
                                    temp = temp->next;
                                } while (temp != circularListHead);
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 3: // Binary Search Tree Operations
                do {
                    printf("\nBinary Search Tree Operations:\n");
                    printf("1. Insert log\n");
                    printf("2. Delete log by timestamp\n");
                    printf("3. Search log by timestamp\n");
                    printf("4. In-order traversal\n");
                    printf("5. Pre-order traversal\n");
                    printf("6. Post-order traversal\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1: {
                            Log newLog = inputTreeLog();
                            treeRoot = insertLog(treeRoot, newLog);
                            break;
                        }
                        case 2:
                            printf("Enter timestamp to delete: ");
                            scanf("%d", &timestamp);
                            treeRoot = deleteLog(treeRoot, timestamp);
                            break;
                        case 3:
                            printf("Enter timestamp to search: ");
                            scanf("%d", &timestamp);
                            foundTreeNode = searchLog(treeRoot, timestamp);
                            if (foundTreeNode) {
                                printf("Found: ");
                                displayTreeLog(foundTreeNode->log);
                            } else {
                                printf("Log not found.\n");
                            }
                            break;
                        case 4:
                            printf("In-order traversal:\n");
                            inOrderTraversal(treeRoot);
                            break;
                        case 5:
                            printf("Pre-order traversal:\n");
                            preOrderTraversal(treeRoot);
                            break;
                        case 6:
                            printf("Post-order traversal:\n");
                            postOrderTraversal(treeRoot);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 4: // Stack Operations
                do {
                    printf("\nStack Operations:\n");
                    printf("1. Push log\n");
                    printf("2. Pop log\n");
                    printf("3. Peek at top log\n");
                    printf("4. Reverse stack\n");
                    printf("5. Check if stack is empty\n");
                    printf("6. Display all logs (destructive)\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1: {
                            LogEntry log;
                            printf("Enter log details:\n");
                            printf("ID: ");
                            scanf("%d", &log.id);
                            printf("Timestamp: ");
                            scanf("%19s", log.timestamp);
                            printf("Message: ");
                            scanf(" %255[^\n]", log.message);
                            printf("Severity (1-5): ");
                            scanf("%d", &log.severity);
                            
                            if (!push(&logStack, log)) {
                                printf("Stack is full!\n");
                            }
                            break;
                        }
                        case 2:
                            if (pop(&logStack, &log)) {
                                printf("Popped log:\n");
                                displayLogEntry(log);
                            } else {
                                printf("Stack is empty!\n");
                            }
                            break;
                        case 3:
                            if (peek(&logStack, &log)) {
                                printf("Top log:\n");
                                displayLogEntry(log);
                            } else {
                                printf("Stack is empty!\n");
                            }
                            break;
                        case 4:
                            reverseStack(&logStack);
                            printf("Stack reversed.\n");
                            break;
                        case 5:
                            if (isEmpty(&logStack)) {
                                printf("Stack is empty.\n");
                            } else {
                                printf("Stack is not empty.\n");
                            }
                            break;
                        case 6:
                            printf("Stack contents (will be emptied):\n");
                            while (pop(&logStack, &log)) {
                                displayLogEntry(log);
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 5: // Bidirectional Linked List Operations
                do {
                    printf("\nBidirectional Linked List Operations:\n");
                    printf("1. Insert at beginning\n");
                    printf("2. Insert at end\n");
                    printf("3. Insert at position\n");
                    printf("4. Delete by ID\n");
                    printf("5. Delete by timestamp\n");
                    printf("6. Delete first\n");
                    printf("7. Delete last\n");
                    printf("8. Delete at position\n");
                    printf("9. Search by ID\n");
                    printf("10. Search by keyword\n");
                    printf("11. Search by timestamp\n");
                    printf("12. Sort by date\n");
                    printf("13. Sort by severity\n");
                    printf("14. Reverse list\n");
                    printf("15. Count logs\n");
                    printf("16. Display forward\n");
                    printf("17. Display backward\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1: {
                            LogEntry log = inputBidirectionalLogEntry();
                            bidirectionalHead = insertAtBeginning(bidirectionalHead, log);
                            break;
                        }
                        case 2: {
                            LogEntry log = inputBidirectionalLogEntry();
                            bidirectionalHead = insertAtEnd(bidirectionalHead, log);
                            break;
                        }
                        case 3: {
                            LogEntry log = inputBidirectionalLogEntry();
                            printf("Enter position to insert at: ");
                            scanf("%d", &pos);
                            bidirectionalHead = insertAtPosition(bidirectionalHead, log, pos);
                            break;
                        }
                        case 4:
                            printf("Enter ID to delete: ");
                            scanf("%d", &id);
                            bidirectionalHead = deleteByID(bidirectionalHead, id);
                            break;
                        case 5:
                            printf("Enter timestamp to delete: ");
                            scanf("%s", timestampStr);
                            bidirectionalHead = deleteByTimestamp(bidirectionalHead, timestampStr);
                            break;
                        case 6:
                            bidirectionalHead = deleteFirst(bidirectionalHead);
                            break;
                        case 7:
                            bidirectionalHead = deleteLast(bidirectionalHead);
                            break;
                        case 8:
                            printf("Enter position to delete: ");
                            scanf("%d", &pos);
                            bidirectionalHead = deleteMiddle(bidirectionalHead, pos);
                            break;
                        case 9:
                            printf("Enter ID to search: ");
                            scanf("%d", &id);
                            foundNode = searchByID(bidirectionalHead, id);
                            if (foundNode) {
                                printf("Found: ");
                                displayLogEntry(foundNode->log);
                            } else {
                                printf("Log not found.\n");
                            }
                            break;
                        case 10:
                            printf("Enter keyword to search: ");
                            scanf("%s", keyword);
                            foundNode = searchByKeyword(bidirectionalHead, keyword);
                            if (foundNode) {
                                printf("Found: ");
                                displayLogEntry(foundNode->log);
                            } else {
                                printf("Log not found.\n");
                            }
                            break;
                        case 11:
                            printf("Enter timestamp to search: ");
                            scanf("%s", timestampStr);
                            foundNode = searchByTimestamp(bidirectionalHead, timestampStr);
                            if (foundNode) {
                                printf("Found: ");
                                displayLogEntry(foundNode->log);
                            } else {
                                printf("Log not found.\n");
                            }
                            break;
                        case 12:
                            bidirectionalHead = sortByDate(bidirectionalHead);
                            printf("List sorted by date.\n");
                            break;
                        case 13:
                            bidirectionalHead = sortBySeverity(bidirectionalHead);
                            printf("List sorted by severity.\n");
                            break;
                        case 14:
                            bidirectionalHead = reverseList(bidirectionalHead);
                            printf("List reversed.\n");
                            break;
                        case 15:
                            printf("Total logs: %d\n", countLogs(bidirectionalHead));
                            break;
                        case 16:
                            printf("\nAll Logs (forward):\n");
                            displayForward(bidirectionalHead);
                            break;
                        case 17:
                            printf("\nAll Logs (backward):\n");
                            if (bidirectionalHead) {
                                Node* tail = bidirectionalHead;
                                while (tail->next) tail = tail->next;
                                displayBackward(tail);
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 6: // Recursion Examples
                do {
                    printf("\nRecursion Examples:\n");
                    printf("1. Calculate factorial\n");
                    printf("2. Calculate Fibonacci number\n");
                    printf("3. Find maximum ID in linked list\n");
                    printf("4. Binary search in sorted array\n");
                    printf("5. Reverse linked list (recursive)\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            printf("Enter number for factorial: ");
                            scanf("%d", &id);
                            printf("Factorial of %d is %d\n", id, factorial(id));
                            break;
                        case 2:
                            printf("Enter Fibonacci sequence position: ");
                            scanf("%d", &id);
                            printf("Fibonacci number at position %d is %d\n", id, fibonacci(id));
                            break;
                        case 3:
                            printf("Maximum ID in linked list: %d\n", 
                                   findMaxID((Node*)linkedListHead, 0));
                            break;
                        case 4:
                            // For binary search, we need a sorted array
                            // Let's create a temporary sorted array from the linked list
                            {
                                int count = totalLogs(linkedListHead);
                                if (count == 0) {
                                    printf("No logs to search.\n");
                                    break;
                                }
                                
                                LogEntry* arr = (LogEntry*)malloc(count * sizeof(LogEntry));
                                LogEntry* temp = linkedListHead;
                                for (int i = 0; i < count && temp != NULL; i++) {
                                    arr[i] = *temp;
                                    temp = temp->next;
                                }
                                
                                // Sort the array by ID (simple bubble sort)
                                for (int i = 0; i < count-1; i++) {
                                    for (int j = 0; j < count-i-1; j++) {
                                        if (arr[j].id > arr[j+1].id) {
                                            LogEntry tmp = arr[j];
                                            arr[j] = arr[j+1];
                                            arr[j+1] = tmp;
                                        }
                                    }
                                }
                                
                                printf("Enter ID to search: ");
                                scanf("%d", &id);
                                int result = binarySearch(arr, 0, count-1, id);
                                if (result != -1) {
                                    printf("Found at position %d:\n", result);
                                    displayLogEntry(arr[result]);
                                } else {
                                    printf("ID not found.\n");
                                }
                                
                                free(arr);
                            }
                            break;
                        case 5:
                            linkedListHead = (LogEntry*)reverseLinkedList((Node*)linkedListHead);
                            printf("Linked list reversed recursively.\n");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 0:
                printf("Exiting program.\n");
                break;
                
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
    
    // Clean up memory
    freeLinkedList(linkedListHead);
    freeCircularList(circularListHead);
    freeTree(treeRoot);
    freeBidirectionalList(bidirectionalHead);
    
    return 0;
}