#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> // contains sockaddr_in structure, and hence defines the various fields in it. It also defines inet_addr() function
// used to specify the IP address of the server
#include<string.h>
#include<stdlib.h> // exit() function
#include<arpa/inet.h> // htnos function

int main()
{
 	int clientSocket, portNum, nBytes;
	char buffer[1024];
	socklen_t addr_size;
	struct sockaddr_in servAddr;
	socklen_t addr_len;


	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

	if(clientSocket < 0)
	{
		perror("Error in opening client socket");
		exit(1);
	}

	// Setting fields in servAddr structure
	servAddr.sin_port = htons(7891);
	servAddr.sin_family = AF_INET;
	memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	addr_len = sizeof(servAddr);

	while(1)
	{
		printf("Type a sentence to send to server:\n");
		scanf("%s", buffer);

		nBytes = sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&servAddr, addr_len);

		if(nBytes < 0)
		{
			perror("Error in sending data to server");
			exit(1);
		}

		bzero(buffer, '\0');
		nBytes = recvfrom(clientSocket, buffer, 1024, 0, (struct sockaddr *)&servAddr, &addr_len);
		if(nBytes < 0)
		{
			perror("Error in recieving data from server");
			exit(1);
		}	

		printf("Message recieved from server : \t%s\n", buffer);	

	}

	return 0;
}
