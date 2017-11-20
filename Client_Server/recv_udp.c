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



int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  struct { char head; char body[10]; char tail;} msg;

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */

  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */
  s_in.sin_port = htons((u_short)0x3333);

  //printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  //fflush(stdout);

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  while(1) {
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    //printsin( &from, "recv_udp: ", "Packet from:");
    printf("Got data ::%c%s%c\n",msg.head,msg.body,msg.tail); 
    fflush(stdout);
    
    
  }
  
  return 0;
}
