#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// function to create a new Trie node
struct TrieNode *createNode(void) {
    struct TrieNode *pNode = malloc(sizeof(struct TrieNode));
    pNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
    }
    return pNode;
}

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *pTrie = malloc(sizeof(struct Trie));
    pTrie->root = createNode();
    return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct TrieNode *crawl = pTrie->root;
    while (*word) {
        int index = *word - 'a';
        if (!crawl->children[index]) {
            crawl->children[index] = createNode();
        }
        crawl = crawl->children[index];
        word++;
    }
    crawl->count++;
}

// computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct TrieNode *crawl = pTrie->root;
    while (*word) {
        int index = *word - 'a';
        if (!crawl->children[index]) {
            return 0;
        }
        crawl = crawl->children[index];
        word++;
    }
    return crawl->count;
}

// function to deallocate a Trie node
void deallocateNode(struct TrieNode *node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            deallocateNode(node->children[i]);
        }
    }
    free(node);
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        deallocateNode(pTrie->root);
    }
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File could not be opened\n");
        return 0;
    }
    
    int numWords;
    fscanf(file, "%d\n", &numWords);

    for (int i = 0; i < numWords; ++i) {
        pInWords[i] = malloc(sizeof(char) * 100);
        fscanf(file, "%s\n", pInWords[i]);
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];
    
    //read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) 
    {
        printf("%s\n", inWords[i]);
    }
    
    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) 
    {
        insert(pTrie, inWords[i]);
    }
    
    // parse line by line, and insert each word to the trie data structure
    
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) 
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL) 
    {
        printf("There is an error in this program\n");
    }

    // free the input words array
    for (int i = 0; i < numWords; i++) {
        free(inWords[i]);
    }

    return 0;
}
