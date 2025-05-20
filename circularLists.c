#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CIRCULARLISTS_H"


//Module 3: Circular Linked Lists (circularLists.c/circularLists.h)
//Insert Log Entry
//Insert at beginning

// LogEntry structure definition
typedef struct LogEntry {
    int id;
    char* timestamp;
    char* message;
    int severity;
    struct LogEntry* next;
} LogEntry;

void insertAtBeginning(LogEntry** head, LogEntry newLog) {
	LogEntry *newnode;
	newnode=(LogEntry*)malloc(sizeof(LogEntry));
	*newnode=newLog;
	
	if(*head == NULL) {
	    // If list is empty
	    *head = newnode;
	    newnode->next = *head; // Point to itself (circular)
	} else {
	    // Find the last node
	    LogEntry *temp = *head;
	    while(temp->next != *head) {
	        temp = temp->next;
	    }
	    
	    newnode->next = *head;
	    *head = newnode;
	    temp->next = *head; // Update the last node to point to new head
	}
} 

//Insert at End
void insertAtEnd(LogEntry** head, LogEntry newLog){
	LogEntry *newnode, *temp;
	newnode=(LogEntry*)malloc(sizeof(LogEntry));
	*newnode = newLog;
	
	if (*head == NULL) {
	 	// If the list is empty
        *head = newnode;
        newnode->next = *head; // Point to itself (circular)
        return;
    }
    
    temp = *head;
	while(temp->next != *head){
		temp = temp->next;
	}
	temp->next = newnode;
	newnode->next = *head; // Point back to head (circular)
}

//Insert after a given position

// function to count the length of the circular linked list
int length(LogEntry** head){
	LogEntry* temp;
	int count = 0;
	
	if(*head == NULL) return 0;
	
	temp = *head;
	do {
		count++;
		temp = temp->next;
	} while(temp != *head);
	  
	return count;	
}

void insertAfterPosition(LogEntry** head, LogEntry newLog, int pos) {
	int i = 0;
    LogEntry *newnode, *temp;
	int count = length(head);
	
	if(pos > count){
		printf("Invalid position!\n");
	} else {
		temp = *head;
		while(i < pos){
			temp = temp->next;
			i++;
		}
		
		newnode = (LogEntry*)malloc(sizeof(LogEntry));
		*newnode = newLog;
		newnode->next = temp->next;
		temp->next = newnode;
	}
}

//Delete Log Entry

//Delete by ID address

void deleteById(LogEntry** head, int id) {
	LogEntry *temp;
	LogEntry *prev;
	
	if(*head == NULL) return;
	
	// If only one node and it has the ID to delete
	if((*head)->next == *head && (*head)->id == id) {
        free(*head);
        *head = NULL;
        return;
    }
	
	temp = *head;
	prev = NULL;
	
	// Check if head node has the ID
	if(temp->id == id) {
	    // Find the last node
	    prev = *head;
	    while(prev->next != *head) {
	        prev = prev->next;
	    }
	    
	    *head = temp->next; // Update head
	    prev->next = *head; // Update last node to point to new head
	    free(temp);
	    return;
	}
	
	// Check remaining nodes
	prev = *head;
	temp = (*head)->next;
	
	while(temp != *head) {
	    if(temp->id == id) {
	        prev->next = temp->next;
	        free(temp);
	        return;
	    }
	    prev = temp;
	    temp = temp->next;
	}
	
	printf("Log with ID %d not found, try again!\n", id);
}

//Delete By Timestamp

void deleteByTimestamp(LogEntry** head, char* timestamp){
	LogEntry *temp;
	LogEntry *prev;
	
	if(*head == NULL) return;
	
	// If only one node and it has the timestamp to delete
	if((*head)->next == *head && strcmp((*head)->timestamp, timestamp) == 0) {
        free(*head);
        *head = NULL;
        return;
    }
	
	temp = *head;
	prev = NULL;
	
	// Check if head node has the timestamp
	if(strcmp(temp->timestamp, timestamp) == 0) {
	    // Find the last node
	    prev = *head;
	    while(prev->next != *head) {
	        prev = prev->next;
	    }
	    
	    *head = temp->next; // Update head
	    prev->next = *head; // Update last node to point to new head
	    free(temp);
	    return;
	}
	
	// Check remaining nodes
	prev = *head;
	temp = (*head)->next;
	
	while(temp != *head) {
	    if(strcmp(temp->timestamp, timestamp) == 0) {
	        prev->next = temp->next;
	        free(temp);
	        return;
	    }
	    prev = temp;
	    temp = temp->next;
	}
	
	printf("Log with Timestamp %s not found, try again!\n", timestamp);
}

//Delete First

void deleteFirst(LogEntry** head) {
    if (*head == NULL) return;
    
    LogEntry* temp;
    
    // If only one node exists
    if((*head)->next == *head) {
        free(*head);
        *head = NULL;
        printf("First log deleted successfully\n");
        return;
    }
    
    temp = *head;
    
    // Find the last node
    LogEntry* last = *head;
    while(last->next != *head) {
        last = last->next;
    }
    
    *head = (*head)->next;
    last->next = *head; // Update last node to point to new head
    free(temp);
    printf("First log deleted successfully\n");
}

//Delete Last

void deleteLast(LogEntry** head) {
    if (*head == NULL) return;

    LogEntry* temp;
    LogEntry* prev;
    
    // If only one node exists
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        printf("Last log deleted successfully\n");
        return;
    }
    
    temp = *head;
    
    // Find the second-to-last node
    while(temp->next->next != *head) {
        temp = temp->next;
    }
    
    prev = temp->next; // Last node
    temp->next = *head; // Point to head
    free(prev);
    printf("Last log deleted successfully\n");
}

//Search Log entry

//Search by ID
LogEntry* searchByID(LogEntry* head, int id) {
    if(head == NULL) return NULL;
    
    LogEntry* temp = head;
    
    do {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    } while(temp != head);

    return NULL;
}

// Search By keyword
LogEntry* searchByKeyword(LogEntry* head, char* keyword) {
	if(head == NULL) return NULL;
	
	LogEntry* temp = head;
	
	do {
		if (strstr(temp->message, keyword) != NULL) {
            return temp;
        }
		temp = temp->next;
	} while(temp != head);

    return NULL;
}

//Search By timestamp

LogEntry* searchByTimestamp(LogEntry* head, char* timestamp) {
    if(head == NULL) return NULL;
    
    LogEntry* temp = head;
    
    do {
        if (strcmp(temp->timestamp, timestamp) == 0) {
            return temp; 
        }
        temp = temp->next;
    } while(temp != head);

    return NULL;
}

//Sort Logs 
//Sort By date

void sortByDate(LogEntry** head) {
    if (*head == NULL || (*head)->next == *head)
        return;
    
    LogEntry* i;
    LogEntry* j;
    char* temp;
    
    for(i = *head; i->next != *head; i = i->next) {
    	for(j = i->next; j != *head; j = j->next) {
    		if(strcmp(i->timestamp, j->timestamp) > 0) {
    		    // Swap timestamps	
    		    temp = i->timestamp;
    		    i->timestamp = j->timestamp;
    		    j->timestamp = temp;
    		    
    		    // Swap other fields
    		    int tempId = i->id;
    		    i->id = j->id;
    		    j->id = tempId;
    		    
    		    char* tempMsg = i->message;
    		    i->message = j->message;
    		    j->message = tempMsg;
    		    
    		    int tempSev = i->severity;
    		    i->severity = j->severity;
    		    j->severity = tempSev;
            }
        }
    }
}

//Sort By Severity 
void sortBySeverity(LogEntry** head) {
    if (*head == NULL || (*head)->next == *head)
        return;

    LogEntry* i;
    LogEntry* j;
    int temp;
    
    for(i = *head; i->next != *head; i = i->next) {
        for(j = i->next; j != *head; j = j->next) {
            if(i->severity > j->severity) {
               // Swap severity
               temp = i->severity;
               i->severity = j->severity;
               j->severity = temp;
               
               // Swap other fields
               int tempId = i->id;
               i->id = j->id;
               j->id = tempId;
               
               char* tempTimestamp = i->timestamp;
               i->timestamp = j->timestamp;
               j->timestamp = tempTimestamp;
               
               char* tempMsg = i->message;
               i->message = j->message;
               j->message = tempMsg;
            }
        }
    }
}

//Reverse the List (to view logs in reverse order)
void reverseList(LogEntry** head) {
	if(*head == NULL || (*head)->next == *head) return;
	
	LogEntry* prevnode = NULL;
	LogEntry* currentnode = *head;
	LogEntry* nextnode;
	LogEntry* last = *head; // Remember the original head
	
	do {
		nextnode = currentnode->next;
		currentnode->next = prevnode;
		prevnode = currentnode;
		currentnode = nextnode;
	} while(currentnode != *head);
	
	(*head)->next = prevnode; // Complete the circular link
	*head = prevnode; // Update head
}

//Count total logs
int totalLogs(LogEntry** head) {
	return length(head);
}



void displayLogs(LogEntry* head) {
    if (head == NULL) {
        printf("No logs available.\n");
        return;
    }

    LogEntry* temp = head;
    printf("\n--- All Logs ---\n");
    do {
        printf("ID: %d | Timestamp: %s | Severity: %d | Message: %s\n",
               temp->id, temp->timestamp, temp->severity, temp->message);
        temp = temp->next;
    } while (temp != head);
    printf("----------------\n\n");
}

int main() {
    LogEntry* logList = NULL;
    LogEntry newLog;
    int choice, id, pos, severity;
    char timestamp[50], message[100], keyword[50];

    do {
        printf("\n?? Log Management System (Circular Linked List)\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert after Position\n");
        printf("4. Delete by ID\n");
        printf("5. Delete by Timestamp\n");
        printf("6. Delete First\n");
        printf("7. Delete Last\n");
        printf("8. Search by ID\n");
        printf("9. Search by Timestamp\n");
        printf("10. Search by Keyword\n");
        printf("11. Sort by Date\n");
        printf("12. Sort by Severity\n");
        printf("13. Reverse Logs\n");
        printf("14. Count Logs\n");
        printf("15. Display Logs\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
            case 2:
            case 3:
                printf("Enter Log ID: ");
                scanf("%d", &newLog.id);
                getchar();
                printf("Enter Timestamp: ");
                fgets(timestamp, sizeof(timestamp), stdin);
                timestamp[strcspn(timestamp, "\n")] = '\0';
                newLog.timestamp = strdup(timestamp);
                printf("Enter Severity: ");
                scanf("%d", &severity);
                newLog.severity = severity;
                getchar();
                printf("Enter Message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                newLog.message = strdup(message);

                if (choice == 1)
                    insertAtBeginning(&logList, newLog);
                else if (choice == 2)
                    insertAtEnd(&logList, newLog);
                else {
                    printf("Enter position to insert after: ");
                    scanf("%d", &pos);
                    insertAfterPosition(&logList, newLog, pos);
                }
                break;

            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteById(&logList, id);
                break;

            case 5:
                printf("Enter Timestamp to delete: ");
                getchar();
                fgets(timestamp, sizeof(timestamp), stdin);
                timestamp[strcspn(timestamp, "\n")] = '\0';
                deleteByTimestamp(&logList, timestamp);
                break;

            case 6:
                deleteFirst(&logList);
                break;

            case 7:
                deleteLast(&logList);
                break;

            case 8:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                LogEntry* foundById = searchByID(logList, id);
                if (foundById)
                    printf("Found: %s\n", foundById->message);
                else
                    printf("Log not found.\n");
                break;

            case 9:
                printf("Enter Timestamp to search: ");
                getchar();
                fgets(timestamp, sizeof(timestamp), stdin);
                timestamp[strcspn(timestamp, "\n")] = '\0';
                LogEntry* foundByTs = searchByTimestamp(logList, timestamp);
                if (foundByTs)
                    printf("Found: %s\n", foundByTs->message);
                else
                    printf("Log not found.\n");
                break;

            case 10:
                printf("Enter keyword to search: ");
                getchar();
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                LogEntry* foundByKey = searchByKeyword(logList, keyword);
                if (foundByKey)
                    printf("Found: %s\n", foundByKey->message);
                else
                    printf("No matching log found.\n");
                break;

            case 11:
                sortByDate(&logList);
                printf("Logs sorted by date.\n");
                break;

            case 12:
                sortBySeverity(&logList);
                printf("Logs sorted by severity.\n");
                break;

            case 13:
                reverseList(&logList);
                printf("Logs reversed.\n");
                break;

            case 14:
                printf("Total logs: %d\n", totalLogs(&logList));
                break;

            case 15:
                displayLogs(logList);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

