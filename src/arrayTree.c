//
// Created by emili on 07/03/2023.
//

#include "arrayTree.h"

// Create an empty tree
void create(arrayTree* tree) {
    (*tree) = (arrayTree) malloc(sizeof(struct arrayNode));
    for(int i = 0; i < 26; ++i) {
        (*tree)->nodes[i].next = NULL;
        (*tree)->nodes[i].isEnd = 0;
        (*tree)->nodes[i].found = 0;
    }
}

// destroy the tree and free all memory
void destroy(arrayTree* tree) {
    if((*tree) != NULL) {
        for (int i = 0; i < 26; ++i) {
            destroy(&((*tree)->nodes[i].next));
        }
        free((*tree));
        (*tree) = NULL;
    }
}

// Insert the value in the tree. If it is already there, do nothing
void insert(arrayTree* tree, char* pal) {
    if(pal != NULL) {
        int pos = tolower(*pal)-'a';
        if(*tree == NULL) {
            create(tree);
        }
        (*tree)->nodes[pos].found = 1;
        if(*(++pal) == 0) {
            (*tree)->nodes[pos].isEnd = 1;
        }
        else {
            insert(&((*tree)->nodes[pos].next), pal);
        }
    }
}

// Save the file into a tree
void saveOnTree(arrayTree* tree, FILE* f) {
    if(f == NULL) {
        perror("Error while opening file in rt mode");
        exit(-1);
    }
    char word[255];
    while(fscanf(f, "%s", word) != 0) {
        insert(tree, word);
        if(feof(f)) break;
    }
}

// Returns 1 if the word passed is stored in the tree and 0 in other
// case without taking into account capital or non capital letters
void wordInTree(arrayTree tree, char* letter, int* itIs) {
    if(letter != NULL && tree != NULL) {
        int pos = tolower(*letter)-'a';
        if(tree->nodes[pos].found == 0) {
            *itIs = 0;
            return;
        }
        if(*(++letter) == 0 && tree->nodes[pos].found == 1 && tree->nodes[pos].isEnd == 1) {
            *itIs = 1;
        }
        else {
            wordInTree(tree->nodes[pos].next, letter, itIs);
        }
    }
    else {
        *itIs = 0;
    }
}



