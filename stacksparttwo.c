#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "STACK_H"
// Node structure for the stack
typedef struct TStack {
    char *word;
    char *synonym;
    char *antonym;
    int numChars;
    int numVowels;
    struct TStack *next;
} TStack;

// Queue node structure
typedef struct TQueueNode {
    char *word;
    struct TQueueNode *next;
} TQueueNode;

// Queue structure
typedef struct {
    TQueueNode *front;
    TQueueNode *rear;
} TQueue;

// Function prototypes
TStack *addWordStack(TStack *stk, char *word, char *syn, char *anton);
TStack *deleteWordStack(TStack *stk, char *word);
void printStack(TStack *stk);
TQueue *stackToSortedQueue(TStack *Stk);
void printQueue(TQueue *q);
TStack* StackRev(TStack *stk);
void cycleSearch(TStack *Stk);
void freeStack(TStack *stk);
void freeQueue(TQueue *q);

// Add new word node to top of stack
TStack *addWordStack(TStack *stk, char *word, char *syn, char *anton) {
    TStack *newNode = (TStack*)malloc(sizeof(TStack));
    newNode->word = strdup(word);
    newNode->synonym = strdup(syn);
    newNode->antonym = strdup(anton);
    newNode->next = stk;
    return newNode;
}

// Delete a node containing the given word
TStack *deleteWordStack(TStack *stk, char *word) {
    TStack *temp = stk;
    TStack *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                stk = temp->next;
            }
            free(temp->word);
            free(temp->synonym);
            free(temp->antonym);
            free(temp);
            return stk;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Word '%s' not found in stack.\n", word);
    return stk;
}

// Print the stack content
void printStack(TStack *stk) {
    if (stk == NULL) {
        printf("Stack is empty.\n\n");
        return;
    }
    printf("Stack content:\n");
    while (stk != NULL) {
        printf("Word: %s, Synonym: %s, Antonym: %s\n", stk->word, stk->synonym, stk->antonym);
        stk = stk->next;
    }
    printf("\n");
}

// Convert stack to queue without sorting
TQueue *stackToQueueun(TStack *Stk) {
    TQueue *q = malloc(sizeof(TQueue));
    q->front = q->rear = NULL;
    
    TStack *temp = Stk;
    while(temp != NULL) {
        TQueueNode *newNode = malloc(sizeof(TQueueNode));
        newNode->word = strdup(temp->word);
        newNode->next = NULL;

        if (q->rear == NULL) {
            q->front = q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
        temp = temp->next;
    }
    return q;
}

// Sort queue lexicographically by word
void sortQueue(TQueue *q) {
    if (q->front == NULL || q->front->next == NULL) {
        return;
    }

    TQueueNode *i, *j;
    char *tempWord;

    for (i = q->front; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->word, j->word) > 0) {
                tempWord = i->word;
                i->word = j->word;
                j->word = tempWord;
            }
        }
    }
}

// Convert stack to sorted queue
TQueue *stackToSortedQueue(TStack *Stk) {
    TQueue *tempQueue = stackToQueueun(Stk);
    sortQueue(tempQueue);
    return tempQueue;
}

// Print queue contents
void printQueue(TQueue *q) {
    if (q == NULL || q->front == NULL) {
        printf("Queue is empty.\n\n");
        return;
    }
    printf("Queue content:\n");
    TQueueNode *temp = q->front;
    while (temp != NULL) {
        printf("Word: %s\n", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

// Reverse the linked stack recursively and return new top
TStack* StackRev(TStack *stk) {
    if (stk == NULL || stk->next == NULL) {
        return stk;
    }
    TStack *rest = StackRev(stk->next);
    stk->next->next = stk;
    stk->next = NULL;
    return rest;
}

// Print stack nodes from start to end (inclusive)
void printBetweenNodes(TStack *start, TStack *end) {
    TStack *temp = start;
    while (temp != NULL && temp != end) {
        printf("Word: %s\n", temp->word);
        temp = temp->next;
    }
    if (temp == end && temp != NULL) {
        printf("Word: %s\n", temp->word);
    }
}

// Search for synonym or antonym cycles and print them
void cycleSearch(TStack *Stk) {
    if (Stk == NULL) {
        printf("Stack is empty. No cycles.\n\n");
        return;
    }

    TStack *temp = Stk;
    bool foundCycle = false;
    while(temp != NULL){
        TStack *current = temp;
        char currentword[100];
        strcpy(currentword, temp->word);

        while (current != NULL) {
            if ((current->synonym && strcmp(current->synonym, currentword) == 0) || 
                (current->antonym && strcmp(current->antonym, currentword) == 0)) {
                printf("Cycle found:\n");
                printBetweenNodes(temp, current);
                printf("\n");
                foundCycle = true;
                break;
            }
            current = current->next;
        }
        temp = temp->next;
    }
    if (!foundCycle) {
        printf("No synonym/antonym cycles found.\n\n");
    }
}

// Free all memory in stack
void freeStack(TStack *stk) {
    while (stk != NULL) {
        TStack *temp = stk;
        stk = stk->next;
        free(temp->word);
        free(temp->synonym);
        free(temp->antonym);
        free(temp);
    }
}

// Free all memory in queue
void freeQueue(TQueue *q) {
    if (!q) return;
    TQueueNode *temp = q->front;
    while (temp != NULL) {
        TQueueNode *toFree = temp;
        temp = temp->next;
        free(toFree->word);
        free(toFree);
    }
    free(q);
}

int main() {
    TStack *stack = NULL;
    int choice;
    char word[100], syn[100], anton[100];

    do {
        printf("Menu:\n");
        printf("1. Add a word\n");
        printf("2. Delete a word\n");
        printf("3. Print stack\n");
        printf("4. Convert stack to sorted queue and print\n");
        printf("5. Reverse stack\n");
        printf("6. Search for synonym/antonym cycles\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline after number input

        switch(choice) {
            case 1:
                printf("Enter word: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0;  // Remove newline

                printf("Enter synonym: ");
                fgets(syn, sizeof(syn), stdin);
                syn[strcspn(syn, "\n")] = 0;

                printf("Enter antonym: ");
                fgets(anton, sizeof(anton), stdin);
                anton[strcspn(anton, "\n")] = 0;

                stack = addWordStack(stack, word, syn, anton);
                printf("Word added.\n\n");
                break;

            case 2:
                printf("Enter word to delete: ");
                fgets(word, sizeof(word), stdin);
                word[strcspn(word, "\n")] = 0;

                stack = deleteWordStack(stack, word);
                printf("\n");
                break;

            case 3:
                printStack(stack);
                break;

            case 4: {
                TQueue *q = stackToSortedQueue(stack);
                printQueue(q);
                freeQueue(q);
                break;
            }

            case 5:
                stack = StackRev(stack);
                printf("Stack reversed.\n\n");
                break;

            case 6:
                cycleSearch(stack);
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n\n");
        }

    } while(choice != 7);

    freeStack(stack);
    return 0;
}

