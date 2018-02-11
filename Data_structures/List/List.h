/*
 ============================================================================
 Name        : List.h
 Author      : Moshe
 Version     : 0.1
 Created on  : Jan 2, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	struct Node* nextNode;
	int data;
}Node;

/**
 * The function gets data (integer).
 * The function returns pointer to node that contains the data.
 */
Node* createNewNode(int data);

/**
 * The function gets the first node of the list and new node.
 * The function	add the new node to the head of the list and returns it.
 * If the addition success returned the new head, else returned NULL
 */
Node* addNodeToTheList(Node* head, Node* newNode);

/**
 * The function gets the first node of the list and new node.
 * The function	add the new node to the tail of the list.
 * If the addition success returned 1, else 0
 */
int addNodeToTheListTail(Node* head, Node* newNode);

/**
 * The function gets the first node of the list.
 * The function	delete the tail of the list.
 * If has only head then returned 0, else returned 1.
 */
int deleteTail(Node* head);

/**
 * The function gets the head of list and print all nodes in the list
 */
void printList(Node* head);

#endif /* LIST_H_ */
