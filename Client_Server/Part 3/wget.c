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


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define urlSize 100
#define portSize 7
#define msgSize 1024

//cd Desktop
//gcc wget.c -o w.out
//./w.out
//http://www.google.co.il:80/path/filder/file.html 

int str_slice_in_place(char str[], const int index_from, const int index_to)
{
    // a support for only positive indexes
    if (index_from < 0 || index_to < 0)
        return -1;

    int len = index_to - index_from;

    // "index_from" is more than "index_to"
    if (len < 0)
        return -1;

    memmove(str, str + index_from, len);
    str[len] = '\0';
    return 0;
}

int search_char_in_string(char str[], const int index_from, const int index_to,char c)
{
    // a support for only positive indexes
    if (index_from < 0 || index_to < 0)
        return -1;

    int len = index_to - index_from;

    // "index_from" is more than "index_to"
    if (len < 0)
        return -1;

	for(int i = 0; i < index_to; i++) {
		if(str[i] == c) {
			return i;
		}
	}
		
   return -1;
}


int main(int argc, char* argv[]) {
  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  char url[urlSize];
  char *port;
  int portNum = 80;
  //char *portres;
  char *urlres;
 // char* msg[msgSize];//The variable hold the message that send to other side and after that given from the other side.
 // int sizeStructFrom;//Size of struct that given from the other side.
 // int socket_fd;							// The number that given from socket method
//  struct sockaddr_in /* dest*/,from;			// The struct contain type of IP, IP, Port of client
 // struct hostent *hostptr;				// Stores information about a given host, such as host name, IPv4 address.
  
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  char value; 
  
  //Get the URL from user.
  
  //Get from user URL  https://www.yahoo.com/:80/path/filder/file.html 
  puts("Enter URL");  
  fgets(url,urlSize,stdin);
  
  url[strlen(url) - 1] = '/';
  puts(url);
  
  //Cut the head "https:" from the URL. the resault is: //www.yahoo.com/:80/path/filder/file.html  
  urlres = strchr(url,'/');
  
  //Cut the head "//" from the URL. the resault is:   www.yahoo.com/:80/path/filder/file.html
  urlres = strchr(urlres,urlres[2]);

  //If in the current URL has ':' than there is port number, and the code take thos number from URL.
  if(strchr(urlres,':') != NULL) {
  //Cut the head "www.example.comExample" from the URL. the resault is: :80/path/filder/file.html
  port = strchr(urlres,':');
  
  //Take the port number that located after ':' and before the first time that appear '/' the result is: (for example) 80  
  str_slice_in_place(port, 1, search_char_in_string(port,0,urlSize,'/'));
  puts("Port number:");
  puts(port);
  
  //Exchange the string of port number to integer.
  portNum = atoi(port);	
  printf("Port number int: %d\n",portNum);
  }
  
  //Take the host name from the urlres variable.
  str_slice_in_place(urlres, 0, search_char_in_string(urlres,0,urlSize,'/'));
  puts("Host name:");
  puts(urlres);

  hostname = urlres;
  
  puts(hostname);
  
  //Exchange the host name to IP address.
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);
  
  printf("The IP address of %s is %s\n",urlres,hostaddr);
  
  
  
  //Send message to the server in order to get the page.
  
  //Create a socket. 
  sock = socket(AF_INET, SOCK_STREAM, 0);//Ask socket from computer 
  if (sock < 0)//Check if the socket succeed
    { 
    	perror ("Error opening channel");
      close(sock);
      exit(1);
    }
    else {
    	puts("Socket success");
    }
      

  memset((char *)&cli_name,0, sizeof(cli_name));
  
  //Create a struct with IP and port.
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(hostaddr); 
  cli_name.sin_port = htons(portNum);
  
  puts("Struct success");

  // Tried to establish connection and check if this succeed
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
  { perror ("Error establishing communications");
      close(sock);
      exit(1);
  }
  else 
  {
    char sendMsg[1024];
    
    strcat(sendMsg, "GET ");
    strcat(sendMsg, url);
    strcat(sendMsg, " HTTP/1.0\nHOST:");
    strcat(sendMsg, urlres);
    strcat(sendMsg, "\n\n");
    
    send(sock,sendMsg,sizeof(sendMsg),0);
  }


/*  for (count = 1; count <= 1; count++)//Read the message
    { read(sock, &value, 4);
      printf("%s", value);
      
    }*/
    while(read(sock, &value, 1) != 0)
    {
    	printf("%d", &value);
    }
/*    char recvMsg[10000];
    recv(sock,recvMsg,10000,0);
    puts(recvMsg);*/
  
  
  exit(0);
}

