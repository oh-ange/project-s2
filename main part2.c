#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include "stack.h"
#include "queues.h"
#include "word_recursion.h"
#include "word_tree.h"

// Helper function to display a word entry from TList
void displayWordEntry(TList *entry) {
    if (entry == NULL) {
        printf("Word not found.\n");
        return;
    }
    printf("Word: %s\n", entry->word);
    printf("Synonym: %s\n", entry->synonym);
    printf("Antonym: %s\n", entry->antonym);
    printf("Characters: %d\n", entry->numChars);
    printf("Vowels: %d\n", entry->numVowels);
}

// Helper function to display a word entry from TStack
void displayStackWord(TStack *entry) {
    if (entry == NULL) {
        printf("Word not found.\n");
        return;
    }
    printf("Word: %s\n", entry->word);
    printf("Synonym: %s\n", entry->synonym);
    printf("Antonym: %s\n", entry->antonym);
    printf("Characters: %d\n", entry->numChars);
    printf("Vowels: %d\n", entry->numVowels);
}

// Helper function to display a word entry from TTree
void displayTreeNode(TTree *node) {
    if (node == NULL) {
        printf("Word not found.\n");
        return;
    }
    printf("Word: %s\n", node->word);
    printf("Synonym: %s\n", node->synonym);
    printf("Antonym: %s\n", node->antonym);
    printf("Characters: %d\n", node->numChars);
    printf("Vowels: %d\n", node->numVowels);
}

// Helper function to input a word entry
void inputWordDetails(char *word, char *syn, char *ant) {
    printf("Enter word: ");
    scanf("%99s", word);
    printf("Enter synonym: ");
    scanf("%99s", syn);
    printf("Enter antonym: ");
    scanf("%99s", ant);
}

// Function to display queue contents
void displayQueue(TQueue *q) {
    if (q->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    
    TQueueNode *current = q->front;
    printf("Queue contents:\n");
    while (current != NULL) {
        printf("%s\n", current->word);
        current = current->next;
    }
}

int main() {
    // Initialize data structures
    TList *synonymList = NULL;
    TList *antonymList = NULL;
    TStack *wordStack = NULL;
    TTree *wordTree = NULL;
    TQueue *wordQueue = NULL;
    File dictionaryFile = {"dictionary.txt"};
    
    // Temporary variables
    char word[100], syn[100], ant[100], searchWord[100];
    int choice, subChoice, rate;
    FILE *filePtr;
    
    printf("=== Dictionary Management System ===\n");
    
    do {
        printf("\nMain Menu:\n");
        printf("1. Linked List Operations\n");
        printf("2. Stack Operations\n");
        printf("3. Queue Operations\n");
        printf("4. Tree Operations\n");
        printf("5. Recursion Examples\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Linked List Operations
                do {
                    printf("\nLinked List Operations:\n");
                    printf("1. Load words from file\n");
                    printf("2. Add word to list\n");
                    printf("3. Search for word information\n");
                    printf("4. Delete word\n");
                    printf("5. Find similar words\n");
                    printf("6. Find palindrome words\n");
                    printf("7. Sort words\n");
                    printf("8. Merge synonym and antonym lists\n");
                    printf("9. Display all words\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            filePtr = fopen(dictionaryFile.filename, "r");
                            if (filePtr == NULL) {
                                printf("Error opening file.\n");
                                break;
                            }
                            synonymList = getAntoWords(filePtr);
                            fclose(filePtr);
                            printf("Words loaded from file.\n");
                            break;
                        case 2:
                            inputWordDetails(word, syn, ant);
                            // For simplicity, adding to synonym list
                            {
                                TList *newNode = malloc(sizeof(TList));
                                strcpy(newNode->word, word);
                                strcpy(newNode->synonym, syn);
                                strcpy(newNode->antonym, ant);
                                newNode->numChars = strlen(word);
                                newNode->numVowels = countVowels(word);
                                newNode->next = synonymList;
                                synonymList = newNode;
                            }
                            printf("Word added.\n");
                            break;
                        case 3:
                            printf("Enter word to search: ");
                            scanf("%99s", searchWord);
                            getInfWord2(synonymList, antonymList, searchWord);
                            break;
                        case 4:
                            printf("Enter word to delete: ");
                            scanf("%99s", word);
                            synonymList = deleteWord(&dictionaryFile, synonymList, antonymList, word);
                            break;
                        case 5:
                            printf("Enter word: ");
                            scanf("%99s", word);
                            printf("Enter similarity rate (0-100): ");
                            scanf("%d", &rate);
                            {
                                TList *similarWords = similarWord(synonymList, word, rate);
                                printf("Similar words:\n");
                                while (similarWords != NULL) {
                                    displayWordEntry(similarWords);
                                    similarWords = similarWords->next;
                                }
                            }
                            break;
                        case 6:
                            {
                                TList *palindromes = palindromWord(synonymList);
                                printf("Palindrome words:\n");
                                while (palindromes != NULL) {
                                    displayWordEntry(palindromes);
                                    palindromes = palindromes->next;
                                }
                            }
                            break;
                        case 7:
                            synonymList = sortWord2(synonymList);
                            printf("Words sorted by length.\n");
                            break;
                        case 8:
                            {
                                TList *mergedList = merge2(synonymList, antonymList);
                                printf("Lists merged.\n");
                                // Display merged list
                                TList *temp = mergedList;
                                while (temp != NULL) {
                                    displayWordEntry(temp);
                                    temp = temp->next;
                                }
                            }
                            break;
                        case 9:
                            {
                                TList *temp = synonymList;
                                printf("All words:\n");
                                while (temp != NULL) {
                                    displayWordEntry(temp);
                                    temp = temp->next;
                                }
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 2: // Stack Operations
                do {
                    printf("\nStack Operations:\n");
                    printf("1. Add word to stack\n");
                    printf("2. Search for word in stack\n");
                    printf("3. Delete word from stack\n");
                    printf("4. Convert stack to queue\n");
                    printf("5. Classify words by pronunciation\n");
                    printf("6. Find cycles in word relationships\n");
                    printf("7. Reverse stack\n");
                    printf("8. Display stack contents\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            inputWordDetails(word, syn, ant);
                            wordStack = addWordStack(wordStack, word, syn, ant);
                            printf("Word added to stack.\n");
                            break;
                        case 2:
                            printf("Enter word to search: ");
                            scanf("%99s", word);
                            {
                                TStack *found = getInfWordStack(wordStack, word);
                                displayStackWord(found);
                            }
                            break;
                        case 3:
                            printf("Enter word to delete: ");
                            scanf("%99s", word);
                            wordStack = deleteWordStack(wordStack, word);
                            break;
                        case 4:
                            wordQueue = stackToQueueun(wordStack);
                            printf("Stack converted to queue.\n");
                            displayQueue(wordQueue);
                            break;
                        case 5:
                            {
                                TStack *shortStack = NULL;
                                TStack *longStack = NULL;
                                TStack *diphthongStack = NULL;
                                pronunciationStack(wordStack, &shortStack, &longStack, &diphthongStack);
                                printf("Short words:\n");
                                while (shortStack != NULL) {
                                    displayStackWord(shortStack);
                                    shortStack = shortStack->next;
                                }
                                printf("\nLong words:\n");
                                while (longStack != NULL) {
                                    displayStackWord(longStack);
                                    longStack = longStack->next;
                                }
                                printf("\nDiphthong words:\n");
                                while (diphthongStack != NULL) {
                                    displayStackWord(diphthongStack);
                                    diphthongStack = diphthongStack->next;
                                }
                            }
                            break;
                        case 6:
                            cycleSearch(wordStack);
                            break;
                        case 7:
                            wordStack = StackRev(wordStack);
                            printf("Stack reversed.\n");
                            break;
                        case 8:
                            {
                                TStack *temp = wordStack;
                                printf("Stack contents:\n");
                                while (temp != NULL) {
                                    displayStackWord(temp);
                                    temp = temp->next;
                                }
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 3: // Queue Operations
                do {
                    printf("\nQueue Operations:\n");
                    printf("1. Create syllable queue\n");
                    printf("2. Convert list to queue\n");
                    printf("3. Display queue contents\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            wordQueue = syllable(synonymList);
                            printf("Syllable queue created.\n");
                            displayQueue(wordQueue);
                            break;
                        case 2:
                            {
                                TList *merged = merge2(synonymList, antonymList);
                                wordQueue = toQueue(merged);
                                printf("List converted to queue.\n");
                                displayQueue(wordQueue);
                            }
                            break;
                        case 3:
                            displayQueue(wordQueue);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 4: // Tree Operations
                do {
                    printf("\nTree Operations:\n");
                    printf("1. Load words into BST\n");
                    printf("2. Add word to BST\n");
                    printf("3. Update word in BST\n");
                    printf("4. Search for word in BST\n");
                    printf("5. Pre-order traversal\n");
                    printf("6. Get tree height and size\n");
                    printf("7. Mirror BST\n");
                    printf("8. Merge BSTs\n");
                    printf("9. Display BST statistics\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            filePtr = fopen(dictionaryFile.filename, "r");
                            if (filePtr == NULL) {
                                printf("Error opening file.\n");
                                break;
                            }
                            wordTree = fillTree(filePtr);
                            fclose(filePtr);
                            printf("Words loaded into BST.\n");
                            break;
                        case 2:
                            inputWordDetails(word, syn, ant);
                            wordTree = AddWordBST(wordTree, word, syn, ant);
                            printf("Word added to BST.\n");
                            break;
                        case 3:
                            inputWordDetails(word, syn, ant);
                            wordTree = UpdateWordBST(wordTree, word, syn, ant);
                            break;
                        case 4:
                            printf("Enter word to search: ");
                            scanf("%99s", word);
                            {
                                TTree *found = getInfWordTree(wordTree, word);
                                displayTreeNode(found);
                            }
                            break;
                        case 5:
                            printf("Pre-order traversal:\n");
                            TraversalBSTpreOrder(wordTree);
                            break;
                        case 6:
                            HighSizeBST(wordTree);
                            break;
                        case 7:
                            {
                                TTree *mirror = BSTMirror(wordTree);
                                printf("Mirror BST created. Pre-order traversal:\n");
                                TraversalBSTpreOrder(mirror);
                            }
                            break;
                        case 8:
                            {
                                // For demonstration, using the same tree
                                TTree *merged = BSTMerge(wordTree, wordTree);
                                printf("BSTs merged. Pre-order traversal:\n");
                                TraversalBSTpreOrder(merged);
                            }
                            break;
                        case 9:
                            printf("Tree statistics:\n");
                            printf("Size: %d\n", getSize(wordTree));
                            printf("Height: %d\n", getHeight(wordTree));
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 5: // Recursion Examples
                do {
                    printf("\nRecursion Examples:\n");
                    printf("1. Remove word occurrences from file\n");
                    printf("2. Generate word permutations\n");
                    printf("3. Find longest subsequence between words\n");
                    printf("4. Check if word is palindrome\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &subChoice);
                    
                    switch(subChoice) {
                        case 1:
                            printf("Enter word to remove: ");
                            scanf("%99s", word);
                            filePtr = fopen(dictionaryFile.filename, "r+");
                            if (filePtr == NULL) {
                                printf("Error opening file.\n");
                                break;
                            }
                            filePtr = removeWordOccurence(filePtr, word);
                            fclose(filePtr);
                            printf("Word occurrences removed from file.\n");
                            break;
                        case 2:
                            printf("Enter word for permutations: ");
                            scanf("%99s", word);
                            wordPermutation(word);
                            break;
                        case 3:
                            printf("Enter first word: ");
                            scanf("%99s", word);
                            printf("Enter second word: ");
                            scanf("%99s", syn);
                            printf("Longest subsequence length: %d\n", 
                                   longestSubseqWord(word, syn));
                            break;
                        case 4:
                            printf("Enter word to check: ");
                            scanf("%99s", word);
                            if (isPalindromWord(word)) {
                                printf("%s is a palindrome.\n", word);
                            } else {
                                printf("%s is not a palindrome.\n", word);
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while (subChoice != 0);
                break;
                
            case 0:
                printf("Exiting program.\n");
                break;
                
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
    
    // Clean up memory (simplified for example)
    // In a real program, you would want to properly free all allocated memory
    
    return 0;
}