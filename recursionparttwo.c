#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "WORD_RECURSION_H"
// Recursive helper to remove occurrences of a word from file
void removeWordRecursive(FILE *src, FILE *dest, const char *word) {
    char temp[100];
    if (fscanf(src, "%99s", temp) == 1) {
        if (strcmp(temp, word) != 0) {
            fprintf(dest, "%s ", temp);
        }
        removeWordRecursive(src, dest, word);
    }
}

// Remove all occurrences of word from file f and return new FILE*
FILE *removeWordOccurence(FILE *f, const char *word) {
    if (f == NULL) return NULL;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Failed to open temp file");
        return NULL;
    }

    rewind(f);
    removeWordRecursive(f, temp, word);

    fclose(f);
    fclose(temp);

    if (remove("input.txt") != 0) {
        perror("Failed to remove input file");
        return NULL;
    }
    if (rename("temp.txt", "input.txt") != 0) {
        perror("Failed to rename temp file");
        return NULL;
    }

    FILE *newFile = fopen("input.txt", "r");
    return newFile;
}

// Swap two characters helper
void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

// Recursive helper to print all permutations of word
void wordPermutationHelper(char *word, int start, int end) {
    if (start == end) {
        printf("%s\n", word);
    } else {
        for (int i = start; i <= end; i++) {
            swap(&word[start], &word[i]);
            wordPermutationHelper(word, start + 1, end);
            swap(&word[start], &word[i]); // backtrack
        }
    }
}

// Print all permutations of word
void wordPermutation(char *word) {
    int length = strlen(word);
    wordPermutationHelper(word, 0, length - 1);
}

// Find length of longest common subsequence of word1 and word2
int longestSubseqWord(char *word1, char *word2) {
    if (*word1 == '\0' || *word2 == '\0') {
        return 0;
    }

    if (*word1 == *word2) {
        return 1 + longestSubseqWord(word1 + 1, word2 + 1);
    } else {
        int option1 = longestSubseqWord(word1 + 1, word2);
        int option2 = longestSubseqWord(word1, word2 + 1);
        return (option1 > option2) ? option1 : option2;
    }
}

// Recursive helper to check if word is palindrome
bool isPalindromWordHelper(char *word, int start, int end) {
    if (start >= end) return true;
    if (word[start] != word[end]) return false;
    return isPalindromWordHelper(word, start + 1, end - 1);
}

// Check if a word is palindrome
bool isPalindromWord(char *word) {
    int len = strlen(word);
    return isPalindromWordHelper(word, 0, len - 1);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;
    char buffer[100];
    FILE *file = fopen("input.txt", "r+");

    if (file == NULL) {
        printf("File 'input.txt' not found. Creating a new one with sample content...\n");
        file = fopen("input.txt", "w+");
        fprintf(file, "apple banana apple orange apple\n");
        rewind(file);
    }

    do {
        printf("\n--- Menu ---\n");
        printf("1. Remove a word from file\n");
        printf("2. Print all permutations of a word\n");
        printf("3. Find longest common subsequence length between two words\n");
        printf("4. Check if a word is palindrome\n");
        printf("5. Show file content\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: {
                printf("Enter the word to remove: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // remove newline

                FILE *newFile = removeWordOccurence(file, buffer);
                if (newFile != NULL) {
                    printf("Word '%s' removed.\n", buffer);
                    fclose(file);
                    file = newFile;
                } else {
                    printf("Error processing file.\n");
                }
                break;
            }

            case 2: {
                printf("Enter a word to permute: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // remove newline

                printf("Permutations:\n");
                wordPermutation(buffer);
                break;
            }

            case 3: {
                char word1[100], word2[100];
                printf("Enter first word: ");
                fgets(word1, sizeof(word1), stdin);
                word1[strcspn(word1, "\n")] = '\0';
                printf("Enter second word: ");
                fgets(word2, sizeof(word2), stdin);
                word2[strcspn(word2, "\n")] = '\0';

                int result = longestSubseqWord(word1, word2);
                printf("Longest common subsequence length: %d\n", result);
                break;
            }

            case 4: {
                printf("Enter a word to check palindrome: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                if (isPalindromWord(buffer)) {
                    printf("'%s' is a palindrome.\n", buffer);
                } else {
                    printf("'%s' is NOT a palindrome.\n", buffer);
                }
                break;
            }

            case 5: {
                printf("File content:\n");
                rewind(file);
                while (fscanf(file, "%99s", buffer) == 1) {
                    printf("%s ", buffer);
                }
                printf("\n");
                rewind(file);
                break;
            }

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    fclose(file);
    return 0;
}

