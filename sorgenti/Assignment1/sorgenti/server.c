#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "myFunction.h"

#define MAX_BUF_SIZE 1024


int excape(char *str, size_t numBytes);


int main(void){
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	char ip[20];
	int sfd;
	int br;
	size_t msgLen;
	ssize_t byteRecv;
	ssize_t byteSent;
	socklen_t cli_size;
	char recivedData[MAX_BUF_SIZE];
	char sendData[MAX_BUF_SIZE];
	int port;

	sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sfd < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	server_addr.sin_family = AF_INET;

	printf("Insert the number port\n");
	scanf("%d", &port);
	fflush(stdin);

	server_addr.sin_port = htons(port);

	printf("Insert server IP address\n");
	fflush(stdin);
	scanf("%s",ip);


	server_addr.sin_addr.s_addr = inet_addr(ip);
	br = bind(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr));

	if(br < 0){
		perror("bind");
		exit(EXIT_FAILURE);
	}
	cli_size = sizeof(client_addr);

	while(1){
		byteRecv = recvfrom(sfd, recivedData, MAX_BUF_SIZE, 0, (struct sockaddr*) & client_addr, &cli_size);
		if(byteRecv == -1){
			perror("recivfrom");
			exit(EXIT_FAILURE);
		}
		if(strncmp(recivedData, "exit", byteRecv - 1) == 0){
			strcpy(sendData, "goodbye");
			msgLen = countStrLen(sendData);
			byteSent = sendto(sfd,sendData, msgLen,0, (struct sockaddr *) & client_addr, sizeof(client_addr));
			printf("goodby\n");
			if(byteSent < 0) printf("problems\n");


		} else {
			printf("Sender address: %s ",inet_ntoa(client_addr.sin_addr));
			printData(recivedData, byteRecv);
		}
	}

	return 0;
}
