/*
 ============================================================================
 Name        : SearchWordInMatrix.c
 Author      : Moshe
 Version     : 0.1
 Created on  : Nov 28, 2017
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include "searchWord.h";

#define MATRIX_SIZE 4 // Number of columns and rows of matrix

bool isWord(char* s){

		return (!strcmp(s,"CAT") |
			!strcmp(s,"CATS") |
			!strcmp(s,"TRAM") |
			!strcmp(s,"TRAMS") |
			!strcmp(s,"TAME") |
			!strcmp(s,"CAR") |
			!strcmp(s,"CARS") |
			!strcmp(s,"RAT") |
			!strcmp(s,"RATS") |
			!strcmp(s,"RAMP") |
			!strcmp(s,"ART") |
			!strcmp(s,"CART") |
			!strcmp(s,"STAMP") |
			!strcmp(s,"TAKEN") |
			!strcmp(s,"MEN") |
			!strcmp(s,"MAKE") |
			!strcmp(s,"TAKE") |
			!strcmp(s,"ATE") |
			!strcmp(s,"SELL") |
			!strcmp(s,"STEEL") |
			!strcmp(s,"RAKE") );
}

void printArr(int a[MATRIX_SIZE][MATRIX_SIZE])
{
	printf("\n");
	for(int i = 0; i < MATRIX_SIZE; i++)
	{
		for(int j = 0; j < MATRIX_SIZE; j++)
		{
			printf("%d",a[i][j]);
		}
		printf("\n");
	}
	//printf("\n");
}

int recorcivePrintWords(char A[MATRIX_SIZE][MATRIX_SIZE],int steps[MATRIX_SIZE][MATRIX_SIZE],int i, int j,char word1[])
{

	int numberOfWords = 0;
	int k;
	steps[i][j] = 1;

	char temp[strlen(word1) + 2];

	for(k = 0; k < strlen(word1); k++)
	{
		temp[k] = word1[k];
		//printf("%c",temp[k]);
	}
	temp[k] = A[i][j];
	k++;
	temp[k] = '\0';

	//printf("%s",temp);
	//TODO add to word1 the current.

	if(isWord(temp))
	{
		printf("\n");
		puts(temp);
		numberOfWords++;
	}

	if((i + 1 < MATRIX_SIZE) && (steps[i + 1][j] == 0 ))
	{
		//printf("%d",steps[i + 1][j]);
		//printArr(steps);
		numberOfWords += recorcivePrintWords(A,steps,i + 1,j,temp);
		steps[i+1][j] = 0;
	}

	if((j + 1 < MATRIX_SIZE) && (steps[i][j + 1] == 0 ))
	{
		//printf("%d",steps[i][j + 1]);
		//printArr(steps);
		numberOfWords += recorcivePrintWords(A,steps,i,j + 1,temp);
		steps[i][j+1] = 0;
	}

	if((i - 1 >= 0)  && (steps[i - 1][j] == 0 ))
	{
		//printf("%d",steps[i - 1][j]);
		//printArr(steps);
		numberOfWords += recorcivePrintWords(A,steps,i - 1,j,temp);
		steps[i-1][j] = 0;
	}

	if((j - 1 >= 0) && (steps[i][j - 1] == 0 ))
	{
		//printf("%d",steps[i][j - 1]);
		//printArr(steps);
		numberOfWords += recorcivePrintWords(A,steps,i,j - 1,temp);
		steps[i][j-1] = 0;
	}

	//printArr(steps);

//	if(isWord(temp))
//	{
//		//printf("\n");
//		puts(temp);
//		numberOfWords++;
//	}

	return numberOfWords;
}

int printWords(char A[MATRIX_SIZE][MATRIX_SIZE])
{
	int numberOfWords = 0;

	for(int i = 0; i < MATRIX_SIZE; i++)
	{
		for(int j = 0; j < MATRIX_SIZE; j++)
		{
			int steps[MATRIX_SIZE][MATRIX_SIZE] = {0};
			char s[] = {};
			//printf("%s",s);
			numberOfWords += recorcivePrintWords(A,steps,i,j,s);
		}
	}

	return numberOfWords;
}


int main(void) {

	char A[MATRIX_SIZE][MATRIX_SIZE] = {{'C','A','R','T'},{'E','T','A','K'},{'E','S','M','E'},{'L','L','P','N'}};
	//char A[MATRIX_SIZE][MATRIX_SIZE] = {{'C','A'},{'R','T'}};

	printf("%d",printWords(A));


	return 0;
}


