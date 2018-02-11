/*
 ============================================================================
 Name        : Part_2.c
 Author      : Moshe
 Version     : 0.1
 Created on  : Jan 5, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Stack.h"

Node* stack = NULL;

bool isStringBalanced(char** sentence, int size)
{
	int countOfparentheses = 0;

	for(int j = 0; j < size; j++)
	{
		char* s = sentence[j];
		int sLen = strlen(s);
		for (int i = 0; i < sLen; ++i) {

			printf("%c",s[i]);

			//Check if the character is open parentheses
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
			//Check if the character is close parentheses
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
	}

	if(countOfparentheses != 0)
		return false;

	printf("\n%d",countOfparentheses);

	return true;
}


int main(void) {

	char* s[4] = {{"if "},{"(x[i] > "},{" x[j]) {"},{" return;}"}};

	if(isStringBalanced(s,4))
	{
		puts("\nThe parentheses are matched");
	}
	else
	{
		puts("\nThe parentheses are not matched");
	}

	return 0;
}
