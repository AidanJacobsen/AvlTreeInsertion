#ifndef TREE_H
#define TREE_H

// Define the node structure with typedef
typedef struct Node {
    int value;
    int height;
    struct Node* left;   // Pointer to the left child node
    struct Node* right;  // Pointer to the right child node
} Node;

// Define the tree structure with typedef
typedef struct Tree {
    Node* root;  // Pointer to the root node of the tree
} Tree;

Node* createNode(int value);
Node* insert(int value, Node* node);
void printPreOrder(Node* node);
void printInOrder(Node* node);
void printPostOrder(Node* node);
Node* leftRotate(Node* node);
Node* rightRotate(Node* node);
void treeInsert(int value, Tree * tree);
void deleteTree(Node * node);

#endif // TREE_H