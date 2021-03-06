/*
 ============================================================================
 Name        : BinaryTree.c
 Author      : moshe
 Version     : 0.1
 Created on  : Feb 5, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#include "BinarySearchTree.h"

void addNodeToTree (BinaryTree* tree, char* s)
{
	if(tree->root == NULL)
	{
		Node* n = createNode(s);
		tree->root = n;
		tree->size = 1;
	}
	else
	{
		tree->size++;
		addNodeToTreeRecursive(tree->root,s);
	}
}

Node* addNodeToTreeRecursive (Node* n, char* s)
{
	if(n == NULL)
	{
		return createNode(s);
	}

	if(strcmp(s,n->data) == 0)
	{
		n->count++;
	}
	else if(strcmp(s,n->data) > 0)
	{
		n->rightNode = addNodeToTreeRecursive(n->rightNode,s);
	}
	else
	{
		n->leftNode = addNodeToTreeRecursive(n->leftNode,s);
	}
}

Node* createNode(char* s)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
		exit(1);

	newNode->data = (char*)malloc(strlen(s) + 1);
	if(newNode->data == NULL)
		exit(1);

	strcpy(newNode->data, s);
	newNode->count = 1;

	return newNode;
}

void freeTree(Node* root)
{
	if (root != NULL)
	{
		freeTree(root->leftNode); 	// free left subtree
		freeTree(root->rightNode); 	// free right subtree
		free(root->data); 			// free pointed word
		free(root); 				// free node itself
	}
}

void printTree(Node* root)
{
	if(root == NULL)
		return;

	printTree(root->leftNode);
	printf("The number of data %s is %d\n",root->data,root->count);
	printTree(root->rightNode);
}
