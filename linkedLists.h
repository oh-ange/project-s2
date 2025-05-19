#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

// LogEntry structure definition
typedef struct LogEntry {
    int id;
    char* timestamp;
    char* message;
    int severity;
    struct LogEntry* next;
} LogEntry;

// Insert functions
void insertAtBeginning(LogEntry** head, LogEntry newLog);
void insertAtEnd(LogEntry** head, LogEntry newLog);
void insertAfterPosition(LogEntry** head, LogEntry newLog, int pos);

// Delete functions
void deleteById(LogEntry** head, int id);
void deleteByTimestamp(LogEntry** head, char* timestamp);
void deleteFirst(LogEntry** head);
void deleteLast(LogEntry** head);

// Search functions
LogEntry* searchByID(LogEntry* head, int id);
LogEntry* searchByKeyword(LogEntry* head, char* keyword);
LogEntry* searchByTimestamp(LogEntry* head, char* timestamp);

// Sort functions
void sortByDate(LogEntry** head);
void sortBySeverity(LogEntry** head);

// Utility functions
void reverseList(LogEntry** head);
int totalLogs(LogEntry* head);
int length(LogEntry* head); // Calculate list length

#endif // LINKED_LISTS_H
