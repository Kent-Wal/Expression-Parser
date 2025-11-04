#include "header.h"

int main(void){
    //open .dat file
    FILE *file = fopen("src/f.dat", "r");
    if(file == NULL){
        perror("Could not open file");
        return 1;
    }

    //declare variables
    struct HeapNode **heap = newHeap();
    readFile(file, heap);

    //function calls
    createHeapTree(heap);
    
    //build the heap by calling downHeap on all non-leaf nodes
    //start from the last non-leaf node and work backwards to root
    for(int i = 19/2; i >= 0; i--){
        downHeap(heap, i, 20);
    }
    
    printHeap(heap);
    freeHeap(heap);

    fclose(file);
    return 0;
}

struct HeapNode **newHeap(void){
    struct HeapNode **h = malloc(sizeof(struct HeapNode *) * 20);
    if(h == NULL){
        perror("Memory allocation failed");
        exit(1);
    }
    for(int i = 0; i < 20; i++){
        //allocate memroy for each node
        h[i] = malloc(sizeof(struct HeapNode));
        if(h[i] == NULL){
            perror("Couldnt allocate memory\n");
            exit(-1);
        }

        h[i]->key = 0;
        h[i]->left = NULL;
        h[i]->right = NULL;
        for(int j = 0; j < 10; j++){
            h[i]->data[j] = 0;
        }
    }
    return h;
}


void readFile(FILE *file, struct HeapNode **heap){
    int num;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            if(fscanf(file, "%d", &num) != 1){
                fprintf(stderr, "does not contain 200 2-digit integers.\n");
                freeHeap(heap);
                exit(-2);
            }

            //find the key
            if(j < 3){
                heap[i]->key += num;
            }
            //store the values
            heap[i]->data[j] = num;
        }
    }
    return;
} 

void createHeapTree(struct HeapNode **heap){
    for(int i = 0; i < 20; i++){
        int leftIndex = 2 * i + 1;
        int rightIndex = 2 * i + 2;

        if(leftIndex < 20){
            heap[i]->left = heap[leftIndex];
        }
        if(rightIndex < 20){
            heap[i]->right = heap[rightIndex];
        }
    }
    return;
}

void downHeap(struct HeapNode **heap, int nodeIndex, int size){
    //keep track of the largest key in the heap
    int childIndex = 2 * nodeIndex + 1;

    while(childIndex < size){
        //find the max among the nodes
        struct HeapNode *value = heap[nodeIndex];
        struct HeapNode *max = value;
        int maxIndex =  -1;

        //check both children to see if they are larger than the current node
        for(int i = 0; i < 2 && i + childIndex < size; i++){
            if(heap[i + childIndex]->key > max->key){
                max = heap[i + childIndex];
                maxIndex = i + childIndex;
            }
        }

        //if this is true both children are smaller than the current node so the heap propety holds and nothing needs to be moved
        if(max->key == value->key){
            return;
        }
        //if one child is larger then swap with the larger child
        else{
            struct HeapNode *temp = heap[nodeIndex];
            heap[nodeIndex] = heap[maxIndex];
            heap[maxIndex] = temp;

            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex + 1;
        }
    }
    return;
}

void printHeap(struct HeapNode **heap){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            printf("%02d ", heap[i]->data[j]);
        }
        printf("\b\n");
    }
    return;
}

void freeHeap(struct HeapNode **heap){
    for(int i = 0; i < 20; i++){
        free(heap[i]);
    }  
    free(heap);
    return;
}

