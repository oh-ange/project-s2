#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "WORD_TREE_H"
typedef struct TreeNode {
    char word[100];
    char synonym[100];
    char antonym[100];
    int numChars;
    int numVowels;
    struct TreeNode *left, *right;
} TTree;

// Count vowels in a word
int countVowels(const char *word) {
    int count = 0;
    for (int i = 0; word[i]; i++) {
        char c = tolower(word[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            count++;
    }
    return count;
}

// Insert node into BST by word lex order
TTree* insertNode(TTree* root, TTree* node) {
    if (!root) return node;

    if (strcmp(node->word, root->word) < 0)
        root->left = insertNode(root->left, node);
    else
        root->right = insertNode(root->right, node);

    return root;
}

// Fill tree from file (word synonym antonym per line)
TTree* fillTree(FILE* f) {
    if (!f) return NULL;
    TTree* root = NULL;
    char w[100], syn[100], ant[100];
    while (fscanf(f, "%99s %99s %99s", w, syn, ant) == 3) {
        TTree* node = malloc(sizeof(TTree));
        strcpy(node->word, w);
        strcpy(node->synonym, syn);
        strcpy(node->antonym, ant);
        node->numChars = strlen(w);
        node->numVowels = countVowels(w);
        node->left = node->right = NULL;
        root = insertNode(root, node);
    }
    return root;
}

// Search for a word and print info, return node or NULL
TTree* getInfWordTree(TTree* tr, const char* word) {
    if (!tr) return NULL;
    int cmp = strcmp(word, tr->word);
    if (cmp == 0) {
        printf("Word: %s\nSynonym: %s\nAntonym: %s\nCharacters: %d\nVowels: %d\n",
            tr->word, tr->synonym, tr->antonym, tr->numChars, tr->numVowels);
        return tr;
    } else if (cmp < 0)
        return getInfWordTree(tr->left, word);
    else
        return getInfWordTree(tr->right, word);
}

// Add word to BST, ignore if exists
TTree* AddWordBST(TTree* tr, const char* word, const char* syn, const char* ant) {
    if (!tr) {
        TTree* node = malloc(sizeof(TTree));
        strcpy(node->word, word);
        strcpy(node->synonym, syn);
        strcpy(node->antonym, ant);
        node->numChars = strlen(word);
        node->numVowels = countVowels(word);
        node->left = node->right = NULL;
        return node;
    }
    int cmp = strcmp(word, tr->word);
    if (cmp < 0)
        tr->left = AddWordBST(tr->left, word, syn, ant);
    else if (cmp > 0)
        tr->right = AddWordBST(tr->right, word, syn, ant);
    // else do nothing if word exists
    return tr;
}

// Update synonym and antonym if word exists
TTree* UpdateWordBST(TTree* tr, const char* word, const char* syn, const char* ant) {
    if (!tr) return NULL;
    int cmp = strcmp(word, tr->word);
    if (cmp == 0) {
        strcpy(tr->synonym, syn);
        strcpy(tr->antonym, ant);
        printf("Word '%s' updated.\n", word);
    } else if (cmp < 0)
        tr->left = UpdateWordBST(tr->left, word, syn, ant);
    else
        tr->right = UpdateWordBST(tr->right, word, syn, ant);
    return tr;
}

// Preorder traversal print
void TraversalBSTpreOrder(TTree* tr) {
    if (!tr) return;
    printf("%s - Syn: %s, Ant: %s, Chars: %d, Vowels: %d\n",
           tr->word, tr->synonym, tr->antonym, tr->numChars, tr->numVowels);
    TraversalBSTpreOrder(tr->left);
    TraversalBSTpreOrder(tr->right);
}

// Get size (count nodes)
int getSize(TTree* tr) {
    if (!tr) return 0;
    return 1 + getSize(tr->left) + getSize(tr->right);
}

// Get height of BST
int getHeight(TTree* tr) {
    if (!tr) return 0;
    int lh = getHeight(tr->left);
    int rh = getHeight(tr->right);
    return (lh > rh ? lh : rh) + 1;
}

// Print size and height
void HighSizeBST(TTree* tr) {
    printf("Size: %d\n", getSize(tr));
    printf("Height: %d\n", getHeight(tr));
}

// Create mirror of BST
TTree* BSTMirror(TTree* tr) {
    if (!tr) return NULL;
    TTree* mirror = malloc(sizeof(TTree));
    *mirror = *tr;
    mirror->left = BSTMirror(tr->right);
    mirror->right = BSTMirror(tr->left);
    return mirror;
}

// Inorder store nodes in array
void storeInOrder(TTree* tr, TTree** arr, int* idx) {
    if (!tr) return;
    storeInOrder(tr->left, arr, idx);
    arr[(*idx)++] = tr;
    storeInOrder(tr->right, arr, idx);
}

// Merge two sorted arrays of nodes into merged array
void mergeArrays(TTree** arr1, int size1, TTree** arr2, int size2, TTree** merged) {
    int i=0, j=0, k=0;
    while (i<size1 && j<size2) {
        if (strcmp(arr1[i]->word, arr2[j]->word) < 0)
            merged[k++] = arr1[i++];
        else
            merged[k++] = arr2[j++];
    }
    while (i<size1) merged[k++] = arr1[i++];
    while (j<size2) merged[k++] = arr2[j++];
}

// Build balanced BST from sorted nodes
TTree* buildBST(TTree** arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    TTree* root = arr[mid];
    root->left = buildBST(arr, start, mid-1);
    root->right = buildBST(arr, mid+1, end);
    return root;
}

// Merge two BSTs into one balanced BST
TTree* BSTMerge(TTree* tr1, TTree* tr2) {
    int size1 = getSize(tr1);
    int size2 = getSize(tr2);

    TTree** arr1 = malloc(sizeof(TTree*) * size1);
    TTree** arr2 = malloc(sizeof(TTree*) * size2);
    TTree** merged = malloc(sizeof(TTree*) * (size1 + size2));

    int idx1 = 0, idx2 = 0;
    storeInOrder(tr1, arr1, &idx1);
    storeInOrder(tr2, arr2, &idx2);

    mergeArrays(arr1, size1, arr2, size2, merged);

    TTree* mergedRoot = buildBST(merged, 0, size1 + size2 -1);

    free(arr1);
    free(arr2);
    free(merged);

    return mergedRoot;
}

// Free tree memory
void freeTree(TTree* tr) {
    if (!tr) return;
    freeTree(tr->left);
    freeTree(tr->right);
    free(tr);
}

// Simple example main with menu to test
int main() {
    TTree* dict = NULL;
    int option;
    char w[100], syn[100], ant[100];
    FILE *f;

    do {
        printf("\n1.Load dictionary from file\n2.Add word\n3.Update word\n4.Search word\n5.Print all\n6.Show size/height\n7.Mirror tree\n8.Exit\nChoose: ");
        scanf("%d", &option);
        getchar(); // consume newline

        switch(option) {
            case 1:
                printf("Enter filename: ");
                char filename[100];
                fgets(filename, 100, stdin);
                filename[strcspn(filename, "\n")] = 0;
                f = fopen(filename, "r");
                if (!f) {
                    printf("Cannot open file\n");
                    break;
                }
                if (dict) freeTree(dict);
                dict = fillTree(f);
                fclose(f);
                printf("Dictionary loaded\n");
                break;

            case 2:
                printf("Enter word: ");
                fgets(w, 100, stdin);
                w[strcspn(w, "\n")] = 0;
                printf("Enter synonym: ");
                fgets(syn, 100, stdin);
                syn[strcspn(syn, "\n")] = 0;
                printf("Enter antonym: ");
                fgets(ant, 100, stdin);
                ant[strcspn(ant, "\n")] = 0;
                dict = AddWordBST(dict, w, syn, ant);
                printf("Word added\n");
                break;

            case 3:
                printf("Enter word to update: ");
                fgets(w, 100, stdin);
                w[strcspn(w, "\n")] = 0;
                printf("Enter new synonym: ");
                fgets(syn, 100, stdin);
                syn[strcspn(syn, "\n")] = 0;
                printf("Enter new antonym: ");
                fgets(ant, 100, stdin);
                ant[strcspn(ant, "\n")] = 0;
                dict = UpdateWordBST(dict, w, syn, ant);
                break;

            case 4:
                printf("Enter word to search: ");
                fgets(w, 100, stdin);
                w[strcspn(w, "\n")] = 0;
                if (!getInfWordTree(dict, w))
                    printf("Word not found\n");
                break;

            case 5:
                TraversalBSTpreOrder(dict);
                break;

            case 6:
                HighSizeBST(dict);
                break;

            case 7: {
                TTree* mirror = BSTMirror(dict);
                printf("Mirror tree:\n");
                TraversalBSTpreOrder(mirror);
                freeTree(mirror);
                break;
            }

            case 8:
                if (dict) freeTree(dict);
                printf("Exiting\n");
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (option != 8);

    return 0;
}

