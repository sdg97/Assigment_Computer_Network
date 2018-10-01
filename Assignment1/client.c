#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "myFunction.h"

#define MAX_BUF_SIZE 1024
size_t countStrLen(char *str);
int goodbye(char *str, size_t numBytes);
void printData(char *str, size_t numBytes);
int main (void){
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sfd;
	int br;
	int port;
	char ip[20];
	ssize_t byteRecv;
	ssize_t byteSent;
	size_t msgLen;
	int stop = 0;
	socklen_t serv_size;
	char recivedData[MAX_BUF_SIZE];
	char sendData[MAX_BUF_SIZE];
	
	sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if(sfd < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	printf("Insert the number port\n");
	scanf("%d", &port);
	fflush(stdin);
	
	printf("Insert server IP address\n");
	fflush(stdin);
	scanf("%s",ip);

	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr=inet_addr(ip);
	
	serv_size = sizeof(server_addr);
	
	while(!stop){
		printf("Insert new word\n");
		fflush(stdin);
		scanf("%s", sendData);
		//fgets(sendData, MAX_BUF_SIZE, stdin);
		//printf("%s ", sendData);
		
		msgLen = countStrLen(sendData);
		//printf("%lu \n", msgLen);
		byteSent = sendto(sfd, sendData, msgLen,0, (struct sockaddr *) & server_addr, sizeof(server_addr));
		
		if(byteSent < 0){
			printf("problems\n");
		}
		
		if(strncmp(sendData, "exit", 4) == 0){
			byteRecv = recvfrom(sfd, recivedData, MAX_BUF_SIZE, 0, (struct sockaddr*) & server_addr, &serv_size);
				printf("server said: ");
				printData(recivedData, byteRecv);
				stop = 1;
		}
	}
	
	return 0;
	exit(0);
}

