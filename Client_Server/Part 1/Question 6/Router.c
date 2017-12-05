#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define msgSize 100

#define client 3333//Port of client
#define router 3334//Port of router
#define server 3335//Port of server

void printsin(struct sockaddr_in *sin, char *pname, char* msg){
    char *ipAdd = inet_ntoa(sin->sin_addr);// Converts the IP from the IPv4 numbers-and-dots notation into binary form.
    puts(pname);
    printf("%s ip = %s, port = %d\n", msg, ipAdd, sin->sin_port);//Print the IP and Port number.
}

int main(int argc, char *argv[])
{
  int socket_fd;
  socklen_t fsize;
  struct sockaddr_in  s_in, from, to;
  char msg[msgSize];
  
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//Create a socket.

  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */

  s_in.sin_family = (short)AF_INET;//Type of IP (IPv4 or Ipv6)
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ //Enter the IP. You can use INADDR_ANY constant to stand for “any incoming address”.
  s_in.sin_port = router;//Enter the router port.

  printsin( &s_in, "Router_UDP", "Local socket is:"); 

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));//Ask constant port number.
  
  double x,randnum;
  
  sscanf(argv[1],"%lf",&x);//Gets the X from terminal.

  while(1) {
  	
  	 //Receive from client 
    fsize = sizeof(from);//Wait for message from client or server.
    recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);   
    printsin(&from, "recv_udp: ", "Packet from:");
    
    puts(msg); 
     
    //Sent to server
    memset((char *) &to,0, sizeof(to)); 

    to.sin_family = (short) AF_INET;//Type of IP (IPv4 or Ipv6)
	 to.sin_addr.s_addr = htonl(INADDR_ANY); 
	 
	 randnum = (double)rand()/(double)RAND_MAX;//Rand number.

	 if((from.sin_port == server ))//If the message given from server then the message that will send to client, else the message will send to server.
	 {
	 	//bzero(msg,msgSize);
	 	//strcpy(msg,"Router return message");  
    	to.sin_port = client;//The number of port
 	 }
 	 else { 
 	 printf("randnum is: %lf\n",randnum);
 	 	if(randnum > x) {//If the random number greater than X then the router will send it to server, else the router blocks the message and sends to the client that the message blocked.
 	 		to.sin_port = server;//The number of port
 	 	} 	 	else {
 	 			bzero(msg,msgSize);
	 			strcpy(msg,"Router NOT pass message");  
    			to.sin_port = client;//The number of port
 	 	}

 	 }
             
    sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to));          
    
    fflush(stdout);
  }
  
  return 0;
}
