#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //is a C standard library header that provides functions for testing and converting characters...
#include <stdbool.h>

typedef struct TList {
    char word[100];      // The word itself
    char synonym[100];   // The synonym of the word
    char antonym[100];   // The antonym of the word
    int numChars;        // The number of characters in the word
    int numVowels;       // The number of vowels in the word
    struct TList *next;  // Pointer to the next node
} TList;

typedef struct {
    char *filename;
} File;

typedef struct TQueueNode {
    char *word;
    struct TQueueNode *next;
} TQueueNode;

// The Queue Structure
typedef struct {
    TQueueNode *front;
    TQueueNode *rear;
} TQueue;

// Function prototypes
int countVowels(char *word);
TList *getAntoWords(FILE *f);
void getInfWord2(TList *syn, TList *ant, char *inf);
TList *sortWord2(TList *syn);
TList *deleteWord(File *f, TList *syn, TList *ant, char *word);
TList *similarWord(TList *syn, char *word, int rate);
bool isPalindrome(char *word);
TList *insertNode(TList *head, TList *newNode);
TList *sort(TList *syn);
TList *palindromWord(TList *syn);
TList *merge2(TList *syn, TList *ant);
int countSyllables(char *word);
TQueue *createQueue();
void enqueue(TQueue *q, char *word);
TQueue *syllable(TList *syn);
TQueue *toQueue(TList *merged);

#endif // DICTIONARY_H
