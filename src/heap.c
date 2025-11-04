#include "header.h"

int main(void){
    //open .dat file
    FILE *file = fopen("src/f.dat", "r");
    if(file == NULL){
        perror("Could not open file");
        return 1;
    }

    //count the number of integers in the file
    int count = 0;
    int temp;
    while(fscanf(file, "%d", &temp) == 1){
        count++;
    }
    
    //check if the count is valid (must be divisible by 10)
    if(count % 10 != 0){
        fprintf(stderr, "File does not contain a multiple of 10 integers.\n");
        fclose(file);
        return 1;
    }
    
    int heapSize = count / 10;
    
    //rewind file to beginning for reading
    rewind(file);

    //declare variables
    struct HeapNode **heap = newHeap(heapSize);
    readFile(file, heap, heapSize);

    //function calls
    createHeapTree(heap, heapSize);
    
    //build the heap by calling downHeap on all non-leaf nodes
    //start from the last non-leaf node and work backwards to root
    for(int i = heapSize/2; i >= 0; i--){
        downHeap(heap, i, heapSize);
    }
    
    printHeap(heap, heapSize);
    freeHeap(heap, heapSize);

    fclose(file);
    return 0;
}

struct HeapNode **newHeap(int size){
    struct HeapNode **h = malloc(sizeof(struct HeapNode *) * size);
    if(h == NULL){
        perror("Memory allocation failed");
        exit(1);
    }
    for(int i = 0; i < size; i++){
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


void readFile(FILE *file, struct HeapNode **heap, int size){
    int num;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < 10; j++){
            if(fscanf(file, "%d", &num) != 1){
                fprintf(stderr, "Error reading file: insufficient integers.\n");
                freeHeap(heap, size);
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

void createHeapTree(struct HeapNode **heap, int size){
    for(int i = 0; i < size; i++){
        int leftIndex = 2 * i + 1;
        int rightIndex = 2 * i + 2;

        if(leftIndex < size){
            heap[i]->left = heap[leftIndex];
        }
        if(rightIndex < size){
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

void printHeap(struct HeapNode **heap, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < 10; j++){
            printf("%02d ", heap[i]->data[j]);
        }
        printf("\b\n");
    }
    return;
}

void freeHeap(struct HeapNode **heap, int size){
    for(int i = 0; i < size; i++){
        free(heap[i]);
    }  
    free(heap);
    return;
}

