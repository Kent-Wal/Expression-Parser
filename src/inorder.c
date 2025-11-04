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
    inorderTraversal(root);
    printf("\n");

    //free data
    freeTree(root);

    return 0;
}

void inorderTraversal(struct Node *root){
    //check if the current node exists
    if(!root){return;}

    //bascially checks if the node has children because operators cannot be leaf nodes
    bool isOperator = (root->left != NULL || root->right != NULL);

    //visit left node first then current node then right node
    if(isOperator){
        printf("(");
    }
    inorderTraversal(root->left);
    printf("%s", root->data);
    inorderTraversal(root->right);
    if(isOperator){
        printf(")");
    }

    return;
}
