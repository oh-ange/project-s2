#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //is a C standard library header that provides functions for testing and converting characters...
#include <stdbool.h>
#include "dictionary.h"


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

//TListgetAntoWords(File *f): this function puts all words with their antonyms into a linked list, where the node 
//contains the words, their antonym, number of chars and vowels.
//function to count vowels in a word 
int countVowels(char *word) {
    int count= 0 ;
        while(*word!='\0'){
             if (tolower(*word) == 'a' || tolower(*word) == 'e' ||
            tolower(*word) == 'i' || tolower(*word) == 'o' || tolower(*word) == 'u') {
            count++;
        }
        word++;
        }
        return count ;
}

//TList *getAntoWords(FILE *f) function

TList *getAntoWords(FILE *f){
    if(f==NULL) return NULL ;
    TList *newnode=NULL ; 
    TList *tail=NULL ;
    TList *head = NULL;

    char word[100], antonym[100];


    while(fscanf(f, "%s %s" , word , antonym)==2){
// function in the C standard library (<stdio.h>) that reads formatted input from a file.    
//fscanf tries to read two strings (%s %s) from the file f.
//It stores the first string into the variable word, and the second into antonym.
//After reading, fscanf returns the number of items successfully read.  
        TLiat *newnode ;

        newnode=malloc(sizeof(TList));
    strcpy(newnode->word , word );//function to copy string
    strcpy(newnode->antonym , antonym );
    newnode->numChars=strlen(word);
    newnode->numVowels=countVowels(word);
    newnode->next=NULL ;
    if(head==NULL){
        head=tail=newnode; // the first node
    }else{
        tail->next=newnode ;
        tail=newnode ;
    }
    return head ;
    }
}

//void getInfWord2(TList *syn, TList *ant, char *inf): this procedure takes synonym or antonym as input and 
//returns the word with number of chars and vowels

void getInfWord2(TList *syn, TList *ant, char *inf){
    TList *temp ;
    temp = syn ;
    while(temp!=NULL){
        if(strcmp (temp-> synonym, inf)==0) {
            printf("Word: %s\n", temp->word);
            printf("Number of characters: %d\n", temp->numChars);
            printf("Number of vowels: %d\n", temp->numVowels);
            return;  

        }else
               if(strcmp (temp->syn , inf)==0) {
                printf("Word: %s\n", temp->word);
                printf("Number of characters: %d\n", temp->numChars);
                printf("Number of vowels: %d\n", temp->numVowels);
                return;  

        }
    }

}
//TList *sortWord2(TList *syn)

TList *sortWord2(TList *syn) {
    if (syn == NULL || syn->next == NULL) {
        return syn;
    }

    TList *i, *j;
    char *tempword;
    char *tempsyn;
    char *tempant;
    int tempChars;
    int tempVowels;

    for (i = syn; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->numChars > j->numChars) {
                // Swap word
                tempword = i->word;
                i->word = j->word;
                j->word = tempword;

                // Swap synonym
                tempsyn = i->synonym;
                i->synonym = j->synonym;
                j->synonym = tempsyn;

                // Swap antonym
                tempant = i->antonym;
                i->antonym = j->antonym;
                j->antonym = tempant;

                // Swap numChars
                tempChars = i->numChars;
                i->numChars = j->numChars;
                j->numChars = tempChars;

                // Swap numVowels
                tempVowels = i->numVowels;
                i->numVowels = j->numVowels;
                j->numVowels = tempVowels;
            }
        }
    }

    return syn;
}

//TList *deleteWord(File *f, TList *syn, TList *ant, char *word)

TList *deleteWord(File *f, TList *syn, TList *ant, char *word) {
    TList *temp ;
    TList *nextnode ;
    int pos=0 ; 
    int i=1 ;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            break;
        }
        pos++;
        temp = temp->next;
    }

    temp=syn ;
    while(i<pos-1) {
        temp=temp->next ;
        i++;
    }
    nextnode=temp->next ;
    temp->next = nextnode->next ;
    free(nextnode);

      // now we delete the word from the file
    // we have to open the file and then read
    FILE *fp = fopen(f->filename, "r");

    // now we need to create temp file to put all words except the one that we want to remove
    FILE *tempFile;
    tempFile = fopen("temp.txt", "w");

    // next we have to move all words to the temp file except the target one
    char wordBuffer[100];
    while (fscanf(fp, "%s", wordBuffer) == 1) {
        if (strcmp(wordBuffer, word) != 0) {
            fprintf(tempFile, "%s ", wordBuffer);
        }
    }

    fclose(fp);
    fclose(tempFile);

    remove(f->filename); // removing the original file
    rename("temp.txt", f->filename); // and we replace it by the temp
}

//TList *similarWord(TList *syn, char *word, rate)
TList *similarWord(TList *syn, char *word, rate) {
    TList *result = NULL;
    TList *last = NULL;
    TList *temp = syn;
    int same ; 
    int i ;
    int length ; 
    int percent ;

    while (temp != NULL) {
        same = 0;
        i = 0;

        // Count how many characters are the same in the same positions
        while (word[i] != '\0' && temp->word[i] != '\0') {
            if (word[i] == temp->word[i]) {
                same++;
            }
            i++;
        }
        length=strlen(word);
        percent =(same * 100) / length ;
        if (percent >= rate) {
            // Add the word to the new list
            TList *newNode = malloc(sizeof(TList));
            strcpy(newNode->word, temp->word);
            strcpy(newNode->synonym, temp->synonym);
            strcpy(newNode->antonym, temp->antonym);
            newNode->numChars = temp->numChars;
            newNode->numVowels = temp->numVowels;
            newNode->next = NULL;
            //It creates a new copy of a string in memory.

            if (result == NULL) {
                result = newNode;
                last = newNode;
            } else {
                last->next = newNode;
                last = newNode;
            }
        }

        temp = temp->next;
    }

    return result;
}

//TList *palindromWord(TList *syn)

bool isPalindrome(char *word) {
    int start = 0;                      // Start at beginning of word
    int end = strlen(word) - 1;         // End at last character
    
    while (start < end) {               // Meet in the middle
        if (word[start] != word[end]) { // Compare letters
            return false;               // Not matching = not palindrome
        }
        start++;                        // Move forward
        end--;                          // Move backward
    }
    return true;                        // All matched = palindrome
}

//function to insert 
TList *insertNode(TList *head, TList *newNode) {
    newNode->next = head;
    return newNode;
}

TList *sort(TList *syn) {
    if (syn == NULL || syn->next == NULL) {
        return syn;  // Already sorted if empty or single element
    }

    TList *i, *j;
    char *tempWord;
    char *tempSyn;
    char *tempAnt;
    int tempChars;
    int tempVowels;

    for (i = syn; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            // Compare words alphabetically using strcmp
            if (strcmp(i->word, j->word) > 0) {
                // Swap word
                tempWord = i->word;
                i->word = j->word;
                j->word = tempWord;

                // Swap synonym
                tempSyn = i->synonym;
                i->synonym = j->synonym;
                j->synonym = tempSyn;

                // Swap antonym
                tempAnt = i->antonym;
                i->antonym = j->antonym;
                j->antonym = tempAnt;

                // Swap numChars (to keep data consistent)
                tempChars = i->numChars;
                i->numChars = j->numChars;
                j->numChars = tempChars;

                // Swap numVowels (to keep data consistent)
                tempVowels = i->numVowels;
                i->numVowels = j->numVowels;
                j->numVowels = tempVowels;
            }
        }
    }

    return syn;
}

//the final function
TList *palindromWord(TList *syn) {
    TList *palindromes = NULL;
    TList *palindromesNosorted = NULL;
    TList *temp = syn;      
    
    while (temp!= NULL) {
        if (isPalindrome(temp->word)) {
            TList *newNode = malloc(sizeof(TList));
            newNode->word = strdup(temp->word);   
            newNode->synonym = strdup(temp->synonym); 
            newNode->antonym = strdup(temp->antonym); 
            newNode->numChars = temp->numChars;     
            newNode->numVowels = temp->numVowels;  
            newNode->next = NULL;
            
            palindromesNosorted = insertNode(palindromesNosorted ,newNode );
        }
        temp= temp->next; 
    }
    palindromes=sort(syn);
    
    return palindromes;  
}

//TList *merge2(TList *syn, TList *ant)

TList *merge2(TList *syn, TList *ant) {
    TList *head = NULL;  // Will point to first node
    TList *last = NULL;  // Will point to last node

    // Loop through both lists until one ends
    while (syn != NULL && ant != NULL) {
        // Create new node
        TList *newNode = malloc(sizeof(TList));

        // Copy data from syn list
        newNode->word = strdup(syn->word);
        newNode->synonym = strdup(syn->synonym);
        newNode->numChars = syn->numChars;
        newNode->numVowels = syn->numVowels;

        //  Copy antonym from ant list
        newNode->antonym = strdup(ant->antonym);
        newNode->next = NULL;

        // Add node to merged list
        if (head == NULL) {
            head = newNode;       // First node
        } else {
            last->next = newNode; // Link to previous
        }
        last = newNode;           // Update last pointer

        // Move to next nodes
        syn = syn->next;
        ant = ant->next;
    }

    // Make list circular
    if (last != NULL) {
        last->next = head;
    }

    return head;
}

//function to count the syllables
int countSyllables(char *word) {
    int count = 0;
    int i = 0;
    while (word[i] != '\0') {
        if (strchr("aeiouAEIOU", word[i])) {
            count++;
            while (strchr("aeiouAEIOU", word[i])) {
                i++;  // Skip any consecutive vowels ike "ee" in "see"
            }
        } else {
            i++;
        }
    }
    // Every word has at least 1 syllable (
    if (count == 0) {
        return 1;
    }
    return count;
}
//Creating a Queue
TQueue *createQueue() {
    TQueue *q = malloc(sizeof(TQueue));
    q->front = q->rear = NULL;
    return q;
}
//Adding to Queue (Enqueue)

void enqueue(Queue *q, char *word) {
    // Create new node
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode->data = strdup(word); // Copy the word
    newNode->next = NULL;         // Will be last item
    
    // If queue is empty
    if (q->back == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } 
    else {
        q->rear->next = newNode; /
        q->rear = newNode;      
    }
}

//final function
Queue* syllable(TList* syn) {
    Queue *q = createQueue();
    
    // Add words to queue based on syllables
    for (int s = 1; s <= 10; s++) {
        TList *temp = syn;
        while (temp != NULL) {
            if (countSyllables(temp->word) == s) {
                enqueue(q, temp->word);
            }
            temp = temp->next;
        }
        enqueue(q, ""); // Add separator
    }
    return q;
}

//TQueue *toQueue(TList *merged) 

TQueue *toQueue(TList *merged) {
    // Create empty queue
    TQueue *q = malloc(sizeof(TQueue));
    q->front = NULL;
    q->rear = NULL;

    // Temporary pointer to walk through list
    TList *temp = merged;

    while (temp != NULL) {
        // Create new queue node
        TQueueNode *newNode = malloc(sizeof(TQueueNode));
        newNode->word = strdup(temp->word);
        newNode->next = NULL;

        // Add to queue
        if (q->front == NULL) {
            // First node in queue
            q->front = newNode;
            q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
        // Move to next node
        temp = temp->next;
    }
    return q;
}

