# AvlTreeInsertion

In this assignment, a program has been created that will take a list of keys (integers) 
and adds them to an AVL tree in order.  The program uses rotations to ensure that the tree 
remains balanced while adding new elements.  The algorithm that is implemented is shown here:
https://www.geeksforgeeks.org/insertion-in-an-avl-tree/#

The input format for this program is a space-separated list of integers that will be placed into
the final AVL tree.  The post order, pre order, and in order traversals are then given as well
as the height of the final tree.  A sample execution is shown below.  The visual tree is shown 
to aid in the understanding of the problem but is not output by the program.  As is indicated,
the correct traversals and height are given by the algorithm.  To run the provided testcases, 
run the 'make testall' target and to run the valgrind assessment, run 'make testmemory'.  This
will generate a file containing the results (memcheck.txt).  Running 'make clean' will remove the
generated files.

./AvlTreeInsertion 1 2 3 4 5

Post Order:  1 3 5 4 2
In Order:    1 2 3 4 5
Pre Order:   2 1 4 3 5
Tree Height: 3

   2
  / \
 1   4
    / \
   3   5