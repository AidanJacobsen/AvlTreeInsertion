#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node* createNode(int value)
{
    Node* node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->height = 1;
    return node;
}

void treeInsert(int value, Tree * tree)
{
    tree->root = insert(value, tree->root);

    int leftHeight = (tree->root->left == NULL)?0:tree->root->left->height;
    int rightHeight= (tree->root->right == NULL)?0:tree->root->right->height;

    if(leftHeight > rightHeight)
    {
        tree->root->height = leftHeight + 1;
    }
    else
    {
        tree->root->height = rightHeight + 1;
    }
    Node* node = tree->root;
    int balance;
    if(node->left == NULL && node->right == NULL)
    {
        balance = 0;
    }
    else if(node->left == NULL)
    {
        balance = -node->right->height;
    }
    else if(node->right == NULL)
    {
        balance = node->left->height;
    }
    else
    {
        balance = node->left->height - node->right->height;
    }
    //printf("Balance: %d\n", balance);


    //Left side too big and child big on left side
    if(balance > 1 && value < node->left->value)
    {
        tree->root = rightRotate(node);
        return;
    }

    //Left side too big and child big on right side
    if(balance > 1 && value > node->left->value)
    {
        node->left = leftRotate(node->left);
        tree->root = rightRotate(node);
        return;
    }

    //right side too big and child big on left side
    if(balance < -1 && value < node->right->value)
    {
        node->right = rightRotate(node->right);
        tree->root = leftRotate(node);
        return;
    }
    //right side too big and child big on right side
    if(balance < -1 && value > node->right->value)
    {
        tree->root = leftRotate(node);
        return;
    }

}

Node* insert(int value, Node* node)
{
    if(value == node->value) return node;
    if(value < node->value)
    {
        if(node->left == NULL)
        {
            node->left = createNode(value);
            if(node->height < node->left->height + 1) node->height = node->left->height + 1;
        }
        else
        {
            node->left = insert(value, node->left);
            if(node->left->height + 1 > node->height)
            {
                node->height = node->left->height + 1;
            }
        }
    }
    if(value > node->value)
    {
        if(node->right == NULL)
        {
            node->right = createNode(value);
            if(node->height < node->right->height + 1) node->height = node->right->height + 1;
        }
        else
        {
            node->right = insert(value, node->right);
            if(node->right->height + 1 > node->height)
            {
                node->height = node->right->height + 1;
            }
        }
    }
    int balance;
    if(node->left == NULL && node->right == NULL)
    {
        balance = 0;
    }
    else if(node->left == NULL)
    {
        balance = -node->right->height;
    }
    else if(node->right == NULL)
    {
        balance = node->left->height;
    }
    else
    {
        balance = node->left->height - node->right->height;
    }

    //Left side too big and child big on left side
    if(balance > 1 && value < node->left->value)
    {
        return rightRotate(node);
    }

    //Left side too big and child big on right side
    if(balance > 1 && value > node->left->value)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //right side too big and child big on left side
    if(balance < -1 && value < node->right->value)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    //right side too big and child big on right side
    if(balance < -1 && value > node->right->value)
    {
        return leftRotate(node);
    }

    return node;
}

void printPreOrder(Node* node)
{
    printf(" %d", node->value);
    if(node->left != NULL) printPreOrder(node->left);
    if(node->right != NULL) printPreOrder(node->right);
}
void printInOrder(Node* node)
{
    if(node->left != NULL) printInOrder(node->left);
    printf(" %d", node->value);
    if(node->right != NULL) printInOrder(node->right);
}
void printPostOrder(Node* node)
{
    if(node->left != NULL) printPostOrder(node->left);
    if(node->right != NULL) printPostOrder(node->right);
    printf(" %d", node->value);
}

Node* leftRotate(Node* node)
{
    Node* newRoot = node->right;
    node->right = node->right->left;
    newRoot->left = node;

    //Update child node height
    if(newRoot->left->left == NULL && newRoot->left->right == NULL) newRoot->left->height = 1;
    else if(newRoot->left->left == NULL) newRoot->left->height = newRoot->left->right->height + 1;
    else if(newRoot->left->right == NULL) newRoot->left->height = newRoot->left->left->height + 1;
    else newRoot->left->height = (newRoot->left->left->height > newRoot->left->right->height)? newRoot->left->left->height + 1 : newRoot->left->right->height + 1;
    
    //Update node height
    if(newRoot->left == NULL && newRoot->right == NULL) newRoot->height = 1;
    else if(newRoot->left == NULL) newRoot->height = newRoot->right->height + 1;
    else if(newRoot->right == NULL) newRoot->height = newRoot->left->height + 1;
    else newRoot->height = (newRoot->left->height > newRoot->right->height)? newRoot->left->height + 1 : newRoot->right->height + 1;

    return newRoot;
}

Node* rightRotate(Node* node)
{
    Node* newRoot = node->left;
    node->left = node->left->right;
    newRoot->right = node;

    //Update child node height
    if(newRoot->right->left == NULL && newRoot->right->right == NULL) newRoot->right->height = 1;
    else if(newRoot->right->left == NULL) newRoot->right->height = newRoot->right->right->height + 1;
    else if(newRoot->right->right == NULL) newRoot->right->height = newRoot->right->left->height + 1;
    else newRoot->right->height = (newRoot->right->left->height > newRoot->right->right->height)? newRoot->right->left->height + 1 : newRoot->right->right->height + 1;
    
    //Update node height
    if(newRoot->left == NULL && newRoot->right == NULL) newRoot->height = 1;
    else if(newRoot->left == NULL) newRoot->height = newRoot->right->height + 1;
    else if(newRoot->right == NULL) newRoot->height = newRoot->left->height + 1;
    else newRoot->height = (newRoot->left->height > newRoot->right->height)? newRoot->left->height + 1 : newRoot->right->height + 1;

    return newRoot;
}

void deleteTree(Node * node)
{
    if(node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}