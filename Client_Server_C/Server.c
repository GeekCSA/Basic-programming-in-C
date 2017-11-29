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

#define client 3333
#define router 3334
#define server 3335

#define msgSize 10

void printsin(struct sockaddr_in *sin, char *pname, char* msg){
    char *ipAdd = inet_ntoa(sin->sin_addr);
    puts(pname);
    printf("%s ip = %s, port = %d\n", msg, ipAdd, sin->sin_port);
}

int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from, to;
  char* msg[msgSize];
  int sizeStructFrom;
  
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */

  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
  s_in.sin_port = server;

  printsin( &s_in, "Server_UDP", "Local socket is:"); 

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  while(1) {
  	
  	 //Receive from client 
  	 
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);   
    printsin(&from, "recv_udp: ", "Packet from:");
    
    memset((char *) &from,0, sizeof(from));
    
    puts(msg);
    
    fgets(msg,msgSize,stdin);     
    //Sent to server   
    
    if(strcmp(msg,"exit\n") == 0 )
    {
    	strcpy(msg,"Server exit"); 
    	sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to));
    	return 0; 
    }
           
    //Sent to router
    struct hostent *hostptr;
    hostptr = gethostbyname("127.0.0.1");
    to.sin_family = (short) AF_INET;//Type of IP (IPv4 or Ipv6)
	 to.sin_addr.s_addr = htonl(INADDR_ANY); 
    to.sin_port = router;//The number of port
           
    //Sent to server
    //bzero(msg,msgSize);    
    //strcpy(msg,"Server receive message.");   
    sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to));
    
	 memset((char *) &to,0, sizeof(to));    
    
    fflush(stdout);
  }
  
  return 0;
  
}
