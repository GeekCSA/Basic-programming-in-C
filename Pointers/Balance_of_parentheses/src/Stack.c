/*
 * Stack.c
 *
 *  Created on: Jan 5, 2018
 *      Author: moshe
 */

#include "Stack.h"

Node* createNewNode(char data)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->nextNode = NULL;

	return newNode;
}

int push(Node* head, char data)
{
	if((head == NULL))
		return 0;
	else
	{
		Node* newNode = createNewNode(data);
		Node* temp = head;

		while(temp->nextNode != NULL)
		{
			temp = temp->nextNode;
		}

		temp->nextNode = newNode;

		return 1;
	}
}

char pop(Node** head)
{
	Node* temp = *head;

	if(temp == NULL)
		return '\0';
	if(temp->nextNode == NULL)
		return temp->data;
	else
	{
		while(temp->nextNode->nextNode != NULL)
		{
			temp = temp->nextNode;
		}
		char charReturn = temp->nextNode->data;
		temp->nextNode = NULL;

		return charReturn;
	}
}

void printStack(Node* head)
{
	Node* temp = head;

	if(temp == NULL)
		printf("isEmpty");
	else
	{
		while(temp != NULL)
		{
			printf("%c",temp->data);
			temp = temp->nextNode;
		}
	}
}
