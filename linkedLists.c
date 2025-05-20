#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LINKEDLISTS_H"

typedef struct LogEntry {
    int id;
    char* timestamp;
    char* message;
    int severity;
    struct LogEntry* next; 
} LogEntry;

// Create a deep copy of a LogEntry
LogEntry* createNodeFromLog(LogEntry* log) {
    LogEntry* newNode = (LogEntry*)malloc(sizeof(LogEntry));
    newNode->id = log->id;
    newNode->timestamp = strdup(log->timestamp);
    newNode->message = strdup(log->message);
    newNode->severity = log->severity;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning of list
void insertAtBeginning(LogEntry** head, LogEntry newLog) {
    LogEntry* newNode = createNodeFromLog(&newLog);
    newNode->next = *head;
    *head = newNode;
}

// Insert at end of list
void insertAtEnd(LogEntry** head, LogEntry newLog) {
    LogEntry* newNode = createNodeFromLog(&newLog);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    LogEntry* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

// Get list length
int length(LogEntry* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Insert after position
void insertAfterPosition(LogEntry** head, LogEntry newLog, int pos) {
    int len = length(*head);
    if (pos > len || pos < 1) {
        printf("Invalid position!\n");
        return;
    }
    LogEntry* newNode = createNodeFromLog(&newLog);
    LogEntry* temp = *head;
    for (int i = 1; i < pos; i++)
        temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete a node and free memory
void deleteNode(LogEntry** head, LogEntry* target, LogEntry* prev) {
    if (prev)
        prev->next = target->next;
    else
        *head = target->next;
    free(target->timestamp);
    free(target->message);
    free(target);
}

// Delete by ID
void deleteById(LogEntry** head, int id) {
    LogEntry* temp = *head;
    LogEntry* prev = NULL;
    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Log with ID %d not found.\n", id);
        return;
    }
    deleteNode(head, temp, prev);
    printf("Log with ID %d deleted.\n", id);
}

// Delete by timestamp
void deleteByTimestamp(LogEntry** head, char* timestamp) {
    LogEntry* temp = *head;
    LogEntry* prev = NULL;
    while (temp && strcmp(temp->timestamp, timestamp) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Log with Timestamp %s not found.\n", timestamp);
        return;
    }
    deleteNode(head, temp, prev);
    printf("Log with Timestamp %s deleted.\n", timestamp);
}

// Delete first node
void deleteFirst(LogEntry** head) {
    if (*head == NULL) return;
    LogEntry* temp = *head;
    *head = temp->next;
    free(temp->timestamp);
    free(temp->message);
    free(temp);
    printf("First log deleted.\n");
}

// Delete last node
void deleteLast(LogEntry** head) {
    if (*head == NULL) return;
    if ((*head)->next == NULL) {
        deleteFirst(head);
        return;
    }
    LogEntry* temp = *head;
    LogEntry* prev = NULL;
    while (temp->next) {
        prev = temp;
        temp = temp->next;
    }
    deleteNode(head, temp, prev);
    printf("Last log deleted.\n");
}

// Search functions
LogEntry* searchByID(LogEntry* head, int id) {
    while (head) {
        if (head->id == id) return head;
        head = head->next;
    }
    return NULL;
}

LogEntry* searchByKeyword(LogEntry* head, char* keyword) {
    while (head) {
        if (strstr(head->message, keyword)) return head;
        head = head->next;
    }
    return NULL;
}

LogEntry* searchByTimestamp(LogEntry* head, char* timestamp) {
    while (head) {
        if (strcmp(head->timestamp, timestamp) == 0) return head;
        head = head->next;
    }
    return NULL;
}

// Sort by date
void sortByDate(LogEntry** head) {
    for (LogEntry* i = *head; i && i->next; i = i->next) {
        for (LogEntry* j = i->next; j; j = j->next) {
            if (strcmp(i->timestamp, j->timestamp) > 0) {
                // swap contents
                int tempId = i->id;
                char* tempTimestamp = i->timestamp;
                char* tempMessage = i->message;
                int tempSeverity = i->severity;

                i->id = j->id;
                i->timestamp = j->timestamp;
                i->message = j->message;
                i->severity = j->severity;

                j->id = tempId;
                j->timestamp = tempTimestamp;
                j->message = tempMessage;
                j->severity = tempSeverity;
            }
        }
    }
}

// Sort by severity
void sortBySeverity(LogEntry** head) {
    for (LogEntry* i = *head; i && i->next; i = i->next) {
        for (LogEntry* j = i->next; j; j = j->next) {
            if (i->severity > j->severity) {
                // swap contents
                int tempId = i->id;
                char* tempTimestamp = i->timestamp;
                char* tempMessage = i->message;
                int tempSeverity = i->severity;

                i->id = j->id;
                i->timestamp = j->timestamp;
                i->message = j->message;
                i->severity = j->severity;

                j->id = tempId;
                j->timestamp = tempTimestamp;
                j->message = tempMessage;
                j->severity = tempSeverity;
            }
        }
    }
}

// Reverse list
void reverseList(LogEntry** head) {
    LogEntry* prev = NULL;
    LogEntry* curr = *head;
    LogEntry* next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

// Count logs
int totalLogs(LogEntry* head) {
    return length(head);
}

// Print
void printLog(LogEntry* log) {
    if (log) {
        printf("ID: %d | Timestamp: %s | Severity: %d | Message: %s\n",
               log->id, log->timestamp, log->severity, log->message);
    } else {
        printf("Log not found.\n");
    }
}

void printList(LogEntry* head) {
    while (head) {
        printLog(head);
        head = head->next;
    }
}

// Create log from user input
LogEntry createLog() {
    LogEntry log;
    char buffer[256];

    printf("Enter ID: ");
    scanf("%d", &log.id);
    getchar();

    printf("Enter Timestamp: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    log.timestamp = strdup(buffer);

    printf("Enter Message: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    log.message = strdup(buffer);

    printf("Enter Severity (1-5): ");
    scanf("%d", &log.severity);
    getchar();

    log.next = NULL;
    return log;
}

int main() {
    LogEntry* head = NULL;
    int choice, id, pos;
    char buffer[256];

    while (1) {
        printf("\n--- LOG MANAGEMENT MENU ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert After Position\n");
        printf("4. Delete by ID\n");
        printf("5. Delete by Timestamp\n");
        printf("6. Delete First Log\n");
        printf("7. Delete Last Log\n");
        printf("8. Search by ID\n");
        printf("9. Search by Keyword\n");
        printf("10. Search by Timestamp\n");
        printf("11. Sort by Date\n");
        printf("12. Sort by Severity\n");
        printf("13. Reverse Log List\n");
        printf("14. Display All Logs\n");
        printf("15. Count Logs\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                insertAtBeginning(&head, createLog());
                break;
            case 2:
                insertAtEnd(&head, createLog());
                break;
            case 3:
                printf("Enter position to insert after: ");
                scanf("%d", &pos);
                getchar();
                insertAfterPosition(&head, createLog(), pos);
                break;
            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                getchar();
                deleteById(&head, id);
                break;
            case 5:
                printf("Enter Timestamp to delete: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                deleteByTimestamp(&head, buffer);
                break;
            case 6:
                deleteFirst(&head);
                break;
            case 7:
                deleteLast(&head);
                break;
            case 8:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                getchar();
                printLog(searchByID(head, id));
                break;
            case 9:
                printf("Enter keyword to search in messages: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                printLog(searchByKeyword(head, buffer));
                break;
            case 10:
                printf("Enter timestamp to search: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                printLog(searchByTimestamp(head, buffer));
                break;
            case 11:
                sortByDate(&head);
                printf("Sorted by date.\n");
                break;
            case 12:
                sortBySeverity(&head);
                printf("Sorted by severity.\n");
                break;
            case 13:
                reverseList(&head);
                printf("List reversed.\n");
                break;
            case 14:
                printf("\n--- All Logs ---\n");
                printList(head);
                break;
            case 15:
                printf("Total Logs: %d\n", totalLogs(head));
                break;
            case 0:
                printf("Exiting...\n");
                while (head)
                    deleteFirst(&head);
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}

