/*
 ============================================================================
 Name        : Stack.h
 Author      : Moshe
 Version     : 0.1
 Created on  : Jan 5, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	struct Node* nextNode;
	char data;
}Node;

/**
 * The function gets data (char).
 * The function returns pointer to node that contains the data.
 */
Node* createNewNode(char data);

/**
 * The function gets a stack and new data.
 * The function	add the new data to the stack and returns it.
 * If the addition success returned the 1, else 0
 */
int push(Node* head, char data);


/**
 * The function gets a pointer to stack.
 * The function	delete the head of the stack.
 * The function returns the char of the head, if the stack is empty then the function returns NULL.
 */
char pop(Node** head);

/**
 * The function gets a stack and print all nodes in the list
 */
void printStack(Node* head);

#endif /* STACK_H_ */
