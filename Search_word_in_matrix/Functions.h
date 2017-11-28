/*
 * Functions.h
 *
 *  Created on: Nov 28, 2017
 *      Author: moshe
 */

#include <stdbool.h>
#include <string.h>
//#include "searchWord.h";

#define MATRIX_SIZE 4 // Number of columns and rows of matrix

/**
 * Vocabulary searched in a matrix
 * @return boolean if the word is in the vocabulary.
 */
bool isWord(char* s);

/**
 * The function print array of integer numbers.
 */
void printArr(int a[MATRIX_SIZE][MATRIX_SIZE]);

/**
 * The function checks for each index (i,j) whether it can move to the top, bottom, right, or left.
 * If we find it possible to move on, then she calls herself recursively.
 */
int recursivePrintWords(char A[MATRIX_SIZE][MATRIX_SIZE],int steps[MATRIX_SIZE][MATRIX_SIZE],int i, int j,char word1[]);

/**
 * The function passes all the points in the matrix and each of them runs the function recursivePrintWords.
 * @return The number of words found.
 */
int printWords(char A[MATRIX_SIZE][MATRIX_SIZE]);



