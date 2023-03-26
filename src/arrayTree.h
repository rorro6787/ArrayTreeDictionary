#ifndef BST_H_
#define BST_H_
#define NUM_NODOS 26
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct arrayNode* arrayTree;

struct TNode {
    int isEnd;
    arrayTree next;
};

struct arrayNode {
    struct TNode nodes[NUM_NODOS];
};

// Create an empty tree
void create(arrayTree* tree);

// destroy the tree and free all memory
void destroy(arrayTree * tree);

// Insert the value in the tree. If it is already there, do nothing
void insert(arrayTree* tree, char* pal);

// Save the file into a tree
void saveOnTree(arrayTree* tree, FILE* f);

// Returns 1 if the word passed is stored in the tree and 0 in other
// case without taking into account capital or non capital letters
void wordInTree(arrayTree tree, char* letter, int* itIs);

// Returns the longest word stored in the tree that can be formed
// by any permutation of the letters in 'letters'
char* longestWord(arrayTree tree, char letters[]);

#endif /* BST_H_ */
