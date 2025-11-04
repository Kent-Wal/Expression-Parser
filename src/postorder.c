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
    postorderTraversal(root);
    printf("\b\n");

    //free data
    freeTree(root);

    return 0;
}

void postorderTraversal(struct Node *root){
    //check if the current node exists
    if(!root){return;}

    //traverse the tree
    postorderTraversal(root->left);
    postorderTraversal(root->right);

    //print the node
    printf("%s ", root->data);

    return;
}
