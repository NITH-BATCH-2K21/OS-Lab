// https://www.programminglogic.com/sockets-programming-in-c-using-udp-datagrams/
// https://www.tutorialspoint.com/unix_sockets/socket_core_functions.htm

#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h> // has definitions of sockaddr_storage structure
#include <arpa/inet.h>  // has definition of inet_addr() function

int main()
{
	int udpSocket, nBytes, i;
	char buffer[1024], serv_to_cli[] = "Recieved message from client";
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage; // Address and port of data-sending client will be stored in this 
	// structure, for resending the requested data.
	socklen_t addr_size, client_addr_size; // used in recvfrom function

	udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // function of inet_addr ???
	memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

	if(bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("Error in binding");
		exit(1);
	}

	/* flags are usually set to 0
	1. int send(int sockfd, const void* msg, int len, int flags); - used to send messages to SOCK_STREAM
	or connected SOCK_DGRAM sockets. To send data over unconnected SOCK_DGRAM sockets use sendto function.

	2. int sendto(int sockfd, const void* msg, int len, unsigned int flags, struct sockaddr *to, int tolen);
	tolen is the length of to.

	3. int recv(int sockfd, void *buf, int len, unsigned int flags); - len is the maximum length of buffer
	Used to recieve data from stream sockets or connected datagrams. Use recvfrom to recieve data from unconnected
	datagram sockets.

	4. int recvfrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen);
	* difference between other function, uses a pointer as the last argument.
	
	*/

	/*
	sockaddr_storage is used to make programs agnostic of ipV4 or ipv6 because sockaddr_storage has enough space
	to accomodate ipv6 itself. besides functions like bind(), connect() which use a pointer from sock_addr always 
	typecast it to (struct sock_addr *). This is the rationale behind having sockaddr_storage
	*/

	addr_size = sizeof(serverStorage);

	while(1)
	{
		nBytes = recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *)&serverStorage, &addr_size);

		printf("Message from client : %s\n", buffer);

		memset(buffer, '\0', 1024);
		
		nBytes = sendto(udpSocket, serv_to_cli, strlen(serv_to_cli), 0, (struct sockaddr *)&serverStorage, addr_size);
	}



	return 0;
}
