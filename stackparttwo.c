// stack.c
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //is a C standard library header that provides functions for testing and converting characters...
#include <stdbool.h>

//Modules based on Stacks

typedef struct TStack {
    char *word;
    char *synonym;
    char *antonym;
    int numChars;
    int numVowels;
    struct TStack *next;
} TStack;

typedef struct stack {
    TStack *top;
} Stack;

typedef struct TQueueNode {
    char *word;
    struct TQueueNode *next;
} TQueueNode;

typedef struct {
    TQueueNode *front;
    TQueueNode *rear;
} TQueue;

//TStack *getInfWordStack(TStack *stk, char *word)
TStack *getInfWordStack(TStack *stk, char *word) {
    TStack *temp = stk;

    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            return temp; }
        temp = temp->next;
    }

    return NULL;
}


//TStack *deleteWordStack(TStack *stk, char *word)

TStack *deleteWordStack(TStack *stk, char *word) {
    TStack *temp=stk ;
    TStack *prev = NULL ;

    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            if (prev != NULL) {
                prev->next = temp->next;
            } else {
                stk = temp->next; // If the word is at the top, update the top pointer
            }
            
            free(temp->word);    // Free memory for the word
            free(temp->synonym); // Free memory for synonym
            free(temp->antonym); // Free memory for antonym
            free(temp);          // Free the node itself
            return stk;          // Return updated stack
        }
        prev = temp;
        temp = temp->next;
    }

    return stk; //if the word does not exit
}

//TQueue *stackToQueue(TStack *Stk)

// Step 1: Convert stack to simple queue (unsorted)

TQueue *stackToQueueun(TStack *Stk) {
    TQueue *q = malloc(sizeof(TQueue));
    q->front = q->rear = NULL;
    
    TStack *temp = Stk;

    while(temp!=NULL){
        TQueueNode *newNode = malloc(sizeof(TQueueNode));
        newNode->word = strdup(temp->word);
        newNode->next = NULL;
        // Add to end of queue
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

//Function to sort the queue
void sortQueue(TQueue *q) {
    if (q->front == NULL || q->front->next == NULL) {
        return;  // Queue is empty or has only one element
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

// Complete conversion with sorting
TQueue *stackToSortedQueue(TStack *Stk) {
    TQueue *tempQueue = stackToQueue(Stk);
    sortQueue(tempQueue);
    return tempQueue;
}

//TStack *addWordStack(TStack *stk, char *word, char *syn, char *anton)

TStack *addWordStack(TStack *stk, char *word, char *syn, char *anton) {
    Create new node
    TStack *newNode = (TStack*)malloc(sizeof(TStack));
    newNode->word = strdup(word);
    newNode->synonym = strdup(syn);
    newNode->antonym = strdup(anton);
    
    // Make it point to current top
    newNode->next = stk;
    
    //Return as new top
    return newNode;
}


// Function to count the number of vowels in a word
int countVowels(char *word) {
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr("aeiouAEIOU", word[i])) {
            count++;
        }
    }
    return count;
}


// Function to classify and sort words into three stacks (short, long, diphthong)
void pronunciationStack(TStack *stk, TStack **shortStack, TStack **longStack, TStack **diphthongStack) {
    TStack *temp = stk;
    
    while (temp != NULL) {
        TStack *newNode = createNode(temp->word, temp->synonym, temp->antonym);
        
        // Classify words based on vowels or syllables
        int vowelCount = countVowels(temp->word);
        
        // Classify the word based on vowel count
        if (vowelCount <= 2) {  // Short word
            *shortStack = push(*shortStack, newNode);
        } else if (vowelCount == 3) {  // Long word
            *longStack = push(*longStack, newNode);
        } else {  // Diphthong word
            *diphthongStack = push(*diphthongStack, newNode);
        }
        
        temp = temp->next;
    }
}



TStack* findWord(TStack *stk, char *word) {
    TStack *temp = stk;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

typedef struct TStack {
    char *word;
    char *synonym;
    char *antonym;
    struct TStack *next;
} TStack;

//function to print stack elements between two specific nodes
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

//void cycleSearch(TStack *Stk)
void cycleSearch(TStack *Stk) {
    TStack *temp = Stk;

    TStack *current=NULL ;
    while(temp!=NULL){
    current=temp ;
    char currentword[100];
    strcpy(currentword, temp->word);

    while (current != NULL) {
        if (strcmp(current->synonym, currentword) == 0 || strcmp(current->antonym, currentword) == 0) {
            printf("The cycle is:\n");
            printBetweenNodes(temp, current);
            printf("\n");
            break;
        }
        current = current->next;
    }
    temp = temp->next;
}
}

//TStack* StackRev(TStack *stk)

TStack* StackRev(TStack *stk) {
    // Base case: if stack is empty or has only one element
    if (stk == NULL || stk->next == NULL) {
        return stk;
    }

    // Recursively reverse the rest of the stack
    TStack *rest = StackRev(stk->next);

    stk->next->next = stk;
    stk->next = NULL;

    return rest;
}







