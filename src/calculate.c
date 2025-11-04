#include  "header.h"

int main(int argc, char *argv[]){
    //declare variables
    struct Node *root;
    
    //check format of CLI input
    if(argc < 2 || argc > 3){
        fprintf(stderr, "Error: syntax error.\n");
        exit(-1);
    }
    
    //get expression from CLI
    char *expression = malloc(sizeof(char) * (strlen(argv[1]) + 1));
    if(expression == NULL){
        perror("Memory could not be allocated\n");
        exit(-2);
    }
    strcpy(expression, argv[1]);
    
    //get variables from CLI
    char *variables;
    if(argc == 3){
        variables = malloc(sizeof(char) * (strlen(argv[2]) + 1));
        if(variables == NULL){
            perror("Memory could not be allocated\n");
            free(expression);
            exit(-2);
        }
        strcpy(variables, argv[2]);
    }
    else{
        variables = malloc(sizeof(char) * 1);
        if(variables == NULL){
            perror("Memory could not be allocated\n");
            free(expression);
            exit(-2);
        }
        strcpy(variables, "");
    }

    //build the binary tree
    root = buildTree(expression);

    //call the calculate function
    calculate(root, variables);

    //free the data since we are now done with the tree
    freeTree(root);
    free(expression);
    free(variables);
    
    return 0;
}

void calculate(struct Node *root, char *variables){
    HashMap *map = createMap();             //use a hasmap to store the variables and their corresponding values

    //check if variable declarations have been passed
    if(strcmp(variables, "") != 0){             //checks to see if variables have been passed
        char *tokens[strlen(variables)];
        int counter = 0;
        
        char *token = strtok(variables, "=;");
        while(token != NULL){
            //store the last iterations token in the tokens array
            tokens[counter] = token;
            token = strtok(NULL, "=;");
            counter++;
        }

        //add each variable and its value to the hashmap
        for(int i = 0; i < counter; i += 2){
            add(map, tokens[i], atof(tokens[i + 1]));
        }
    }
    //assume the tree is already created
    calculateTree(root, map);
    
    double result = atof(root->data);

    //print the total
    printf("%4.2f\n", result);
    
    freeMap(map);
}

void calculateTree(struct Node *root, HashMap *map){            //the solution to the tree is stored in the root of the tree once function has completed
    //check if the current node exists
    if(!root){return;}
    struct Node *leftNode = root->left;
    struct Node *rightNode = root->right; 
    double operand[2];
    char operator;

    if(leftNode->left == NULL && leftNode->right == NULL){
        //check if the leaf node is in the hasmap
        if(contains(map, leftNode->data)){
            operand[0] = get(map, leftNode->data);
        }
        else{
            //check for valid number
            char *endptr;
            operand[0] = strtod(leftNode->data, &endptr);
            if(*endptr != '\0' && *endptr != '\n'){
                // Not a valid number and not in map
                fprintf(stderr, "Error: undefined argument.\n");
                exit(-1);
            }
        }
    }
    //if its not a leaf node travese the tree
    else{
        calculateTree(leftNode, map);
        operand[0] = atof(leftNode->data);          //set the operand after returning and updating the tree
    }

    if(rightNode->left == NULL && rightNode->right == NULL){
        //check if the leaf node is in the hasmap
        if(contains(map, rightNode->data)){
            operand[1] = get(map, rightNode->data);
        }
        else{
            //chek for valid number
            char *endptr;
            operand[1] = strtod(rightNode->data, &endptr);
            if(*endptr != '\0' && *endptr != '\n'){
                // Not a valid number and not in map
                fprintf(stderr, "Error: undefined argument.\n");
                exit(-1);
            }
        }
    }
    //if its not a leaf node traverse the tree
    else{
        calculateTree(rightNode, map);
        operand[1] = atof(rightNode->data);
    }

    //root cannot be a leaf node which must mean it is some kind of operator
    operator = root->data[0];        //had the operator removed before
    
    //update the tree
    leftNode = NULL;
    rightNode = NULL;
    double total = 0;
    char totalStr[32];
    
    switch(operator){
        case '+':
            total = operand[0] + operand[1];
            break;
        case '-':
            total = operand[0] - operand[1];
            break;
        case '*':
            total = operand[0] * operand[1];
            break;
        case '/':
            if(operand[1] == 0){
                fprintf(stderr, "Error: division by zero.\n");
                freeMap(map);
                freeTree(root);
                exit(-1);
            }

            total = operand[0] / operand[1];
            break;
    }
    //convert to string
    sprintf(totalStr, "%.2f", total);


    root->data = realloc(root->data, sizeof(char) * (strlen(totalStr) + 1));
    if(root->data == NULL){
        perror("Could not allocate memory\n");
        exit(-2);
    }

    strcpy(root->data, totalStr);

    return;
}
