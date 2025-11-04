#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//constants
#define MAX_VAR 10

//create node struct for tree;
struct Node{
    char *data;
    struct Node *left;
    struct Node *right;
};

//heap struct
struct HeapNode{
    int key;
    int data[10];
    struct HeapNode *left;
    struct HeapNode *right;
};

//hasmap for calculate.c
typedef struct{         //decleration for each item in the table
    char *key;
    double value;
}Entry;

typedef struct{             //decleration for the table as a whole
    Entry *table[MAX_VAR];
}HashMap;

//part a functions
int hashFunction(char *key);
HashMap* createMap(void);
void add(HashMap *map, char *key, double value);
double get(HashMap *map, char *key);
bool contains(HashMap *map, char *key);
void freeMap(HashMap *map);
struct Node* buildTree(char *str);
void freeTree(struct Node *root);
bool checkOperand(char *o);
bool checkOperator(char *o);
void preorderTraversal(struct Node *root);
void postorderTraversal(struct Node *root);
void inorderTraversal(struct Node *root);
void calculate(struct Node *root,  char *variables);
void calculateTree(struct Node *root, HashMap *map);

//heap functions
struct HeapNode **newHeap(int size);
void readFile(FILE *file, struct HeapNode **heap, int size);
void createHeapTree(struct HeapNode **heap, int size);
void downHeap(struct HeapNode **heap, int nodeIndex, int size);
void printHeap(struct HeapNode **heap, int size);
void freeHeap(struct HeapNode **heap, int size);

#endif
