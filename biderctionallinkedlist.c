#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BIDERCTIONAL_H"
typedef struct {
    int id;
    char keyword[100];
    char timestamp[20];
    int severity;
} LogEntry;

typedef struct Node {
    LogEntry log;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(LogEntry log) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->log = log;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

Node* insertAtBeginning(Node* head, LogEntry log) {
    Node* newNode = createNode(log);
    newNode->next = head;
    if (head) head->prev = newNode;
    return newNode;
}

Node* insertAtEnd(Node* head, LogEntry log) {
    Node* newNode = createNode(log);
    if (!head) return newNode;
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

Node* insertAtPosition(Node* head, LogEntry log, int position) {
    if (position <= 1) return insertAtBeginning(head, log);
    Node* newNode = createNode(log);
    Node* temp = head;
    int i = 1;
    while (temp && i < position - 1) {
        temp = temp->next;
        i++;
    }
    if (!temp || !temp->next) {
        return insertAtEnd(head, log);
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
    return head;
}

Node* deleteNode(Node* head, int id) {
    Node* temp = head;
    while (temp && temp->log.id != id) temp = temp->next;
    if (!temp) return head;
    if (temp->prev) temp->prev->next = temp->next;
    else head = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    free(temp);
    return head;
}

Node* searchByID(Node* head, int id) {
    while (head) {
        if (head->log.id == id) return head;
        head = head->next;
    }
    return NULL;
}

Node* searchByKeyword(Node* head, char* keyword) {
    while (head) {
        if (strcmp(head->log.keyword, keyword) == 0) return head;
        head = head->next;
    }
    return NULL;
}

Node* searchByTimestamp(Node* head, char* timestamp) {
    while (head) {
        if (strcmp(head->log.timestamp, timestamp) == 0) return head;
        head = head->next;
    }
    return NULL;
}

void sortLogs(Node** headRef) {
    if (!*headRef || !(*headRef)->next) return;
    Node* i, *j;
    for (i = *headRef; i->next; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (i->log.severity > j->log.severity) {
                LogEntry temp = i->log;
                i->log = j->log;
                j->log = temp;
            }
        }
    }
}

Node* reverseList(Node* head) {
    Node* temp = NULL;
    Node* current = head;
    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    return temp ? temp->prev : NULL;
}

Node* mergeLists(Node* head1, Node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;
    Node* temp = head1;
    while (temp->next) temp = temp->next;
    temp->next = head2;
    head2->prev = temp;
    return head1;
}

void displayLogs(Node* head) {
    while (head) {
        printf("ID: %d, Keyword: %s, Timestamp: %s, Severity: %d\n",
               head->log.id, head->log.keyword, head->log.timestamp, head->log.severity);
        head = head->next;
    }
}

LogEntry inputLog() {
    LogEntry log;
    printf("Enter ID: ");
    scanf("%d", &log.id);
    printf("Enter keyword: ");
    scanf(" %99s", log.keyword);
    printf("Enter timestamp (e.g., 2024-05-19_17:00:00): ");
    scanf(" %19s", log.timestamp);
    printf("Enter severity (1-5): ");
    scanf("%d", &log.severity);
    return log;
}

int main() {
    Node* head = NULL;
    int choice, id, position;
    LogEntry log;
    char keyword[100];
    char timestamp[20];

    do {
        printf("\nMenu:\n");
        printf("1. Insert at beginning\n2. Insert at end\n3. Insert at position\n");
        printf("4. Delete node\n5. Search by ID\n6. Search by keyword\n");
        printf("7. Search by timestamp\n8. Sort by severity\n9. Reverse list\n");
        printf("10. Merge with another list\n11. Display logs\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                log = inputLog();
                head = insertAtBeginning(head, log);
                break;
            case 2:
                log = inputLog();
                head = insertAtEnd(head, log);
                break;
            case 3:
                printf("Enter position: ");
                scanf("%d", &position);
                log = inputLog();
                head = insertAtPosition(head, log, position);
                break;
            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                head = deleteNode(head, id);
                break;
            case 5: {
                printf("Enter ID to search: ");
                scanf("%d", &id);
                Node* foundByID = searchByID(head, id);
                if (foundByID)
                    printf("Found: ID: %d, Keyword: %s, Timestamp: %s, Severity: %d\n",
                           foundByID->log.id, foundByID->log.keyword, foundByID->log.timestamp, foundByID->log.severity);
                else
                    printf("Log with ID %d not found.\n", id);
                break;
            }
            case 6: {
                printf("Enter keyword to search: ");
                scanf(" %99s", keyword);
                Node* foundByKeyword = searchByKeyword(head, keyword);
                if (foundByKeyword)
                    printf("Found: ID: %d, Keyword: %s, Timestamp: %s, Severity: %d\n",
                           foundByKeyword->log.id, foundByKeyword->log.keyword, foundByKeyword->log.timestamp, foundByKeyword->log.severity);
                else
                    printf("Log with keyword %s not found.\n", keyword);
                break;
            }
            case 7: {
                printf("Enter timestamp to search: ");
                scanf(" %19s", timestamp);
                Node* foundByTimestamp = searchByTimestamp(head, timestamp);
                if (foundByTimestamp)
                    printf("Found: ID: %d, Keyword: %s, Timestamp: %s, Severity: %d\n",
                           foundByTimestamp->log.id, foundByTimestamp->log.keyword, foundByTimestamp->log.timestamp, foundByTimestamp->log.severity);
                else
                    printf("Log with timestamp %s not found.\n", timestamp);
                break;
            }
            case 8:
                sortLogs(&head);
                printf("Logs sorted by severity.\n");
                break;
            case 9:
                head = reverseList(head);
                printf("List reversed.\n");
                break;
            case 10: {
                printf("Enter number of logs for the second list: ");
                int n;
                scanf("%d", &n);
                Node* secondList = NULL;
                for (int i = 0; i < n; ++i) {
                    printf("Enter log %d:\n", i + 1);
                    log = inputLog();
                    secondList = insertAtEnd(secondList, log);
                }
                head = mergeLists(head, secondList);
                printf("Lists merged.\n");
                break;
            }
            case 11:
                displayLogs(head);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    // Free memory
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

