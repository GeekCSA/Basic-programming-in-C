/*
 * Functions.c
 *
 *  Created on: Dec 14, 2017
 *      Author: moshe
 */

#include "Functions.h"


void play()
{
	int head_of_columns[COLUMNS];
	int table_of_tokens[ROWS][COLUMNS] = {{0}};
	int table_of_steps[ROWS][COLUMNS] = {{0}};
	int count_of_turns = 0;
	int user_choice;
	bool win_Situation = false;

	for (int i = 0; i < COLUMNS; i++) {
		head_of_columns[i] = ROWS - 1;
	}

	while(1)
	{
		puts("Enter 0 for UNDO.\nOr enter number of column that you want to put the token");
		scanf("%d",&user_choice);

		while(checkFullcolumn(head_of_columns,COLUMNS,user_choice))
		{
			printf("Illegal number! Please enter number between 0 to %d",COLUMNS);
			scanf("%d",&user_choice);
		}


		if((user_choice > 0) && (count_of_turns < COLUMNS*ROWS))
		{
			user_choice--;//In order to fix to index of array that start from 0.
			count_of_turns++;

			int head_of_column = head_of_columns[user_choice];
			head_of_columns[user_choice]--;
			table_of_steps[head_of_column][user_choice] = count_of_turns;

			if(count_of_turns % 2 == 0)
			{//Turn of first player
				table_of_tokens[head_of_column][user_choice] = 1;
				win_Situation = hasSeries(table_of_tokens,ROWS,COLUMNS,user_choice,head_of_column,1);
			}
			else
			{//Turn of second player
				table_of_tokens[head_of_column][user_choice] = 2;
				win_Situation = hasSeries(table_of_tokens,ROWS,COLUMNS,user_choice,head_of_column,2);
			}
		}
		else
		{
			int index_of_prev_turnX = -1;
			int index_of_prev_turnY = -1;
			int column_head = -1;

			for (int i = 0; i < COLUMNS; i++) {

				column_head = head_of_columns[i] + 1;
				if((column_head >= 0) && (column_head < ROWS) && (table_of_steps[column_head][i] == count_of_turns))
				{
					index_of_prev_turnX = i;
					index_of_prev_turnY = column_head;
				}
			}
			//printf("\ncolumn: %d \n",index_of_prev_turnX);
			//printf("\nrow: %d \n",index_of_prev_turnY);

			if(index_of_prev_turnX > -1)
			{
				head_of_columns[index_of_prev_turnX]++;
				table_of_steps[index_of_prev_turnY][index_of_prev_turnX] = 0;
				table_of_tokens[index_of_prev_turnY][index_of_prev_turnX] = 1;
				table_of_tokens[index_of_prev_turnY][index_of_prev_turnX] = 0;
			}

			if(count_of_turns > 1)
				count_of_turns--;
		}

		printArr(table_of_tokens);

		if(win_Situation)
		{
			int player_order = (count_of_turns % 2 == 0)? 2 : 1;
			printf("The player %d win",player_order);
			break;
		}
	}
}

bool checkFullcolumn(int head_of_columns[],int columns,int user_choice)
{
	if((user_choice < 0))
		return true;

	if(user_choice > columns)
		return true;

	if(head_of_columns[user_choice - 1] == -1)//I sub 1 for fix to index of array that start from 0
		return true;

	return false;
}

bool hasSeries(int table[ROWS][COLUMNS],int rows,int columns,int x,int y,int playerOrder)
{
	bool hasWin = false;

	int sequence_length = 0;

	//[row][column]

	//printf("\n");
	for(int k = y; k < y + 1 && sequence_length < 4; k++)
	{//row
		for(int q = 0; q < COLUMNS && sequence_length < 4; q++)
		{
			//printf(" %d ",table[k][q]);

			if(table[y][q] == playerOrder)
				sequence_length++;
			else
				sequence_length = 0;

		}
		//printf("\n");
	}

	hasWin = (sequence_length >= 4)? true : false;
	if(hasWin)
		return hasWin;

	sequence_length = 0;

	//printf("\n");

	for(int k = 0; k < ROWS && sequence_length < 4; k++)
	{//column
		for(int q = x; q < x + 1 && sequence_length < 4; q++)
		{
			//printf(" %d ",table[k][q]);

			if(table[k][x] == playerOrder)
				sequence_length++;
			else
				sequence_length = 0;
		}
		//printf("\n");
	}

	hasWin = (sequence_length >= 4)? true : false;

	if(hasWin)
		return hasWin;

	sequence_length = 0;

	//printf("\n");

	int set = 4;
	int sizeMax = (COLUMNS > ROWS)? COLUMNS : ROWS;

	for(int i = 0; i < sizeMax + 2 * (set - 1) + 1; i++)
	{
		if(((x + i - set >= 0) && (x + i - set < COLUMNS)) && ((y + i - set >= 0) && (y + i - set < ROWS)))
		{
			//printf(" %d ",table[y + i - set][x + i - set]);
			if(table[y + i - set][x + i - set] == playerOrder)
				sequence_length++;
			else
				sequence_length = 0;
		}

	}
	//printf("\n");

	hasWin = (sequence_length >= 4)? true : false;

	if(hasWin)
		return hasWin;

	sequence_length = 0;

	for(int i = 0; i < sizeMax + 2 * (set - 1) + 1; i++)
	{
		if(((x - i + set >= 0) && (x - i + set < COLUMNS)) && ((y + i - set >= 0) && (y + i - set < ROWS)))
		{
			//printf(" %d ",table[y + i - set][x + i - set]);
			if(table[y + i - set][x - i + set] == playerOrder)
				sequence_length++;
			else
				sequence_length = 0;
		}
	}
	//printf("\n");

	hasWin = (sequence_length >= 4)? true : false;

	return hasWin;


}

void printArr(int a[ROWS][COLUMNS])
{
	printf("\n");
	for(int k = 0; k < ROWS; k++)
	{
		for(int q = 0; q < COLUMNS; q++)
		{
			if(a[k][q] == 0)
				printf("| |");
			if(a[k][q] == 1)
				printf("|x|");
			if(a[k][q] == 2)
				printf("|o|");
		}
		printf("\n");
	}

	for(int k = 0; k < COLUMNS; k++)
	{
		printf(" %d ",k + 1);
	}

	printf("\n");
}

