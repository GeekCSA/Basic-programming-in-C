/*
 * BinaryTree.h
 *
 *  Created on: Feb 5, 2018
 *      Author: moshe
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



void addNodeToTree (BinaryTree* tree, char* s);

Node* addNodeToTreeRecursive (Node* n, char* s);

Node* createNode(char* s);

void freeTree(Node* root);

void printTree(Node* root);

#endif /* BINARYSEARCHTREE_H_ */
