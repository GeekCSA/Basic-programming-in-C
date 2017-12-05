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

#define client 3333//Port of client
#define router 3334//Port of router
#define server 3335//Port of server

#define msgSize 100

void printsin(struct sockaddr_in *sin, char *pname, char* msg){
    char *ipAdd = inet_ntoa(sin->sin_addr);// Converts the IP from the IPv4 numbers-and-dots notation into binary form.
    puts(pname);
    printf("%s ip = %s, port = %d\n", msg, ipAdd, sin->sin_port);//Print the IP and Port number.
}

int main(int argc, char *argv[])
{
  int socket_fd;
  socklen_t fsize;
  struct sockaddr_in  s_in, from, to;//Struct of the client, messages received and messages sent
  char msg[msgSize];//The message itself
  
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//Create a socket.

  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */

  s_in.sin_family = (short)AF_INET;//Type of IP (IPv4 or Ipv6)
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ //Enter the IP. You can use INADDR_ANY constant to stand for “any incoming address”
  s_in.sin_port = client; //The client port

  printsin( &s_in, "Client_UDP", "Local socket is:"); 

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));//Ask constant port number.

  while(1) {
           
    //Sent to router
    to.sin_family = (short) AF_INET;//Type of IP (IPv4 or Ipv6)
	 to.sin_addr.s_addr = htonl(INADDR_ANY); 
    to.sin_port = router;//The number of port
 
    fgets(msg,msgSize,stdin);//Ask text from user for the message that client will send.
         
    //Sent to server   
    //puts(msg);
    if(strcmp(msg,"exit\n") == 0 )//Check if the user entered "exit" if he entered "exit" the client sends message of closing the exit from the software.
    {
    	strcpy(msg,"client exit"); 
    	sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to));
    	return 0; 
    }
    
    sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to));//Send the message to the router.
    
	 memset((char *) &to,0, sizeof(to));    
	 	 
	 //Receive from client 
  	 
    fsize = sizeof(from);
    recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize); //Wait for a message from the router.  
    printsin(&from, "recv_udp: ", "Packet from:");
    //printf("%u",from.sin_addr.s_addr);
    
    memset((char *) &from,0, sizeof(from));

    puts(msg);
    
    bzero(msg,msgSize);
    fflush(stdout);

  }
  
  return 0;
  
}
