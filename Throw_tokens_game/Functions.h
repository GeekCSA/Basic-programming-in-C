/*
 * Functions.h
 *
 *  Created on: Dec 14, 2017
 *      Author: Student
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 6
#define COLUMNS 7

/**
 * The function that manages the game
 */
void play();

/**
 * The function checks whether a row, row, or diagonal set exists
 */
bool hasSeries(int table[ROWS][COLUMNS],int rows,int columns,int x,int y,int playerOrder);

/**
 * The function checks whether the received number is correct and does not return a message accordingly
 *
 * If return 0 is everything OK.
 *
 * If return 1 than the input is not any number, or double with full column.
 *
 * If return 2 than the input is double number, with correct column.
 *
 * If return 3 than the input is integer number, but out of the table and not UNDO (0).
 *
 * If return 4 than the input is integer number, but cannot UNDO because the table is empty.
 *
 * If return 5 than the input is integer number, but the correct column is full.
 *
 * If return 6 than the input is integer number, but the table is full.
 */
int checkInput(int head_of_columns[],int columns,char* user_choice, int* num_of_user_choice);

/**
 * The function print array of integer numbers.
 */
void printArr(int a[ROWS][COLUMNS]);

/**
 * The function checks the amount of characters that are different from digits and points.
 */
int checkNotDigitNotPoint(char* s,int len);

/**
 * The function receives a character and checks how many times it appears in the string
 */
int checkChar(char* s,int len, char c);

