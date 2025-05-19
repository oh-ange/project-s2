#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedLists.h"

// Insert at beginning of list
void insertAtBeginning(LogEntry** head, LogEntry newLog) {
    LogEntry* newNode = (LogEntry*)malloc(sizeof(LogEntry));
    *newNode = newLog;
    newNode->next = *head;
    *head = newNode;
}

// Insert at end of list
void insertAtEnd(LogEntry** head, LogEntry newLog) {
    LogEntry* newNode = (LogEntry*)malloc(sizeof(LogEntry));
    *newNode = newLog;
    newNode->next = NULL;  // It's going to be the last node
    
    if (*head == NULL) {
        // If the list is empty
        *head = newNode;
        return;
    }
    
    LogEntry* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode; // Link the last node to the new one
}

// Calculate length of the linked list
int length(LogEntry* head) {
    int count = 0;
    LogEntry* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Insert after a given position
void insertAfterPosition(LogEntry** head, LogEntry newLog, int pos) {
    int i = 1;
    int listLength = length(*head);
    
    if (pos > listLength) {
        printf("Invalid position!\n");
        return;
    } 
    
    LogEntry* newNode = (LogEntry*)malloc(sizeof(LogEntry));
    *newNode = newLog;
    
    LogEntry* temp = *head;
    while (i < pos) {
        temp = temp->next;
        i++;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete by ID
void deleteById(LogEntry** head, int id) {
    if (*head == NULL) return;
    
    LogEntry* temp = *head;
    LogEntry* prev = NULL;
    
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Log with ID %d not found, try again!\n", id);
        return;
    }
    
    if (prev == NULL) {
        *head = temp->next; // We remove the first node
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
}

// Delete by timestamp
void deleteByTimestamp(LogEntry** head, char* timestamp) {
    if (*head == NULL) return;
    
    LogEntry* temp = *head;
    LogEntry* prev = NULL;
    
    while (temp != NULL && strcmp(temp->timestamp, timestamp) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Log with Timestamp %s not found, try again!\n", timestamp);
        return;
    }
    
    if (prev == NULL) {
        *head = temp->next; // We remove the first node
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
}

// Delete first log entry
void deleteFirst(LogEntry** head) {
    if (*head == NULL) return;
    
    LogEntry* temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("First log deleted successfully\n");
}

// Delete last log entry
void deleteLast(LogEntry** head) {
    if (*head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        printf("Last log deleted successfully\n");
        return;
    }
    
    LogEntry* temp = *head;
    LogEntry* prev = NULL;
    
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }
    
    prev->next = NULL;
    free(temp);
    printf("Last log deleted successfully\n");
}

// Search by ID
LogEntry* searchByID(LogEntry* head, int id) {
    LogEntry* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

// Search by keyword
LogEntry* searchByKeyword(LogEntry* head, char* keyword) {
    LogEntry* temp = head;
    
    while (temp != NULL) {
        if (strstr(temp->message, keyword) != NULL) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

// Search by timestamp
LogEntry* searchByTimestamp(LogEntry* head, char* timestamp) {
    LogEntry* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->timestamp, timestamp) == 0) {
            return temp; 
        }
        temp = temp->next;
    }

    return NULL;
}

// Sort by date
void sortByDate(LogEntry** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;
    
    LogEntry* i;
    LogEntry* j;
    char* temp;
    
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->timestamp, j->timestamp) > 0) {
                // Swap timestamps
                temp = i->timestamp;
                i->timestamp = j->timestamp;
                j->timestamp = temp;
                
                // Swap other fields to move entire records
                int tempId = i->id;
                i->id = j->id;
                j->id = tempId;
                
                char* tempMessage = i->message;
                i->message = j->message;
                j->message = tempMessage;
                
                int tempSeverity = i->severity;
                i->severity = j->severity;
                j->severity = tempSeverity;
            }
        }
    }
}

// Sort by severity
void sortBySeverity(LogEntry** head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    LogEntry* i;
    LogEntry* j;
    
    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->severity > j->severity) {
                // Swap severity
                int tempSeverity = i->severity;
                i->severity = j->severity;
                j->severity = tempSeverity;
                
                // Swap other fields to move entire records
                int tempId = i->id;
                i->id = j->id;
                j->id = tempId;
                
                char* tempTimestamp = i->timestamp;
                i->timestamp = j->timestamp;
                j->timestamp = tempTimestamp;
                
                char* tempMessage = i->message;
                i->message = j->message;
                j->message = tempMessage;
            }
        }
    }
}

// Reverse the list
void reverseList(LogEntry** head) {
    LogEntry* prevNode = NULL;
    LogEntry* currentNode = *head;
    LogEntry* nextNode = NULL;
    
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    
    *head = prevNode;
}

// Count total logs
int totalLogs(LogEntry* head) {
    return length(head);
}
