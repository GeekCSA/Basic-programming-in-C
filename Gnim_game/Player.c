/*
 * Player.c
 *
 *  Created on: Nov 12, 2017
 *      Author: moshe
 */

#include <math.h>
#include "Player.h"

void play(int left,int center, int right, int turn,int bigPacket, int mediumPacket, int smallPacket)

{
	int userChoicePacket,userNewNumber;

	while (left + center + right > 1) {
			if (turn == 1)
			{
				turn = 0; //that in the next loop will be the computer turn
				printf("Your Turn\n please state how much to take? ");

				scanf("%d",&userChoicePacket);
				while (userChoicePacket != left && userChoicePacket != center && userChoicePacket != right)
				{
					printf("Incorrect number! Please enter a %d, %d or %d.\n",left,center,right);
					scanf("%d",&userChoicePacket);
				}
				printf(" to ");

				scanf("%d",&userNewNumber);
				while (userNewNumber < 0 || (userNewNumber >= userChoicePacket))
				{
					printf("Incorrect number! Please enter a number from 0 to %d.\n",userChoicePacket - 1);
					scanf("%d",&userNewNumber);
				}

				//userNewNumber
				if(left == userChoicePacket)
				{
					left = userNewNumber;
				}
				else
				{
					if(center == userChoicePacket)
					{
						center = userNewNumber;
					}
					else
					{
						if(right == userChoicePacket)
						{
							right = userNewNumber;
						}
					}
				}
			}
			else//If the isn't balance the computer would play
			{
				turn = 1; //that in the next loop will be the user turn
				if((left > 1 && center > 1) || (left > 1 && right > 1) || (center > 1 && right > 1)) // If 2 from 3 of all of packets are more than 1
				{
					if(left == right)
						center = 0;
					else
					{
						if(left == center)
							right = 0;
						else
							if(center == right)
								left = 0;
					}
					if(left == bigPacket)//The computer need to balance the greatest
					{
						printf("I turned %d to %d\n",left,mediumPacket - smallPacket);
						left = mediumPacket - smallPacket;
						if(left == 0)
						{
							printf("I loss!!");
							right = 0;
							center = 0;
						}

					}
					else
					{
						if(center == bigPacket)
						{
							printf("I turned %d to %d\n",center,mediumPacket - smallPacket);
							center = mediumPacket - smallPacket;
							if(center == 0)
							{
								printf("I loss!!");
								right = 0;
								left = 0;
							}
						}
						else
						{
							printf("I turned %d to %d\n",right,mediumPacket - smallPacket);
							right = mediumPacket - smallPacket;
							if(right == 0)
							{
								printf("I loss!!");
								left = 0;
								center = 0;
							}
						}
					}
				}
				else//If there are not 2 packets with more 1
				{
					if((left == 1 && center == 1) || (left == 1 && right == 1) || (center == 1 && right == 1))// If 2 from 3 of all of packets are equal 1
					{
						if (left == 1 && center == 1 && right == 1) {
							printf("Error!!! 1,1,1 -- now is computer turn!!\n");
						}
						else//If not all packets equal to 1, than maximun 2 packets equal to 1
						{// If 2 packets equal to 1 than we decrees the third to 1
							if(left > 1)
							{
								printf("I turned %d to %d\n",left,1);
								left = 1;
							}
							else
							{
								if(center > 1)
								{
									printf("I turned %d to %d\n",center,1);
									center = 1;
								}
								else
								{
									if (right > 1) {
										printf("I turned %d to %d\n",right,1);
										right = 1;
									}
									else//(1,1,0)!
									{
										if(left == 0)
										{
											printf("I turned %d to %d\n",1,0);
											right = 0;
											printf("Game Over - You Lost !! \n");
										}
										else
										{
											if(center == 0)
											{
												printf("I turned %d to %d\n",1,0);
												left = 0;
												printf("Game Over - You Lost !! \n");
											}
											else
											{
												if(right == 0)
												{
													printf("I turned %d to %d\n",1,0);
													left = 0;
													printf("Game Over - You Lost !! \n");
												}
											}
										}
									}
								}
							}
						}
					}
					else
					{//If don't have 2 packets that equal to 1
						if((left == 0 && center == 0) || (center == 0 && right == 0) || (left == 0 && right == 0))//If there are 2 packets that equal to 0 and the third is more 1
						{//Decrees the third to 1
							if(left >= 1)
							{
								printf("I turned %d to %d\n",left,1);
								left = 1;
								printf("Game Over - You Lost !! \n");
							}
							else
							{
								if(center >= 1)
								{
									printf("I turned %d to %d\n",center,1);
									center = 1;
									printf("Game Over - You Lost !! \n");
								}
								else
								{
									printf("I turned %d to %d\n",right,1);
									right = 1;
									printf("Game Over - You Lost !! \n");
								}
							}
						}
						else
						{//If one equals to 1 and other equals to 0 and the third is more 1 then we need to decrees the third to 0
							if(left > 1)
							{
								printf("I turned %d to %d\n",left,0);
								left = 0;
								printf("Game Over - You Lost !! \n");
							}
							else
							{
								if(center > 1)
								{
									printf("I turned %d to %d\n",center,0);
									center = 0;
									printf("Game Over - You Lost !! \n");
								}
								else
								{
									printf("I turned %d to %d\n",right,1);
									right = 0;
									printf("Game Over - You Lost !! \n");
								}
							}
						}
					}
				}
				printf("packet sizes are\n");
				printf("%d %d %d\n\n",right,center,left);
			}
			// sort the packets - start
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
			// sort the packets - end
		}
}
