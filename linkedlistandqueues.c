
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlistandqueues.h"

// Helper: count characters and vowels
void analyzeWord(const char *word, int *char_count, int *vowel_count) {
    *char_count = strlen(word);
    *vowel_count = 0;
    for (int i = 0; word[i]; i++) {
        char c = tolower(word[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            (*vowel_count)++;
    }
}

// Add new node to list
TList *addToList(TList *head, const char *word, const char *syn) {
    TList *node = (TList *)malloc(sizeof(TList));
    strcpy(node->word, word);
    strcpy(node->synonym, syn);
    node->antonym[0] = '\0';
    analyzeWord(word, &node->char_count, &node->vowel_count);
    node->next = head;
    node->prev = NULL;
    if (head) head->prev = node;
    return node;
}

TList *getSynWords(FILE *f) {
    char line[200];
    TList *head = NULL;
    while (fgets(line, sizeof(line), f)) {
        char *word = strtok(line, "=");
        char *syn = strtok(NULL, "#\n");
        if (word && syn)
            head = addToList(head, word, syn);
    }
    return head;
}

void getInfWord(TList *syn, TList *ant, char *word) {
    while (syn) {
        if (strcmp(syn->word, word) == 0) {
            printf("Synonym: %s, Chars: %d, Vowels: %d\n", syn->synonym, syn->char_count, syn->vowel_count);
            break;
        }
        syn = syn->next;
    }
    while (ant) {
        if (strcmp(ant->word, word) == 0) {
            printf("Antonym: %s, Chars: %d, Vowels: %d\n", ant->antonym, ant->char_count, ant->vowel_count);
            break;
        }
        ant = ant->next;
    }
}

TList *sortWord(TList *syn) {
    for (TList *i = syn; i; i = i->next) {
        for (TList *j = i->next; j; j = j->next) {
            if (strcmp(i->word, j->word) > 0) {
                char tmp[50];
                strcpy(tmp, i->word); strcpy(i->word, j->word); strcpy(j->word, tmp);
                strcpy(tmp, i->synonym); strcpy(i->synonym, j->synonym); strcpy(j->synonym, tmp);
            }
        }
    }
    return syn;
}

TList *sortWord3(TList *syn) {
    for (TList *i = syn; i; i = i->next) {
        for (TList *j = i->next; j; j = j->next) {
            if (i->vowel_count < j->vowel_count) {
                char tmp[50];
                strcpy(tmp, i->word); strcpy(i->word, j->word); strcpy(j->word, tmp);
                strcpy(tmp, i->synonym); strcpy(i->synonym, j->synonym); strcpy(j->synonym, tmp);
                int t = i->vowel_count; i->vowel_count = j->vowel_count; j->vowel_count = t;
            }
        }
    }
    return syn;
}

TList *updateWord(FILE *f, TList *syn, TList *ant, char *word, char *syne, char *anton) {
    for (TList *node = syn; node; node = node->next)
        if (strcmp(node->word, word) == 0)
            strcpy(node->synonym, syne);

    for (TList *node = ant; node; node = node->next)
        if (strcmp(node->word, word) == 0)
            strcpy(node->antonym, anton);

    // Skipping file update logic for now (would require re-writing file)
    return syn;
}

TList *countWord(TList *syn, char *prt) {
    TList *result = NULL;
    for (TList *node = syn; node; node = node->next) {
        if (strstr(node->word, prt))
            result = addToList(result, node->word, node->synonym);
    }
    return result;
}

TList *merge(TList *syn, TList *ant) {
    TList *merged = NULL;
    while (syn && ant) {
        if (strcmp(syn->word, ant->word) == 0) {
            TList *node = (TList *)malloc(sizeof(TList));
            strcpy(node->word, syn->word);
            strcpy(node->synonym, syn->synonym);
            strcpy(node->antonym, ant->antonym);
            node->char_count = syn->char_count;
            node->vowel_count = syn->vowel_count;
            node->next = merged;
            node->prev = NULL;
            if (merged) merged->prev = node;
            merged = node;
        }
        syn = syn->next;
        ant = ant->next;
    }
    return merged;
}

TList *addWord(TList *syn, TList *ant, char *word, char *syne, char *anton) {
    syn = addToList(syn, word, syne);
    ant = addToList(ant, word, anton);
    return syn;
}

TQueue *prounounciation(TList *syn) {
    TQueue *q = (TQueue *)malloc(sizeof(TQueue));
    q->front = q->rear = NULL;

    for (TList *node = syn; node; node = node->next) {
        TQueueNode *qn = (TQueueNode *)malloc(sizeof(TQueueNode));
        strcpy(qn->word, node->word);
        qn->next = NULL;
        if (node->vowel_count <= 2) strcpy(qn->type, "short");
        else if (node->vowel_count == 3) strcpy(qn->type, "long");
        else strcpy(qn->type, "diphthong");

        if (!q->front)
            q->front = q->rear = qn;
        else {
            q->rear->next = qn;
            q->rear = qn;
        }
    }
    return q;
}
