#include "header.h"

int hashFunction(char *key){
    int index = 0;
    int len = strlen(key);

    //add the ASCII value of every character
    for(int i = 0; i < len; i++){
        index += key[i];
    }
    return index % MAX_VAR;
}


HashMap* createMap(void){           //initialize the hashmap
    HashMap *map = malloc(sizeof(HashMap));
    if(map == NULL){
        perror("Memory could not be allocated\n");
        exit(-2);
    }

    for(int i = 0; i < MAX_VAR; i++){       //set each element in the table to NULL
        map->table[i] = NULL;
    }
    return map;
}

void add(HashMap *map, char *key, double value){
    int index = hashFunction(key);

    Entry *newEntry = malloc(sizeof(Entry));
    if(newEntry == NULL){
        perror("Memory could not be allocated\n");
        exit(-2);
    }
    
    newEntry->key = malloc(strlen(key) + 1);
    if(newEntry->key == NULL){
        perror("Memory could not be allocated\n");
        free(newEntry);
        exit(-2);
    }

    strcpy(newEntry->key, key);
    newEntry->value = value;
    map->table[index] = newEntry; 
}

double get(HashMap *map, char *key){
    int index = hashFunction(key);

    //check to make sure the key is in the hashtable
    if(map->table[index] != NULL && strcmp(map->table[index]->key, key) == 0){
        return map->table[index]->value;
    }

    //exit if the key is not in the table
    fprintf(stderr, "Error: undefined argument.\n");
    exit(-1);          
}

bool contains(HashMap *map, char *key){
    int index = hashFunction(key);
    Entry *current = map->table[index];

    if(current != NULL && strcmp(current->key, key) == 0){
        return true;
    }

    return false;
}

void freeMap(HashMap *map){
    for(int i = 0; i < MAX_VAR; i++){
        Entry *current = map->table[i];
        if(current){
            free(current->key);     //used a malloc to declare the key
            free(current);
        }
    }
    free(map);
}





struct Node* buildTree(char *str){
    //declare tree
    struct Node *root = malloc(sizeof(struct Node));
    if(root == NULL){
        perror("Memory could not be allocated\n");
        exit(-2);
    }
    
    //check for balanced parentheses first
    int parenBalance = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '(') parenBalance++;
        else if(str[i] == ')') parenBalance--;
        if(parenBalance < 0){  //closing before opening
            fprintf(stderr, "Error: syntax error.\n");
            free(root);
            exit(-1);
        }
    }
    if(parenBalance != 0){  //missing a closing bracket
        fprintf(stderr, "Error: syntax error.\n");
        free(root);
        exit(-1);
    }
    
    //the expression is empty and its just a variable or value also the recursive base case
    if(str[0] != '('){
        root->data = malloc(strlen(str) + 1);
        if(root->data == NULL){
            perror("Memory could not be allocated\n");
            free(root);
            exit(-2);
        }

        strcpy(root->data, str);
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    
    //skip the first bracket
    str++;
    
    int bracketCount = 0;   //counts the number of internal brackets
    int leftStart = 0;      //left must start at the first index in the string
    int leftEnd = 0;
    int operatorPos = -1;   //could be no operator in string
    
    //find where left operand ends
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '('){
            bracketCount++;
        }
        else if(str[i] == ')'){
            bracketCount--;
        }
        // If we're at depth 0 and find an operator
        else if(bracketCount == 0 && (str[i] == '+' || str[i] == '-' || 
                                     str[i] == '*' || str[i] == '/')){
            leftEnd = i - 1;
            
            operatorPos = i;
            break;
        }
    }

    //check if no operator was found
    if(operatorPos == -1){
        fprintf(stderr, "Error: syntax error.\n");
        free(root);
        exit(-1);
    }
    
    //left operand
    int leftLen = leftEnd - leftStart + 1;
    char *leftOperand = malloc(sizeof(char) * (leftLen + 1));
    if(leftOperand == NULL){
        perror("Memory could not be allocated\n");
        free(root);
        exit(-2);
    }

    strncpy(leftOperand, str + leftStart, leftLen);             //copy the substring of the left operand
    leftOperand[leftLen] = '\0';                                //add the null terminator
    
    //check if the operand is valid
    if(!checkOperand(leftOperand)){
        fprintf(stderr, "Error: syntax error.\n");
        free(root);
        free(leftOperand);
        exit(-1);
    }

    //operator
    root->data = malloc(sizeof(char) * 2);
    if(root->data == NULL){
        perror("Memory could not be allocated\n");
        free(leftOperand);
        free(root);
        exit(-2);
    }
    root->data[0] = str[operatorPos];
    root->data[1] = '\0';
    
    //check if operator is valid
    if(!checkOperator(root->data)){
        fprintf(stderr, "Error: syntax error.\n");
        free(root->data);
        free(root);
        free(leftOperand);
        exit(-1);
    }

    //right operand
    int rightStart = operatorPos + 1;   //starts at the position after the operator
    int rightEnd = strlen(str) - 2;     // len-1 is '\0', len-2 is the last ')'
    int rightLen = rightEnd - rightStart + 1;
    char *rightOperand = malloc(sizeof(char) * (rightLen + 1));
    if(rightOperand == NULL){
        perror("Memory could not be allocated\n");
        free(leftOperand);
        free(root);
        free(root->data);
        exit(-2);
    }

    strncpy(rightOperand, str + rightStart, rightLen);
    rightOperand[rightLen] = '\0';                      //add the null terminator
    
    //check if the operand is valid
    if(!checkOperand(rightOperand)){
        fprintf(stderr, "Error: syntax error.\n");
        free(root->data);
        free(root);
        free(leftOperand);
        free(rightOperand);
        exit(-1);
    }

    //iterate through subtrees recursively
    root->left = buildTree(leftOperand);
    root->right = buildTree(rightOperand);
    
    //free temporary strings
    free(leftOperand);
    free(rightOperand);
    
    return root;
}

//need some function to free the tree
void freeTree(struct Node *root){
    if(root == NULL) return;
    
    //free left and right subtrees
    freeTree(root->left);
    freeTree(root->right);
    
    //free the data string and the node
    free(root->data);
    free(root);
}

bool checkOperator(char *o){
    if(o[0] == '+' || o[0] == '-' || o[0] == '*' || o[0] == '/'){
        return true;
    }
    else{
        return false;
    }
}

bool checkOperand(char *o){
    // Check if empty
    if(o == NULL || strlen(o) == 0){
        return false;
    }
    
    //we only need to validate the leaf nodes technically so we just return true because an expression still exists
    if(o[0] == '('){
        return true;
    }
    
    //check for valid number
    bool isNumber = true;
    bool hasDecimal = false;
    bool hasDigit = false;
    
    for(int i = 0; i < strlen(o); i++){
        if(o[i] >= '0' && o[i] <= '9'){
            hasDigit = true;
        }
        else if(o[i] == '.'){
            if(hasDecimal){
                //multiple decimal points
                isNumber = false;
                break;
            }
            hasDecimal = true;
        }
        else{
            //contains somrhitn other than a number or decimal point
            isNumber = false;
            break;
        }
    }
    
    //if a valid number
    if(isNumber && hasDigit){
        return true;
    }
    
    //check for valid variable
    if((o[0] >= 'a' && o[0] <= 'z') || (o[0] >= 'A' && o[0] <= 'Z')){
        for(int i = 1; i < strlen(o); i++){
            if(!((o[i] >= 'a' && o[i] <= 'z') || (o[i] >= 'A' && o[i] <= 'Z') || 
                 (o[i] >= '0' && o[i] <= '9'))){
                return false;  // ivalid character in variable name
            }
        }
        return true; 
    }
    
    return false;   //neither a valid number nor a valid variable name
}
