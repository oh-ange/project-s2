#ifndef LOG_TREE_H
#define LOG_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Log {
    int timestamp;         
    char message[256];    
} Log;

typedef struct TTree {
    Log log;              
    struct TTree *left;   
    struct TTree *right;   
} TTree;

typedef struct TList {
    char word[256];
    struct TList *next;
} TList;

// Function declarations for BST operations
TTree *insertLog(TTree *tr, Log log);
TTree *deleteLog(TTree *root, int timestamp);
TTree *searchLog(TTree *root, int timestamp);

// Traversal functions
void inOrderTraversal(TTree *root);
void preOrderTraversal(TTree *root);
void postOrderTraversal(TTree *root);

// List to BST conversion
TList* findMiddle(TList *head);
TTree* sortedListToBST(TList *head);

#endif /* LOG_TREE_H */