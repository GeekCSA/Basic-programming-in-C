/*
 ============================================================================
 Name        : net_client.c
 Author      : moshe
 Version     : 0.1
 Created on  : Feb 5, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define SIM_LENGTH 10 
#define IP_ADDRESS "127.0.0.1" 
#define PORT 1337 

int main(void)
{ 
	int sock;
	struct sockaddr_in cli_name;
	int count;
	int value;

	printf("Client is alive and establishing socket connection.\n");

	sock = socket(AF_INET, SOCK_STREAM, 0);//Ask socket from computer

	//Check if the socket succeed
	if (sock < 0)
	{
		perror ("Error opening channel");
		close(sock);
		exit(1);
	}

	memset((char *)&cli_name,0, sizeof(cli_name));

	//Create a struct with IP and port.
	cli_name.sin_family = AF_INET;
	cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS);
	cli_name.sin_port = htons(PORT);//

	// Tried to establish connection and check if this succeed
	if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
	{ perror ("Error establishing communications");
	close(sock);
	exit(1);
	}

	for (count = 1; count <= SIM_LENGTH; count++)//Read the message
	{
		read(sock, &value, 4);
		printf("Client has received %d from socket.\n", value);
	}

	printf("Exiting now.\n");

	close(sock);
	exit(0);
} 
