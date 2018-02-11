/*
 ============================================================================
 Name        : BinaryTree.h
 Author      : moshe
 Version     : 0.1
 Created on	 : Feb 5, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
	struct Node* leftNode;
	struct Node* rightNode;
	char* data;
	int count;

}Node;

typedef struct BinaryTree
{
	Node* root;
	int size;

}BinaryTree;

/**
 * This function adds a new string to the tree.
 *
 * The function gets pointer to the tree and a pointer to char.
 */
void addNodeToTree (BinaryTree* tree, char* s);

/**
 * This function adds a new string to the tree.
 *
 * The function gets pointer to the root of a tree and a pointer to char.
 *
 * The function returns a pointer to the root node.
 */
Node* addNodeToTreeRecursive (Node* n, char* s);

/**
 * This function creates new node with data of the pointer that given to the function.
 *
 * The function returns a pointer to the new node.
 */
Node* createNode(char* s);

/**
 * This function frees the memory of all nodes in the tree.
 *
 * The function gets a pointer to the root of the tree.
 */
void freeTree(Node* root);

/**
 * This function passes on each node in the tree and prints its information.
 *
 * The function gets a pinter to the root of the tree.
 */
void printTree(Node* root);

#endif /* BINARYSEARCHTREE_H_ */
