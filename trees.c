#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TREES_H"
typedef struct Log { 
    int timestamp;         
    char message[256];    
} Log;

typedef struct TTree {
    Log log;              
    struct TTree *left;   
    struct TTree *right;   
} TTree;

// Insert Log into BST (sorted by timestamp)
TTree *insertLog(TTree *tr, Log log) {
    if (tr == NULL) {
        TTree *newNode = (TTree *)malloc(sizeof(TTree));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->log = log;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (log.timestamp < tr->log.timestamp)
        tr->left = insertLog(tr->left, log);
    else
        tr->right = insertLog(tr->right, log);

    return tr;
}

// Delete Log from BST
TTree *deleteLog(TTree *root, int timestamp) {
    if (root == NULL) return NULL;

    if (timestamp < root->log.timestamp)
        root->left = deleteLog(root->left, timestamp);
    else if (timestamp > root->log.timestamp)
        root->right = deleteLog(root->right, timestamp);
    else {
        // Found node to delete
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            TTree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TTree *temp = root->left;
            free(root);
            return temp;
        }
        else {
            // Node with two children: Find inorder successor (min in right subtree)
            TTree *minRight = root->right;
            while (minRight->left != NULL)
                minRight = minRight->left;

            root->log = minRight->log;
            root->right = deleteLog(root->right, minRight->log.timestamp);
        }
    }
    return root;
}

// Search Log in BST
TTree *searchLog(TTree *root, int timestamp) {
    if (root == NULL) return NULL;

    if (timestamp == root->log.timestamp)
        return root;

    if (timestamp < root->log.timestamp)
        return searchLog(root->left, timestamp);

    return searchLog(root->right, timestamp);
}

// Inorder traversal of BST
void inOrderTraversal(TTree *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Timestamp: %d, Message: %s\n", root->log.timestamp, root->log.message);
        inOrderTraversal(root->right);
    }
}

// Free all nodes of BST (postorder)
void freeTree(TTree *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    TTree *root = NULL;

    // Sample logs
    Log logs[] = {
        {20230519, "System started"},
        {20230520, "User logged in"},
        {20230521, "Error: Disk full"},
        {20230518, "Boot sequence initialized"},
        {20230522, "User logged out"}
    };

    // Insert logs into BST
    for (int i = 0; i < 5; i++) {
        root = insertLog(root, logs[i]);
    }

    printf("Inorder traversal after insertion:\n");
    inOrderTraversal(root);

    // Search for a log
    int searchTimestamp = 20230521;
    TTree *found = searchLog(root, searchTimestamp);
    if (found != NULL)
        printf("\nFound log with timestamp %d: %s\n", searchTimestamp, found->log.message);
    else
        printf("\nLog with timestamp %d not found\n", searchTimestamp);

    // Delete a log
    int deleteTimestamp = 20230520;
    root = deleteLog(root, deleteTimestamp);
    printf("\nInorder traversal after deleting timestamp %d:\n", deleteTimestamp);
    inOrderTraversal(root);

    // Free memory
    freeTree(root);
    root = NULL;

    return 0;
}



