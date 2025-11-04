# Expression-Parser

## Description
The first part of this project creates a binary tree given an arithmetic expression in the form of a string via the command line. From there depending on the file run the program displays how the tree can be traversed with either an inorder, preorder, or postorder traversal pattern.

Additionally the user can also run the calculate function and given an arithmetic expression and also a set of variable values in the form of a string via the command line to determine the result of the expression. To do this the program traverses through the tree and rebuilds the tree on its way back up and eventually ends up with the result of the expression stored at the root node.

The second part of this project uses a heap to take in some set of data by reading the given file and building a heap from the data. From there the heap is then converted into a max-heap using a percolate down algorithm. Finally the new max-heap is displayed on the screen.

&emsp;**Note:** This implementation of the heap specifies that the maximum number of data that can be in a single row in the data set is 10 for simplicity but this can be easily changed to implement any number of even to be dynamic.

## Build Instructions
First clone the git repository using "git clone" and then "cd" into the repo. From there run "make all" to compile all the source files. To run each program follow the list below:  
-Inorder: ./bin/inorder '...'  
-Preorder: ./bin/preorder '...'  
-Postorder: ./bin/postorder '...'  
-Calculate: ./bin/calculate '...' '...'  
-Heap: ./bin/heap '<'File Path'>'

**Note:**  
For the inorder, preorder and postorder file they are expecting some arithmetic expression surrounded by singe quotes and and also surrounded by a set of brackets  
&emsp;ex. '(((x1+5.88)*(x2-7.62))/x3)'

For the calculate file it is expecting some arithmetic expression with the same requirements as above and also a set of variables surrounded by single quotes in the following form
&emsp;ex. 'x1=2;x2=4.32;x3=9.3'

run "make clean" to delete the object files  
run "make cleaner" to delete the object and executable files

&emsp;**Note:** I included a sample data file that can be used for testing but any data file can be used as long as it satisfies the given parameters listed above

## What I Learned
This project really expanded my knowledge on how binary trees and heaps work and also the similarities they have with eachother.