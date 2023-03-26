//
// Created by emili on 07/03/2023.
//

#include "arrayTree.h"

// Create an empty tree
void create(arrayTree* tree) {
    (*tree) = (arrayTree) malloc(sizeof(struct arrayNode));
    for(int i = 0; i < NUM_NODOS; ++i) {
        (*tree)->nodes[i].next = NULL;
        (*tree)->nodes[i].isEnd = 0;
        (*tree)->nodes[i].found = 0;
    }
}

// destroy the tree and free all memory
void destroy(arrayTree* tree) {
    if((*tree) != NULL) {
        for (int i = 0; i < NUM_NODOS; ++i) {
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

void longestWordAux(arrayTree tree, char letters[], char** longest_word, char** one_solution) {
    int actual_length = strlen(*one_solution);
    if(strlen(*one_solution) > strlen(*longest_word)) {
        *longest_word = realloc(*longest_word, actual_length+2);
        strcpy(*longest_word, *one_solution);
    }
    for(int i = 0; i < strlen(letters); ++i) {
        int pos = tolower(letters[i])-'a';
        if(tree != NULL && tree->nodes[pos].found == 1) {
            char* aux = malloc(actual_length+1);
            strcpy(aux, *one_solution);
            *one_solution = realloc(*one_solution,actual_length+2);
            (*one_solution)[actual_length] = letters[i];
            (*one_solution)[actual_length+1] = '\0';
            longestWordAux(tree->nodes[pos].next, letters, longest_word, one_solution);
            *one_solution = realloc(*one_solution, actual_length+1);
            strcpy(*one_solution, aux);
        }
    }
}

// Returns the longest word stored in the tree that can be formed
// by any permutation of the letters in 'letters'

char* longestWord(arrayTree tree, char letters[]) {
    if(tree == NULL || letters == NULL) return "none";
    char* res = malloc(0);
    strcpy(res, "");
    char* aux = malloc(0);
    strcpy(aux, "");
    longestWordAux(tree, letters, &res, &aux);
    return res;
}



