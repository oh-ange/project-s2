#ifndef BIDIRECTIONAL_LINKED_LISTS_H
#define BIDIRECTIONAL_LINKED_LISTS_H

typedef struct LogEntry {
    int id;
    char keyword[100];
    char timestamp[20]; // Format: "YYYY-MM-DD HH:MM:SS"
    int severity; // e.g., 1 = Low, 5 = High
} LogEntry;

typedef struct Node {
    LogEntry log;
    struct Node* next;
    struct Node* prev;
} Node;

Node* insertAtBeginning(Node* head, LogEntry log);
Node* insertAtEnd(Node* head, LogEntry log);
Node* insertAtPosition(Node* head, LogEntry log, int position);
Node* deleteByID(Node* head, int id);
Node* deleteByTimestamp(Node* head, const char* timestamp);
Node* deleteFirst(Node* head);
Node* deleteLast(Node* head);
Node* deleteMiddle(Node* head, int index);
Node* searchByID(Node* head, int id);
Node* searchByKeyword(Node* head, const char* keyword);
Node* searchByTimestamp(Node* head, const char* timestamp);
Node* sortByDate(Node* head);
Node* sortBySeverity(Node* head);
Node* reverseList(Node* head);
int countLogs(Node* head);
void displayForward(Node* head);
void displayBackward(Node* tail);
Node* mergeLogLists(Node* head1, Node* head2);

#endif

