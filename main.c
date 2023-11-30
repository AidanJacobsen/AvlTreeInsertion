#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(int argc, char* argv[]) {

    if(argc != 2)
    {
        printf("Incorrect number of arguments.\n");
        return 1;
    }

    const char* filename = argv[1];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 0;
    }

    //Read the characters in the file in order looking for newlines
    int lineCount = 0;
    for (char c = getc(file); c != EOF; c = getc(file))
    {
        if (c == '\n')
        {
            lineCount = lineCount + 1;
        }
    }
    //Reset to start of file
    fseek(file, 0, SEEK_SET);

    int nodeValue;
    if(fscanf(file, "%d", &nodeValue) != 1)
    {
        printf("File Invalid\n");
        return 0;
    }

    // int nodeValue = atoi(argv[1]);
    // if (nodeValue == 0 && argv[1][0] != '0') {
    //     printf("Argument error\n");
    //     return 1;
    // }
    
    Tree tree;
    tree.root = createNode(nodeValue);

    for (int i = 2; i <= lineCount; ++i) {
        if(fscanf(file, "%d", &nodeValue) != 1)
        {
            printf("File Invalid\n");
            
            deleteTree(tree.root);
            return 0;
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
    fclose(file);
    return 0;
}