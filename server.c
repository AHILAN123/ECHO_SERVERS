					// It wil include  the server  side code 
					// argv[0] : filename
					// argv[1] : port_no
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

void error(const char *msg){perror(msg);exit(1);} //for system errors only, not for user side errors, bindor accept or socket(){these are system functions} generally fails and hence we use this. 

int main(int argc , char *argv[]){

	if(argc<2){fprintf(stderr,"port not provided program terminated. \n");exit(1);}

	int sockfd, newsockfd, portno, n;
	char buffer[255];
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len; //we need client as server would CONNECT, so WHO is connecting becomes important

	//creating a socket.
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){error("failure to open socket. \n");}

	//pointer,size
	bzero((char *)&server_addr, sizeof(server_addr)); //as the serv_addr may initially be filled with random form the old stack bzero would initialize it to 0; as sometimes while i initialize after the random garbage values causes error

	portno = atoi(argv[1]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr  = INADDR_ANY;
	server_addr.sin_port = htons(portno);


	if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){error("binding failed \n");}
	
	listen(sockfd, 5);

	client_len = sizeof(client_addr);

	newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len); // creating the new socket that establishing a communicationn between the client and the server, the earliler socket was just to listen.

	if(newsockfd<0){error("Connection failed \n");}

	while(1){

		bzero(buffer, 255);
		n = read(newsockfd, buffer, 255);
		if(n<0){error("reading failed \n");}

		printf("Client : %s \n", buffer);

		bzero(buffer,255); //for clearing the buffer 
		fgets(buffer, 255, stdin); //takes input from the server 

		n = write(newsockfd, buffer, strlen(buffer));// and this would return to client
		if(n<0){error("failed to write \n");}

		int i = strncmp("bye", buffer, 3);
		if(i == 0){break;}
	}
	close(newsockfd);
	close(sockfd);
return 0;
}
