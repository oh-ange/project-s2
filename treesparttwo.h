#ifndef WORD_TREE_H
#define WORD_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stbool.h>
#include <ctype.h>

typedef struct TreeNode {
    char word[100];
    char synonym[100];
    char antonym[100];
    int numChars;
    int numVowels;
    struct TreeNode *left, *right;
} TTree;

// Function to count vowels in a word
int countVowels(char *word);

// Function to insert a node into the BST
TTree* insertTree(TTree* root, TTree* node);

// Function to fill tree from file
TTree *fillTree(FILE *f);

// Function to get information about a word
TTree *getInfWordTree(TTree *tr, char *word);

// Function to add a new word to BST
TTree* AddWordBST(TTree *tr, char *word, char *syne, char *anton);

// Function to update a word in BST
TTree* UpdateWordBST(TTree *tr, char *word, char *syne, char *anton);

// Function to traverse BST in pre-order
void TraversalBSTpreOrder(TTree *tr);

// Function to get size of BST
int getSize(TTree *tr);

// Function to get height of BST
int getHeight(TTree *tr);

// Function to print height and size
void HighSizeBST(TTree *tr);

// Function to count nodes in range
int CountNodesInRange(TTree *root, int min, int max);

// Function to mirror BST
TTree* BSTMirror(TTree *tr);

// Function to store tree in array (in-order)
void storeInOrder(TTree *root, TTree **arr, int *index);

// Function to merge two arrays
void mergeArrays(TTree **arr1, int size1, TTree **arr2, int size2, TTree **merged);

// Function to build BST from array
TTree *buildBST(TTree **arr, int start, int end);

// Function to merge two BSTs
TTree *BSTMerge(TTree *tr1, TTree *tr2);

#endif /* WORD_TREE_H */
