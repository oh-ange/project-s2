#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bidirectionalLinkedLists.h"

// Create a new node with given log data
Node* createNode(LogEntry log) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->log = log;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Insert log at the beginning of the list
Node* insertAtBeginning(Node* head, LogEntry log) {
    Node* newNode = createNode(log);
    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }
    return newNode; // New node becomes the new head
}

// Insert log at the end of the list
Node* insertAtEnd(Node* head, LogEntry log) {
    Node* newNode = createNode(log);
    if (!head) return newNode; // If list is empty, return new node as head
    Node* temp = head;
    while (temp->next) temp = temp->next; // Traverse to the last node
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Insert log at a specific position (0-based index)
Node* insertAtPosition(Node* head, LogEntry log, int position) {
    if (position == 0 || !head) return insertAtBeginning(head, log);
    Node* newNode = createNode(log);
    Node* temp = head;
    for (int i = 0; temp && i < position - 1; i++) temp = temp->next;
    if (!temp || !temp->next) return insertAtEnd(head, log); // Insert at end if position is out of range
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
    return head;
}

// Delete log by ID
Node* deleteByID(Node* head, int id) {
    Node* temp = head;
    while (temp) {
        if (temp->log.id == id) {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next; // Update head if deleting first node
            free(temp);
            break;
        }
        temp = temp->next;
    }
    return head;
}

// Delete log by timestamp string
Node* deleteByTimestamp(Node* head, const char* timestamp) {
    Node* temp = head;
    while (temp) {
        if (strcmp(temp->log.timestamp, timestamp) == 0) {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            free(temp);
            break;
        }
        temp = temp->next;
    }
    return head;
}

// Delete the first log node
Node* deleteFirst(Node* head) {
    if (!head) return NULL;
    Node* temp = head->next;
    if (temp) temp->prev = NULL;
    free(head);
    return temp;
}

// Delete the last log node
Node* deleteLast(Node* head) {
    if (!head || !head->next) return deleteFirst(head);
    Node* temp = head;
    while (temp->next) temp = temp->next; // Traverse to the last node
    temp->prev->next = NULL;
    free(temp);
    return head;
}

// Delete log at specific index (middle of the list)
Node* deleteMiddle(Node* head, int index) {
    if (index == 0) return deleteFirst(head);
    Node* temp = head;
    for (int i = 0; temp && i < index; i++) temp = temp->next;
    if (!temp) return head; // Index out of bounds
    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    free(temp);
    return head;
}

// Search for log by ID and return pointer to node
Node* searchByID(Node* head, int id) {
    Node* temp = head;
    while (temp) {
        if (temp->log.id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Search for log by keyword (substring match)
Node* searchByKeyword(Node* head, const char* keyword) {
    Node* temp = head;
    while (temp) {
        if (strstr(temp->log.keyword, keyword)) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Search for log by timestamp (exact match)
Node* searchByTimestamp(Node* head, const char* timestamp) {
    Node* temp = head;
    while (temp) {
        if (strcmp(temp->log.timestamp, timestamp) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Sort logs in ascending order by timestamp (bubble sort)
Node* sortByDate(Node* head) {
    if (!head) return NULL;
    for (Node* i = head; i->next; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (strcmp(i->log.timestamp, j->log.timestamp) > 0) {
                LogEntry tmp = i->log; i->log = j->log; j->log = tmp;
            }
        }
    }
    return head;
}

// Sort logs in ascending order by severity level
Node* sortBySeverity(Node* head) {
    if (!head) return NULL;
    for (Node* i = head; i->next; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (i->log.severity > j->log.severity) {
                LogEntry tmp = i->log; i->log = j->log; j->log = tmp;
            }
        }
    }
    return head;
}

// Reverse the entire linked list
Node* reverseList(Node* head) {
    Node *temp = NULL, *current = head;
    while (current) {
        temp = current->prev;            // Store previous pointer
        current->prev = current->next;   // Swap prev and next
        current->next = temp;
        current = current->prev;         // Move to next node (which is previous due to swap)
    }
    return temp ? temp->prev : head;    // Return new head
}

// Count total number of log entries in the list
int countLogs(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Print logs from head to tail
void displayForward(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("ID: %d | Keyword: %s | Timestamp: %s | Severity: %d\n",
               temp->log.id, temp->log.keyword, temp->log.timestamp, temp->log.severity);
        temp = temp->next;
    }
}

// Print logs from tail to head
void displayBackward(Node* tail) {
    Node* temp = tail;
    while (temp) {
        printf("ID: %d | Keyword: %s | Timestamp: %s | Severity: %d\n",
               temp->log.id, temp->log.keyword, temp->log.timestamp, temp->log.severity);
        temp = temp->prev;
    }
}

// Merge two doubly linked log lists by appending second to first
Node* mergeLogLists(Node* head1, Node* head2) {
    if (!head1) return head2; // If first list is empty, return second
    if (!head2) return head1; // If second list is empty, return first
    Node* temp = head1;
    while (temp->next) temp = temp->next; // Go to last node of first list
    temp->next = head2;
    head2->prev = temp;
    return head1;
}

