#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

//#include <arpa/inet.h>
//#include <stdio.h>

int main(int argc, char *argv[])
{
  int socket_fd;							// The number that given from socket method
  struct sockaddr_in  dest;			// The struct contain type of IP, IP, Port of client
  struct hostent *hostptr;				// Stores information about a given host, such as host name, IPv4 address.
  struct { char head; char body[10]; char tail; } msgbuf;//The message that given from 

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//Create a socket that take IP and Port
  memset((char *) &dest,0, sizeof(dest)); /* They say you must do this */ //Clean the piece of memory.
  hostptr = gethostbyname(argv[1]);//Get the host name and enter to to the struct
  
  //printf("%s",hostptr->h_name);  
  
  //inet_aton("169.254.125.196", &dest.sin_addr);
  
  dest.sin_family = (short) AF_INET;//Type of IP (IPv4 or Ipv6)
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);//Copy the piece of memory, in size h_length, from right 
  dest.sin_port = htons((u_short)0x3333);//The number of port

  msgbuf.head = '<';//Set the char header of message
  msgbuf.body[0] = 'm'; /* IMPORTANT! */ // Get the ID process and convert it to the other number
  msgbuf.body[1] = 'o';
  msgbuf.body[2] = 's'; /* IMPORTANT! */ // Get the ID process and convert it to the other number
  msgbuf.body[3] = 'h';   
  msgbuf.tail = '>';//Set the char tail of message

  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest));//Send the message to the address that contain 

  return 0;
}