/*
 ============================================================================
 Name        : send_udp.c
 Author      : moshe
 Version     : 0.1
 Created on  : Feb 5, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define msgSize 10

int main(int argc, char *argv[])
{
  int socket_fd;						// The number that given from socket method
  struct sockaddr_in  dest,from;		// The struct contain type of IP, IP, Port of client
  struct hostent *hostptr;				// Stores information about a given host, such as host name, IPv4 address.
  char msg[msgSize];					//The variable hold the message that send to other side and after that given from the other side.
  socklen_t sizeStructFrom;				//Size of struct that given from the other side.

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);	//Create a socket
  memset((char *) &dest,0, sizeof(dest)); 		/* They say you must do this */ //Clean the piece of memory.
  hostptr = gethostbyname(argv[1]);				//Get the host name and enter to to the struct
  
  dest.sin_family = (short) AF_INET;			//Type of IP (IPv4 or Ipv6)
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);//Copy the piece of memory, in size h_length, from right, IP address. 
  dest.sin_port = htons((u_short)0x3333);		//The number of port

  strcpy(msg,"Client");
  sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&dest,sizeof(dest));		//Send the message to the address that contain
                  
  bzero(msg,sizeof(msg));//Clean the piece of memory.
  recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&sizeStructFrom);	// Receive the message from the other side.
  puts(msg);      
                 
  return 0;
}
