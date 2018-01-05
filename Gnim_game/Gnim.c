/*
 ============================================================================
 Name        : Gnim.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Player.h"

int main(void) {

	int right,center,left;
	int bigPacket, mediumPacket, smallPacket;
	int userChoicePacket,userNewNumber;
	int turn; // If turn = 0 then now computer turn else now player turn

	printf("please enter 3 numbers\n");
	scanf("%d%d%d",&right,&center,&left);
	while(((left + center + right) < 1)||(right < 0 || center < 0 || left < 0))
	{
		printf("Incorrect number! Please enter numbers that equals of greater than 0 (zero three times is illegal.\n ");
		scanf("%d%d%d",&right,&center,&left);
	}
	printf("packet sizes are\n");
	printf("%d %d %d\n\n",right,center,left);

	if(right > center)
	{
		if(center > left)
		{
			bigPacket = right;
			mediumPacket = center;
			smallPacket = left;
		}
		else
			if(right > left)
			{
				bigPacket = right;
				mediumPacket = left;
				smallPacket = center;
			}
			else
			{
				bigPacket = left;
				mediumPacket = right;
				smallPacket = center;
			}
	}
	else
	{
		if(right > left)
		{
			bigPacket = center;
			mediumPacket = right;
			smallPacket = left;
		}
		else
			if(center > left)
			{
				bigPacket = center;
				mediumPacket = left;
				smallPacket = right;
			}
			else
			{
				bigPacket = left;
				mediumPacket = center;
				smallPacket = right;
			}
	}
	//Who start to play

	if (bigPacket == mediumPacket + smallPacket)
		turn = 1;//User
	else
		turn = 0;//Computer
	if(left == 1 && center == 1 && right == 1)//1,1,1
		turn = 1;
	if(bigPacket == 1 && mediumPacket == 0)//1,0,0
	{
		printf("Game Over - You Lost !! \n");
		left = 0;
		center = 0;
		right = 0;
	}
	if(mediumPacket == 1 && smallPacket == 0)//1,1,0
		turn = 0;//Computer

	play(left,center,right,turn,bigPacket,mediumPacket,smallPacket);

	return 0;
}
