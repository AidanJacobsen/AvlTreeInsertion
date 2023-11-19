#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char* argv[]) {

    if(argc == 1)
    {
        printf("You must add at least one node.");
        return 1;
    }

    int nodeValue = atoi(argv[1]);
    if (nodeValue == 0 && argv[1][0] != '0') {
        printf("Argument error\n");
        return 1;
    }
    
    Tree tree;
    tree.root = createNode(nodeValue);

    for (int i = 2; i < argc; ++i) {
        nodeValue = atoi(argv[i]);

        if (nodeValue == 0 && argv[i][0] != '0') {
            printf("Argument error\n");
            deleteTree(tree.root);
            return 1;
        }
        treeInsert(nodeValue, &tree);
    }
    printf("Post Order: ");
    printPostOrder(tree.root);
    printf("\n");

    printf("In Order:   ");
    printInOrder(tree.root);
    printf("\n");

    printf("Pre Order:  ");
    printPreOrder(tree.root);
    printf("\n");
    printf("Tree Height: %d\n", tree.root->height);
    deleteTree(tree.root);
    return 0;
}