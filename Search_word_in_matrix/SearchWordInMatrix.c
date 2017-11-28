/*
 ============================================================================
 Name        : SearchWordInMatrix.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Functions.h"

int main(void) {

	char A[MATRIX_SIZE][MATRIX_SIZE] = {{'C','A','R','T'},{'E','T','A','K'},{'E','S','M','E'},{'L','L','P','N'}};
	//char A[MATRIX_SIZE][MATRIX_SIZE] = {{'C','A'},{'R','T'}};

	printf("\nThe number of words that found in the matrix is: %d",printWords(A));


	return 0;
}

