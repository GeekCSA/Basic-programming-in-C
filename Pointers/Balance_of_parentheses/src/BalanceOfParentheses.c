/*
 ============================================================================
 Name        : Part_2.c
 Author      : Moshe
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Stack.h"

bool isStringBalanced(char** sentence, int size)
{
	char* s = *sentence;
	int countOfparentheses = 0;

	Node* stack = NULL;

	for(int i = 0; i < size; i++)
	{
		printf("%c",s[i]);

		if((s[i] == '(')||(s[i] == '[')||(s[i] == '{'))
		{
			countOfparentheses++;
			if(stack == NULL)
				stack = createNewNode(s[i]);
			else
			{
				push(stack, s[i]);
			}

		}
		if((s[i] == ')'))
		{
			char parentheses = pop(&stack);
			if(parentheses != '(')
				return false;
			countOfparentheses--;
		}
		if((s[i] == ']'))
		{
			char parentheses = pop(&stack);
			if(parentheses != '[')
				return false;
			countOfparentheses--;
		}
		if((s[i] == '}'))
		{
			char parentheses = pop(&stack);
			if(parentheses != '{')
				return false;
			countOfparentheses--;
		}
	}

	if(countOfparentheses != 0)
		return false;

	printf("\n%d",countOfparentheses);

	return true;
}


int main(void) {

	char* s = "if (x[i] > x[j]) { return;}";
	int sLen = strlen(s);

	if(isStringBalanced(&s,sLen))
	{
		puts("\nThe parentheses are matched");
	}
	else
	{
		puts("\nThe parentheses are not matched");
	}

	return 0;
}
