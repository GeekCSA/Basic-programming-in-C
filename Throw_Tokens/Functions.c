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
	int number_of_massege = 0;
	bool win_Situation = false;

	for (int i = 0; i < COLUMNS; i++) {
		head_of_columns[i] = ROWS - 1;
	}
	puts("Welcome!");

	printArr(table_of_tokens);

	while((number_of_massege == 0))
	{
		setvbuf(stdout,NULL, _IONBF, 0);
		char user_number[50];

		if(count_of_turns == COLUMNS*ROWS)
		{
			puts("The end matrix is:\n");
			printArr(table_of_tokens);
			puts("It's a tie!");
			return ;
		}

		printf("Player %c, please enter a column number (or 0 to UNDO)",(count_of_turns % 2 == 0)? 'o' : 'x');
		gets(user_number);

		number_of_massege = checkInput(head_of_columns,COLUMNS,user_number,&user_choice);

		//Input a number from user
		while(number_of_massege)
		{
			if(number_of_massege == 1)
				return ;

			int tableIsFull = 0;

			for(int i = 0; i < COLUMNS; i++)
			{
				if(table_of_steps[0][i] != 0)
					tableIsFull = 1;
			}

			if(number_of_massege == 2)
				break;

			puts("The corrent table is:\n\t");
			printArr(table_of_tokens);
			gets(user_number);

			number_of_massege = checkInput(head_of_columns,COLUMNS,user_number,&user_choice);
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
				//table_of_tokens[index_of_prev_turnY][index_of_prev_turnX] = 1;
				table_of_tokens[index_of_prev_turnY][index_of_prev_turnX] = 0;
			}

			if(count_of_turns > 1)
				count_of_turns--;
		}

		printArr(table_of_tokens);

		if(win_Situation)
		{
			char player_order = (count_of_turns % 2 == 0)? 'x' : 'o';
			printf("The player %c win",player_order);
			break;
		}
	}
}

int checkChar(char* s,int len, char c)
{
	int countC = 0;

	for(int i = 0; i < len; i++)
	{
		if(s[i] == c )
			countC++;
	}

	return countC;
}

int checkNotDigitNotPoint(char* s,int len)
{
	int countC = 0;

	for(int i = 0; i < len; i++)
	{
		if((s[i] < '0') || ((s[i] > '9') && (s[i] != '.')))
			countC++;
	}

	return countC;
}

/**
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
 *
 */
int checkInput(int head_of_columns[],int columns,char* user_number_choice, int* num_of_user_choice)
{
	int numChoice;

	int countOfPoints = checkChar(user_number_choice,strlen(user_number_choice),'.');

	int countOfChars = checkNotDigitNotPoint(user_number_choice,strlen(user_number_choice));

	if(countOfChars > 0)
	{
		puts("Invalid input, bye-bye!");
		*num_of_user_choice = -1;
		return 1;
	}

	if(countOfPoints > 1)
	{
		puts("Invalid input, bye-bye!");
		*num_of_user_choice = -1;
		return 1;
	}

	numChoice = (int)atof(user_number_choice);

	if(countOfPoints == 1)
	{
		puts("Invalid input, bye-bye!");
		if(!(head_of_columns[numChoice - 1] == -1))
		{
			*num_of_user_choice = numChoice;
			return 2;
		}
		*num_of_user_choice = -1;
		return 1;
	}

	if((numChoice < 0))
	{
		*num_of_user_choice = -1;
		printf("Invalid input, the number must be between 1 to %d (or 0 to undo):",columns);
		return 3;
	}

	if(numChoice > columns)
	{
		*num_of_user_choice = -1;
		printf("Invalid input, the number must be between 1 to %d (or 0 to undo):",columns);
		return 3;
	}

	if(numChoice == 0)
	{
		for(int i = 0; i < columns; i++)
		{
			if(head_of_columns[i - 1] < ROWS - 1)//I sub 1 for fix to index of array that start from 0
			{
				*num_of_user_choice = numChoice;
				return 0;
			}
		}

		*num_of_user_choice = -1;
		puts("Board is empty - can't undo!");
		return 4;
	}

	bool fullTable = true;
	for(int i = 0; i < columns; i++)
	{
		if(head_of_columns[i - 1] > -1)//I sub 1 for fix to index of array that start from 0
		{
			fullTable = false;
		}
	}

	if(fullTable)
	{
		puts("full table");
		return 6;
	}


	if(head_of_columns[numChoice - 1] == -1)//I sub 1 for fix to index of array that start from 0
	{
		*num_of_user_choice = -1;
		puts("Invalid input, this column is full. Please choose another one:");
		return 5;
	}
	*num_of_user_choice = numChoice;
	return 0;
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
			printf("|");
			if(a[k][q] == 0)
				printf(" ");
			if(a[k][q] == 1)
				printf("x");
			if(a[k][q] == 2)
				printf("o");

		}
		printf("|");
		printf("\n");
	}

	for(int k = 0; k < COLUMNS; k++)
	{
		printf(" %d",k + 1);
	}

	printf("\n");
}

