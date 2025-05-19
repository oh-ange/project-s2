#ifndef LINKEDLISTANFQUEUES_H
#define LINKEDLISTANFQUEUES_H

#include <stdio.h>

typedef struct Node {
    char word[50];
    char synonym[50];
    char antonym[50];
    int char_count;
    int vowel_count;
    struct Node *next;
    struct Node *prev;
} TList;

typedef struct QueueNode {
    char word[50];
    char type[10];  // "short", "long", "diphthong"
    struct QueueNode *next;
} TQueueNode;

typedef struct Queue {
    TQueueNode *front, *rear;
} TQueue;

// Function Prototypes
TList *getSynWords(FILE *f);
void getInfWord(TList *syn, TList *ant, char *word);
TList *sortWord(TList *syn);
TList *sortWord3(TList *syn);
TList *updateWord(FILE *f, TList *syn, TList *ant, char *word, char *syne, char *anton);
TList *countWord(TList *syn, char *prt);
TList *merge(TList *syn, TList *ant);
TList *addWord(TList *syn, TList *ant, char *word, char *syne, char *anton);
TQueue *prounounciation(TList *syn);

#endif
