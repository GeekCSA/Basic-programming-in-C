/*
 ============================================================================
 Name        : recv_udp.c
 Author      : moshe
 Version     : 0.1
 Created on  : Feb 5, 2018
 Copyright   : Your copyright notice
 ============================================================================
 */
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define msgSize 10

void printsin(struct sockaddr_in *sin, char *pname, char* msg){
    char *ipAdd = inet_ntoa(sin->sin_addr);// Converts the IP from the IPv4 numbers-and-dots notation into binary form.
    puts(pname);
    printf("%s ip = %s, port = %d\n", msg, ipAdd, sin->sin_port);//Print the IP and Port number.
}

int main(int argc, char *argv[])
{
  int socket_fd;
  struct sockaddr_in  s_in, from;
  char msg[msgSize];
  
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);	//Create a socket

  memset((char *) &s_in,0, sizeof(s_in));  		/* They say you must do this */ //Clean the piece of memory.
 
  s_in.sin_family = (short)AF_INET;				//Type of IP (IPv4 or Ipv6)
  s_in.sin_addr.s_addr = htonl(INADDR_ANY); 	/* WILDCARD */ //Enter the IP. You can use INADDR_ANY constant to stand for “any incoming address”.
  s_in.sin_port = htons((u_short)0x3333);		//Number of the port of this side.

  printsin( &s_in, "RECV_UDP", "Local socket is:"); 

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));//Ask constant port number.

  while(1) {
  	
  	//Receive from client
    socklen_t fsize = sizeof(from);
    recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);// Wait to the message from other side.
    printsin(&from, "recv_udp: ", "Packet from:");
    
    puts(msg);
           
    //Sent to client
    bzero(msg,msgSize);   
    strcpy(msg,"Server");  
    sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&from,sizeof(from));//Send message to the sender.
    
    fflush(stdout);
  }
  
  return 0;
}
