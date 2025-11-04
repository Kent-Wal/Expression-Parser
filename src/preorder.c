#include "header.h"

int main(int argc, char *argv[]){
    //declare beginning of tree
    struct Node *root;

    //check if there was an invalid expression entered
    if(argc > 3){
        fprintf(stderr, "Error: syntax error.\n");
        exit(-1);
    }

    //build the binary tree
    root = buildTree(argv[1]);

    //call function
    preorderTraversal(root);
    printf("\b\n");

    //free data
    freeTree(root);

    return 0;
}

void preorderTraversal(struct Node *root){
    //check if the current node exists
    if(!root){return;}

    //print the value of the current node
    printf("%s ", root->data);

    //traverse the tree
    preorderTraversal(root->left);
    preorderTraversal(root->right);

    return;
}
