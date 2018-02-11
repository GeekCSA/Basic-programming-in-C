/*
 ============================================================================
 Name        : List.c
 Author      : Moshe
 Version     : 0.1
 Created on  : Jan 2, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#include "List.h"

Node* createNewNode(int data)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->nextNode = NULL;

	return newNode;
}

Node* addNodeToTheList(Node* head, Node* newNode)
{
	if (head != NULL) {
		newNode->nextNode = head;
		return newNode;
	}

	return NULL;
}

int addNodeToTheListTail(Node* head, Node* newNode)
{
	if (head != NULL) {
		Node* temp = head;
		while(temp->nextNode != NULL)
			temp = temp->nextNode;

		temp->nextNode = newNode;

		return 1;
	}

	return 0;
}

int deleteTail(Node* head)
{
	if((head == NULL) || (head->nextNode == NULL))
	{
		return 0;
	}

	Node* temp = head;

	while(temp->nextNode->nextNode != NULL)
	{
		temp = temp->nextNode;
	}

	temp->nextNode = NULL;

	return 1;
}

void printList(Node* head)
{
	Node* temp = head;

	printf("->");
	while(temp != NULL)
	{
		printf(" (DATA: %d, NEXT: %d) ->",temp->data,temp->nextNode);
		temp = temp->nextNode;
	}
	printf("\n");
}
