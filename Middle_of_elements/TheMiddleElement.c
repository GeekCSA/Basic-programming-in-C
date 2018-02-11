/*
 ============================================================================
 Name        : TheMiddleElement.c
 Author      : Moshe
 Version     : 0.1
 Created on  : Jan 2, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int numberOfNodes = 0;
Node* middle = NULL;
Node* head;

int take(int num){

	numberOfNodes++;

	if(head == NULL)
		head = createNewNode(num);
	else
	{
		Node* newNode = createNewNode(num);
		addNodeToTheListTail(head,newNode);
	}

	if(middle == NULL)
		middle = head;

	if(numberOfNodes % 2 == 0)
		middle = middle->nextNode;

	return middle->data;
}

int main(void) {

	//Test
	printf("%d\n",take(20));
	printList(head);

	printf("%d\n",take(10));
	printList(head);

	printf("%d\n",take(30));
	printList(head);

	printf("%d\n",take(5));
	printList(head);

	printf("%d\n",take(40));
	printList(head);

	return 0;
}
