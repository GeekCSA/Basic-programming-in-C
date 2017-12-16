/*
 * Functions.h
 *
 *  Created on: Dec 14, 2017
 *      Author: Student
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLUMNS 5

void play();

bool hasSeries(int table[ROWS][COLUMNS],int rows,int columns,int x,int y,int playerOrder);

bool checkFullcolumn(int head_of_columns[COLUMNS],int columns,int user_choice);

/**
 * The function print array of integer numbers.
 */
void printArr(int a[ROWS][COLUMNS]);

