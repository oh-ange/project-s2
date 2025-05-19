// stack.h
#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Structures
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

// Function declarations
TStack *getInfWordStack(TStack *stk, char *word);
TStack *deleteWordStack(TStack *stk, char *word);
TQueue *stackToQueueun(TStack *Stk);
void sortQueue(TQueue *q);
TQueue *stackToSortedQueue(TStack *Stk);
TStack *addWordStack(TStack *stk, char *word, char *syn, char *anton);
int countVowels(char *word);
void pronunciationStack(TStack *stk, TStack **shortStack, TStack **longStack, TStack **diphthongStack);
TStack* findWord(TStack *stk, char *word);
void printBetweenNodes(TStack *start, TStack *end);
void cycleSearch(TStack *Stk);
TStack* StackRev(TStack *stk);

#endif // STACK_H
