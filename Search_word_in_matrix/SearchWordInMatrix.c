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

#include "Functions.h"

int main(void) {

	char A[MATRIX_SIZE][MATRIX_SIZE] = {{'C','A','R','T'},{'E','T','A','K'},{'E','S','M','E'},{'L','L','P','N'}};

	printf("\nThe number of words that found in the matrix is: %d",printWords(A));
	return 0;
}

