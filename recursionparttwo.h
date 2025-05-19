#ifndef WORD_RECURSION_H
#define WORD_RECURSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Function to recursively remove a word from a file
void removeWordRecursive(FILE *src, FILE *dest, char *word);

// Function to remove all occurrences of a word from a file
FILE *removeWordOccurence(FILE *f, char *word);

// Function to swap two characters
void swap(char *x, char *y);

// Helper function to generate permutations recursively
void wordPermutationHelper(char *word, int start, int end);

// Function to generate all permutations of a word
void wordPermutation(char *word);

// Function to find the longest subsequence between two words
int longestSubseqWord(char *word1, char *word2);

// Helper function to check if a word is a palindrome
bool isPalindromWordHelper(char *word, int start, int end);

// Function to check if a word is a palindrome
bool isPalindromWord(char *word);

#endif /* WORD_RECURSION_H */
