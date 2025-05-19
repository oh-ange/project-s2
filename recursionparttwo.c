#include "word_recursion.h"

void removeWordRecursive(FILE *src, FILE *dest, char *word) {
    char temp[100];
    
    if (fscanf(src, "%s", temp == 1) ) {
        
        if (strcmp(temp, word) != 0) {
            fprintf(dest, "%s ", temp);
        }

    
        removeWordRecursive(src, dest, temp);
    }
}

//File *removeWordOccurence(File *f, char *word):

FILE *removeWordOccurence(FILE *f, char *word) {
    if (f == NULL) return NULL;

    FILE *temp = fopen("temp.txt", "w");

    rewind(f);  //Reset file pointer to the beginning of the input file
    removeWordRecursive(f, temp, word);

    fclose(f);
    fclose(temp);

    remove("input.txt");    
    rename("temp.txt", "input.txt");

    FILE *newFile = fopen("input.txt", "r");//read mode
    return newFile;
}

// Function to swap two characters
void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

// Recursive function to do all permutations of the word
void wordPermutationHelper(char *word, int start, int end) {
    if (start == end) {
        printf("%s\n", word);  // Print one permutation
    } else {
        for (int i = start; i <= end; i++) {
            swap(&word[start], &word[i]);              // Swap current index with start
            wordPermutationHelper(word, start + 1, end);  // Recurse for the rest of the string
            swap(&word[start], &word[i]);              // Backtrack 
        }
    }
}

// void wordPermutation(char *word)
void wordPermutation(char *word) {
    int length = strlen(word);
    wordPermutationHelper(word, 0, length - 1);
}

//int longestSubseqWord(char *word1, char *word2)
int longestSubseqWord(char *word1, char *word2) {
    int   option1 ;
    int   option2 ;
    if (*word1 == '\0' || *word2 == '\0') {
        return 0;
    }

    if (*word1 == *word2) {
        return 1 + longestSubseqWord(word1 + 1, word2 + 1);
    } else {
        option1 = longestSubseqWord(word1 + 1, word2);
        option2 = longestSubseqWord(word1, word2 + 1);

        if (option1 > option2) {
            return option1;
        } else {
            return option2;
        }
    }
}


bool isPalindromWordHelper(char *word, int start, int end) {
    if (start >= end) {
        return true;  // If pointers crossed, it's palindrome
    }
    if (word[start] != word[end]) {
        return false; // Characters don't match → not palindrome
    }
    // Move pointers closer and check again
    return isPalindromWordHelper(word, start + 1, end - 1);
}
//bool isPalindromWord(char *word)
bool isPalindromWord(char *word) {
    int len ;
    len = strlen(word);
    return isPalindromWordHelper(word, 0, len - 1);
}

