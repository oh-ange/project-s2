#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LINKEDLISTANDQUEUES_H"

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
typedef struct TList {
    char word[100];
    char synonym[100];
    char antonym[100];
    int char_count;
    int vowel_count;
    struct TList *next;
    struct TList *prev;
} TList;

typedef struct TQueueNode {
    char word[100];
    char type[20];  // short, long, diphthong
    struct TQueueNode *next;
} TQueueNode;

typedef struct TQueue {
    TQueueNode *front;
    TQueueNode *rear;
} TQueue;

// Analyze the word to count characters and vowels
void analyzeWord(const char *word, int *char_count, int *vowel_count) {
    *char_count = strlen(word);
    *vowel_count = 0;
    for (int i = 0; word[i]; i++) {
        char c = tolower(word[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            (*vowel_count)++;
    }
}

// Add a new node to the word list (TList)
TList *addToList(TList *head, const char *word, const char *syn) {
    TList *node = (TList *)malloc(sizeof(TList));
    if (!node) {
        printf("Memory allocation failed\n");
        return head;
    }
    strcpy(node->word, word);
    strcpy(node->synonym, syn);
    node->antonym[0] = '\0';  // antonym is empty initially
    analyzeWord(word, &node->char_count, &node->vowel_count);

    node->next = head;
    node->prev = NULL;
    if (head) head->prev = node;
    return node;
}

// Read synonyms and words from a file (not used in main here, but available)
TList *getSynWords(FILE *f) {
    char line[200];
    TList *head = NULL;
    while (fgets(line, sizeof(line), f)) {
        char *word = strtok(line, "=");
        char *syn = strtok(NULL, "#\n");
        if (word && syn) {
            head = addToList(head, word, syn);
        }
    }
    return head;
}

// Print information about a given word (synonym and antonym details)
void getInfWord(TList *syn, TList *ant, const char *word) {
    int foundSyn = 0, foundAnt = 0;
    for (TList *node = syn; node; node = node->next) {
        if (strcmp(node->word, word) == 0) {
            printf("Synonym: %s, Chars: %d, Vowels: %d\n",
                   node->synonym, node->char_count, node->vowel_count);
            foundSyn = 1;
            break;
        }
    }
    for (TList *node = ant; node; node = node->next) {
        if (strcmp(node->word, word) == 0) {
            printf("Antonym: %s, Chars: %d, Vowels: %d\n",
                   node->antonym, node->char_count, node->vowel_count);
            foundAnt = 1;
            break;
        }
    }
    if (!foundSyn && !foundAnt)
        printf("Word '%s' not found.\n", word);
}

// Sort the list alphabetically by word
TList *sortWord(TList *head) {
    for (TList *i = head; i; i = i->next) {
        for (TList *j = i->next; j; j = j->next) {
            if (strcmp(i->word, j->word) > 0) {
                char tmp[100];
                strcpy(tmp, i->word); strcpy(i->word, j->word); strcpy(j->word, tmp);
                strcpy(tmp, i->synonym); strcpy(i->synonym, j->synonym); strcpy(j->synonym, tmp);

                int t = i->char_count; i->char_count = j->char_count; j->char_count = t;
                t = i->vowel_count; i->vowel_count = j->vowel_count; j->vowel_count = t;
            }
        }
    }
    return head;
}

// Sort the list descending by number of vowels
TList *sortWordByVowels(TList *head) {
    for (TList *i = head; i; i = i->next) {
        for (TList *j = i->next; j; j = j->next) {
            if (i->vowel_count < j->vowel_count) {
                char tmp[100];
                strcpy(tmp, i->word); strcpy(i->word, j->word); strcpy(j->word, tmp);
                strcpy(tmp, i->synonym); strcpy(i->synonym, j->synonym); strcpy(j->synonym, tmp);

                int t = i->vowel_count; i->vowel_count = j->vowel_count; j->vowel_count = t;
                t = i->char_count; i->char_count = j->char_count; j->char_count = t;
            }
        }
    }
    return head;
}

// Update synonym and antonym for a specific word
void updateWord(TList *syn, TList *ant, const char *word, const char *newSyn, const char *newAnt) {
    for (TList *node = syn; node; node = node->next) {
        if (strcmp(node->word, word) == 0) {
            strcpy(node->synonym, newSyn);
        }
    }
    for (TList *node = ant; node; node = node->next) {
        if (strcmp(node->word, word) == 0) {
            strcpy(node->antonym, newAnt);
        }
    }
}

// Merge synonym and antonym lists into one list
TList *mergeLists(TList *syn, TList *ant) {
    TList *merged = NULL;
    for (TList *s = syn; s; s = s->next) {
        for (TList *a = ant; a; a = a->next) {
            if (strcmp(s->word, a->word) == 0) {
                TList *node = (TList *)malloc(sizeof(TList));
                strcpy(node->word, s->word);
                strcpy(node->synonym, s->synonym);
                strcpy(node->antonym, a->antonym);
                node->char_count = s->char_count;
                node->vowel_count = s->vowel_count;

                node->next = merged;
                node->prev = NULL;
                if (merged) merged->prev = node;
                merged = node;
            }
        }
    }
    return merged;
}

// Add a new word with synonym and antonym to both lists
void addWord(TList **syn, TList **ant, const char *word, const char *synonym, const char *antonym) {
    *syn = addToList(*syn, word, synonym);
    *ant = addToList(*ant, word, antonym);
}

// Create a queue to classify words by vowel count type
TQueue *pronunciationQueue(TList *syn) {
    TQueue *q = (TQueue *)malloc(sizeof(TQueue));
    q->front = q->rear = NULL;

    for (TList *node = syn; node; node = node->next) {
        TQueueNode *qn = (TQueueNode *)malloc(sizeof(TQueueNode));
        strcpy(qn->word, node->word);
        qn->next = NULL;

        if (node->vowel_count <= 2)
            strcpy(qn->type, "short");
        else if (node->vowel_count == 3)
            strcpy(qn->type, "long");
        else
            strcpy(qn->type, "diphthong");

        if (!q->front) {
            q->front = q->rear = qn;
        } else {
            q->rear->next = qn;
            q->rear = qn;
        }
    }
    return q;
}

// Print the list of words with their synonyms, antonyms, and counts
void printList(TList *head) {
    printf("List contents:\n");
    for (TList *node = head; node; node = node->next) {
        printf("Word: %s, Synonym: %s, Antonym: %s, Chars: %d, Vowels: %d\n",
               node->word, node->synonym, node->antonym, node->char_count, node->vowel_count);
    }
    printf("\n");
}

// Print the queue contents with word type classification
void printQueue(TQueue *q) {
    printf("Queue contents:\n");
    for (TQueueNode *node = q->front; node; node = node->next) {
        printf("Word: %s, Type: %s\n", node->word, node->type);
    }
    printf("\n");
}

int main() {
    // Example usage

    // 1. Create synonym and antonym lists
    TList *synonyms = NULL;
    TList *antonyms = NULL;

    // 2. Add words manually with synonyms and antonyms
    addWord(&synonyms, &antonyms, "happy", "joyful", "sad");
    addWord(&synonyms, &antonyms, "fast", "quick", "slow");
    addWord(&synonyms, &antonyms, "big", "large", "small");
    addWord(&synonyms, &antonyms, "bright", "shiny", "dark");

    // 3. Update a word's synonym and antonym
    updateWord(synonyms, antonyms, "fast", "speedy", "sluggish");

    // 4. Print lists before sorting
    printf("Before sorting:\n");
    printList(synonyms);

    // 5. Sort words alphabetically
    synonyms = sortWord(synonyms);

    printf("After alphabetical sorting:\n");
    printList(synonyms);

    // 6. Sort words by vowel count descending
    synonyms = sortWordByVowels(synonyms);

    printf("After sorting by vowels (descending):\n");
    printList(synonyms);

    // 7. Print information for a specific word
    printf("Information for 'fast':\n");
    getInfWord(synonyms, antonyms, "fast");

    // 8. Merge synonym and antonym lists
    TList *mergedList = mergeLists(synonyms, antonyms);
    printf("Merged list:\n");
    printList(mergedList);

    // 9. Create queue classifying words by vowel count type
    TQueue *queue = pronunciationQueue(synonyms);
    printQueue(queue);

    // Note: Memory freeing is omitted here for simplicity.

    return 0;
}

