
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlistandqueues.h"

// Helper: count characters and vowels
void analyzeWord(const char *word, int *char_count, int *vowel_count) {
    *char_count = strlen(word);
    *vowel_count = 0;
    int i ;
    for (i = 0; word[i]; i++) {
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
	TList *i;
	TList *j;
    for (i = syn; i; i = i->next) {
        for (j = i->next; j; j = j->next) {
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
	TList *i;
	TList *j;
    for (i = syn; i; i = i->next) {
        for (j = i->next; j; j = j->next) {
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
	TList *node;
    for (node = syn; node; node = node->next)
        if (strcmp(node->word, word) == 0)
            strcpy(node->synonym, syne);

    for (node = ant; node; node = node->next)
        if (strcmp(node->word, word) == 0)
            strcpy(node->antonym, anton);

    // Skipping file update logic for now (would require re-writing file)
    return syn;
}

TList *countWord(TList *syn, char *prt) {
    TList *result = NULL;
    TList *node;
    for (node = syn; node; node = node->next) {
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
    TList *node;
    for (node = syn; node; node = node->next) {
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

int main() {
    TList *synonyms = NULL, *antonyms = NULL, *merged = NULL;
    TQueue *pronunciationQueue = NULL;
    TQueueNode *n;
    TList *nn;
    char word[50], synonym[50], antonym[50], part[50];
    FILE *synFile = fopen("synonyms.txt", "r");
    FILE *antFile = fopen("antonyms.txt", "r");

    if (synFile) synonyms = getSynWords(synFile);
    if (antFile) antonyms = getSynWords(antFile);  // assumes antonyms file has same format

    int choice;
    do {
        printf("\n=== Dictionary Menu ===\n");
        printf("1. Show info about a word\n");
        printf("2. Sort words alphabetically\n");
        printf("3. Sort words by vowel count\n");
        printf("4. Add new word\n");
        printf("5. Update existing word\n");
        printf("6. Count words containing part\n");
        printf("7. Merge synonyms and antonyms\n");
        printf("8. Generate pronunciation queue\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter word: ");
                scanf("%s", word);
                getInfWord(synonyms, antonyms, word);
                break;
            case 2:
                synonyms = sortWord(synonyms);
                printf("Words sorted alphabetically.\n");
                break;
            case 3:
                synonyms = sortWord3(synonyms);
                printf("Words sorted by vowel count.\n");
                break;
            case 4:
                printf("Enter word, synonym, antonym: ");
                scanf("%s %s %s", word, synonym, antonym);
                synonyms = addWord(synonyms, antonyms, word, synonym, antonym);
                printf("Word added.\n");
                break;
            case 5:
                printf("Enter word to update, new synonym, new antonym: ");
                scanf("%s %s %s", word, synonym, antonym);
                synonyms = updateWord(NULL, synonyms, antonyms, word, synonym, antonym);
                printf("Word updated.\n");
                break;
            case 6:
                printf("Enter part to search: ");
                scanf("%s", part);
                TList *matches = countWord(synonyms, part);
               
                for (nn = matches; nn; nn = nn->next)
                    printf("%s -> %s\n", nn->word, nn->synonym);
                break;
            case 7:
                merged = merge(synonyms, antonyms);
                
                for (nn = merged; nn; n = nn->next)
                    printf("%s -> %s | %s\n", nn->word, nn->synonym, nn->antonym);
                break;
            case 8:
                pronunciationQueue = prounounciation(synonyms);
                for (n = pronunciationQueue->front; n; n = n->next)
                    printf("%s (%s)\n", n->word, n->type);
                break;
            case 9:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 9);

    fclose(synFile);
    fclose(antFile);
    return 0;
}

