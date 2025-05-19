#include "word_tree.h"

//function to count the number of vowles
int countVowels(char *word) {
    int i = 0;
    int count = 0;

    while (word[i] != '\0') {
        char c = tolower(word[i]); // change to small letter
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        i++;
    }

    return count;
}

//function to insert a new node in a BST tree
TTree* insertTree(TTree* root, TTree* node) {
    if (root == NULL)
        return node;

    if (strcmp(node->word, root->word) < 0)
        root->left = insertTree(root->left, node);
    else
        root->right = insertTree(root->right, node);

    return root;
}

//TTree *fillTree(File *f): this function returns a BST filled with words.
TTree *fillTree(FILE *f){
    if(f == NULL ) return NULL ;
    TTree *root = NULL ;
    char word[100], synonym[100], antonym[100];
while (fscanf(f, "%s %s %s", word, synonym, antonym) == 3) {
     TTree *node = malloc(sizeof(TTree));
        strcpy(node->word, word);
        strcpy(node->synonym, synonym);
        strcpy(node->antonym, antonym);
        node->numChars = strlen(word);
        node->numVowels = countVowels(word);
        node->left = node->right = NULL;
        root = insertTree(root, node);
}
    return root;
}


TTree *getInfWordTree(TTree *tr, char *word) {
    if (tr == NULL) return NULL;
    // Check current node first
    if(strcmp(tr->word, word) == 0) {
        printf("Word: %s\n", tr->word);
        printf("Synonym: %s\n", tr->synonym);
        printf("Antonym: %s\n", tr->antonym);
        printf("Characters: %d\n", tr->numChars);
        printf("Vowels: %d\n", tr->numVowels);
        return tr;
    }

     // Then search in left subtree
    TTree *leftResult = getInfWordTree(tr->left, word);
    if (leftResult != NULL) return leftResult; // Stop and return if found on left

    // Then search in right subtree
    return getInfWordTree(tr->right, word);
}

//TStack *AddWordBST(TTree *tr, char *word, char *syne, char *anton)

TTree* AddWordBST(TTree *tr, char *word, char *syne, char *anton){
    TTree* newNode ; int cmp ;
     if(tr==NULL){
        newNode = malloc(sizeof(TTree));
        strcpy(newNode->word, word);
        strcpy(newNode->synonym, syne);
        strcpy(newNode->antonym, anton);
        newNode->numChars = strlen(word);
        newNode->numVowels = countVowels(word);
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode; }
        else{   
       cmp = strcmp(word, tr->word);  
        if (cmp < 0) { //we add it in the left
        tr->left = AddWordBST(tr->left, word, syne, anton);
    } else if (cmp > 0) { // we add it in the right
        tr->right = AddWordBST(tr->right, word, syne, anton);
    }
    return tr;   
}
}


//TTree *UpdateWordBST(TTree *tr, char *word, char *syne, char *anton

TTree* UpdateWordBST(TTree *tr, char *word, char *syne, char *anton) {
    int cmp;
    if(tr==NULL) return NULL ;
    cmp = strcmp(word, tr->word);
     if (cmp < 0) {
        tr->left = UpdateWordBST(tr->left, word, syne, anton);
    } else if (cmp > 0) {
        tr->right = UpdateWordBST(tr->right, word, syne, anton);
    } else {
        strcpy(tr->synonym, syne);
        strcpy(tr->antonym, anton);
        printf("Updated: %s → Synonym: %s, Antonym: %s\n", word, syne, anton);
    }

    return tr;
}

//TTree *TraversalBSTpreOrder(TTree *tr)
void TraversalBSTpreOrder(TTree *tr) {
    if (tr == NULL) return;
    printf("Word: %s\n", tr->word);
    printf("  Synonym: %s\n", tr->synonym);
    printf("  Antonym: %s\n", tr->antonym);
    printf("  Characters: %d\n", tr->numChars);
    printf("  Vowels: %d\n", tr->numVowels);
    printf("------------------------\n");


    TraversalBSTpreOrder(tr->left);

    TraversalBSTpreOrder(tr->right);
}

//function to calculate the number of nodes

int getSize(TTree *tr) {
    if (tr == NULL) return 0;
    return 1 + getSize(tr->left) + getSize(tr->right);
}

//function to get the height of the tree

int getHeight(TTree *tr) {
    if (tr == NULL)
        return 0;

    int leftHeight = getHeight(tr->left);
    int rightHeight = getHeight(tr->right);

    if (leftHeight > rightHeight)
        return 1 + leftHeight;
    else
        return 1 + rightHeight;
}

//void HighSizeBST(TTree *tr)
void HighSizeBST(TTree *tr) {
    int size = getSize(tr);
    int height = getHeight(tr);
    printf("BST Size: %d\n", size);
    printf("BST Height: %d\n", height);
}

//Int CountNodesRanges(TTree *tr, int min, int max)

int CountNodesInRange(TTree *root, int min, int max) {
    if (root == NULL)
        return 0;

    int count = 0;
    count += CountNodesInRange(root->left, min, max);
    if (root->value >= min && root->value <= max)
        count += 1;
    count += CountNodesInRange(root->right, min, max);

    return count;
}


TTree* BSTMirror(TTree *tr) {
    if (tr == NULL)
        return NULL;

//TTree *BSTMirror(TTree *tr)
    TTree *mirror = malloc(sizeof(TTree));

    strcpy(mirror->word, tr->word);
    strcpy(mirror->synonym, tr->synonym);
    strcpy(mirror->antonym, tr->antonym);
    mirror->numChars = tr->numChars;
    mirror->numVowels = tr->numVowels;

    mirror->left = BSTMirror(tr->right);
    mirror->right = BSTMirror(tr->left);

    return mirror;
}

//store the element of a tree in a array

void storeInOrder(TTree *root, TTree **arr, int *index) {
    if (root == NULL) return;
    storeInOrder(root->left, arr, index);
    arr[(*index)++] = root;
    storeInOrder(root->right, arr, index);
}

// merge two arrays
void mergeArrays(TTree **arr1, int size1, TTree **arr2, int size2, TTree **merged) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (strcmp(arr1[i]->word, arr2[j]->word) < 0)
            merged[k++] = arr1[i++];
        else
            merged[k++] = arr2[j++];
    }
    while (i < size1) {
       merged[k++] = arr1[i++];
    } 
    while (j < size2) {
        merged[k++] = arr2[j++];
    }
}

//build bst throught an array
TTree *buildBST(TTree **arr, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    TTree *root = arr[mid];
    root->left = buildBST(arr, start, mid - 1);
    root->right = buildBST(arr, mid + 1, end);
    return root;
}

//TTree *BTSMerge(TTree *tr1, TTree *tr2)
TTree *BSTMerge(TTree *tr1, TTree *tr2) {
    int size1 = getSize(tr1);
    int size2 = getSize(tr2);

    TTree *arr1[size1], *arr2[size2], *merged[size1 + size2];
    int index1 = 0, index2 = 0;

    storeInOrder(tr1, arr1, &index1);
    storeInOrder(tr2, arr2, &index2);

    mergeArrays(arr1, size1, arr2, size2, merged);

    return buildBST(merged, 0, size1 + size2 - 1);
}
