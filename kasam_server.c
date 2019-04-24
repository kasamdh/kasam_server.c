//Kasam Dhakal

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void error(const char *message)
{
	perror(message);
	exit(1);
}


int main(int argc, char *argv[])
{
	int sockfd, nsockfd, pnum;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	if (argc < 2) {
		fprintf(stderr, "ERROR: Not enough arguments! \n");
		exit(1);
	}
	fprintf(stdout, "The server is listening at port: %s\n", argv[1]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

//	if (n < 0)
//		error("ERROR ");
//	fprintf(stdout, "Here is the message: %s", buffer);
//	n = write(nsockfd, "message received\n", 18);

//	if (nsockfd < 0)
//		error("ERROR ");
//	bzero(buffer, 256);
//	n = read(nsockfd, buffer, 255);
//	if (n < 0)
//		error("ERROR ");
	if (sockfd < 0)
		error("ERROR");

	bzero((char *)&serv_addr, sizeof(serv_addr));

	pnum = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(pnum);
	printf("Ready..\n");
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR ");


	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	nsockfd = accept(sockfd,
		(struct sockaddr *) &cli_addr,
		&clilen);

	bzero(buffer,256);
	n = read(nsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s",buffer);

	n = write(nsockfd,"My router number is 1\nMy leasts known costs are:\nRouter 0: 1\nRouter 1: 0\nRouter 2: 1",255);
	if (n < 0) error("ERROR writing to socket");

	printf("Client Closed ");
	close(nsockfd);
	close(sockfd);
	return 0;
}
