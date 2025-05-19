#include "log_tree.h"

//Insert Log into BST (logs sorted by timestamp).
TTree *insertLog(TTree *tr, Log log) {
    if (tr == NULL) { //the tree is empt
        TTree *newNode = (TTree *)malloc(sizeof(TTree));
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

//Delete Log from BST.
TTree *deleteLog(TTree *root, int timestamp) {
    if (root == NULL) return NULL;

    
    if (timestamp < root->log.timestamp)
        root->left = deleteLog(root->left, timestamp);
    else if (timestamp > root->log.timestamp)
        root->right = deleteLog(root->right, timestamp);
    else {
        
        if (root->left == NULL && root->right == NULL) {
            free(root); // node without children
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
            // node has two children
            TTree *minRight = root->right;
            while (minRight->left != NULL)
                minRight = minRight->left;

            root->log = minRight->log; 
            root->right = deleteLog(root->right, minRight->log.timestamp);
        }
    }

    return root;
}

//Search Log in BST.
TTree *searchLog(TTree *root, int timestamp) {
    if (root == NULL) return NULL;

    if (timestamp == root->log.timestamp)
        return root; 

    if (timestamp < root->log.timestamp)
        return searchLog(root->left, timestamp); 

    return searchLog(root->right, timestamp);
}

//Traverse Logs in Different Orders
//1-IN order
void inOrderTraversal(TTree *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Timestamp: %d, Message: %s\n", root->log.timestamp, root->log.message);
        inOrderTraversal(root->right);
    }
}

//2-preOrder
void preOrderTraversal(TTree *root) {
    if (root != NULL) {
        printf("Timestamp: %d, Message: %s\n", root->log.timestamp, root->log.message);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

//3-postOrder
void postOrderTraversal(TTree *root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("Timestamp: %d, Message: %s\n", root->log.timestamp, root->log.message);
    }
}

//Convert Linked List to BST (to improve search efficiency).

//divide the linked list
TList* findMiddle(TList *head) {
    TList *slow = head;
    TList *fast = head;
    TList *prev = NULL;

    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (prev != NULL)
        prev->next = NULL;
    return slow;
}

//sortedListToBST
TTree* sortedListToBST(TList *head) {
    if (head == NULL) return NULL;

    // if there is only one element
    if (head->next == NULL) {
        TTree *node = malloc(sizeof(TTree));
        strcpy(node->word, head->word);
        node->left = node->right = NULL;
        return node;
    }

    TList *mid = findMiddle(head);

    TTree *root = malloc(sizeof(TTree));
    strcpy(root->word, mid->word);

    root->left = sortedListToBST(head);      // before the middle
    root->right = sortedListToBST(mid->next); // after the middle

    return root;
}