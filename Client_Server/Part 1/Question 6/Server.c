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

#define client 3333//Client port number.
#define router 3334//Router port number.
#define server 3335//Server port number.

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
	struct sockaddr_in s_in, from, to;
	char msg[msgSize];

	socket_fd = socket (AF_INET, SOCK_DGRAM, 0);//Create a socket.

	memset((char *) &s_in,0, sizeof(s_in));  	/* They say you must do this    */

	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);   /* WILDCARD */
	s_in.sin_port = server;

	printsin( &s_in, "Server_UDP", "Local socket is:");

	bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));//Ask constant port number.

	while(1) {

		//Receive from client
		fsize = sizeof(from);
		recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
		printsin(&from, "recv_udp: ", "Packet from:");

		memset((char *) &from,0, sizeof(from));

		puts(msg);

		fgets(msg,msgSize,stdin); //Ask text from user for the message that server will send.

		//Check if the user entered "exit" if he entered "exit" the server sends message of closing the exit from the software.
		if(strcmp(msg,"exit\n") == 0 )
		{
			strcpy(msg,"Server exit");
			sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to));
			return 0;
		}

		//Sent to router
		to.sin_family = (short) AF_INET;//Type of IP (IPv4 or Ipv6)
		to.sin_addr.s_addr = htonl(INADDR_ANY); //Enter the IP. You can use INADDR_ANY constant to stand for “any incoming address”.
		to.sin_port = router;			//The number of port

		sendto(socket_fd,msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to));//Sends the message to the router.

		memset((char *) &to,0, sizeof(to));

		fflush(stdout);
	}

	return 0;
}
