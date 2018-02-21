/*
If a server is implemented with many child processes to handle the incomming client requests using the fork() system call,
make sure to use write() function instead of the printf() function. printf() is buffered, it groups the outputs of a process
and then prints out on the monitor. So, if a child process also uses printf along with it's parent, both the outputs could
get mixed up in wierd ways. So use the unbuffered write() function
More - http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html

*/


#include<stdio.h>
#include<sys/socket.h> 
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h> // for hton and ntoh functions
#include<netdb.h>

int main()
{

	struct sockaddr_in serv_addr, cli_addr, len;
	char buffer[1024], serv_to_cli[] = "Recieved your message!\n";
	int sockfd, portno, new_sockfd, clilen, n;


	/* this structure contains information about server's address. The fields in it are:(sin = short int)
	1. sin_address : families of addresses - AF_INET(IPv4), AF_UNIX, AF_INET6(IPv6), etc
	2. sin_port : 16 byte service port number in Network Byte order - use htons() function to convert to Network Byte order
	3. sin_addr : 32 byte IP address in Network Byte order, use INADDR_ANY to bind to Local Host(127.0.0.1)
	3. unsigned char sin_zero[8] - set it to NULL, it's not being used. Set the whole structure to NULL initially using bzero()
	bzero((char *) &serv_addr, sizeof(serv_addr));
	*/

	sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket(int domain, int type, int protocol)
	/* socket returns a file descriptor
	1. domain - family of communication - AF_INET, AF_UNIX, etc. Domain is defined in <sys/socket.h>
	2. type - type of socket - SOCK_STREAM(tcp), SOCK_DGRAM(udp), SOCK_RAW(raw), etc
	3. protocol - what protocol to be used with the type of socket. Usually only one protocol exists for the given type of 
	socket in the specified family(which is why 0 is used). The only valid values for tcp are 0 and IPPROTO_TCP; for UDP - 0
	and IPPROTO_UDP
	*/

	if(sockfd<0)
	{
		perror("Error in opening socket");
		exit(1);
	}

	portno = 5001;

	/*
	void bzero(void* s, int nbytes); - places n NULL bytes in the string given by s. This function is used to set all socket 
	values to NULL values.
	*/

	bzero((char *) &serv_addr, sizeof(serv_addr)); // DOUBT: serv_addr is a structure, why is it type-casted to char* ?

	serv_addr.sin_port = htons(portno);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; // special format than the other fields !! - IMP
	/*
	1. INADDR_ANY is a constant with value = 0. It's used to set the machine to listen/bind at all local interfaces of host 
	machines IP address.
	2. INADDR_ANY is used when we bind the socket to all IP address of the machine. How many IP's can a machine have?

	DOUBT: what are local interfaces?? 
	*/

	/*
	htnos, htnol, ntohl, ntohs : s = short, l = long
	These functions are defined in <arpa/inet.h>
	hton = host to network byte order
	ntoh = network to host byte order
	*/

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Error in binding");
		exit(1);
	}

	/*
	bind = assigning a name to the socket
	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); - returns 0 on success, -1 in error
	*/

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	/*
	listen - marks the socket as a passive one. The socket is used to accept connections using accept function
	int listen(int sockfd, int backlog); - returns 0 on success, -1 on error
	sockfd = file descriptor of the socket
	backlog = maximum length of the waiting queue. Clients may recieve ECONNREFUSED if backlog limit is reached
	*/

	new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if(new_sockfd < 0)
	{
		perror("Error in accept");
		exit(1);
	}
	/*
	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); - returns new socket file descriptor
	this function creates a new socket, the old sockfd is not affected by this call - for listening from client
	the last two arguments pertain to the client's sockaddr_in structure
	*/

	n = read(new_sockfd, buffer, 1024);

	/*
	read and write is declared in <unistd.h>
	int read(int sockfd, void* buf, int count); - returns number of characters read
	sockfd = socket file descriptor
	buf = storage for recieved message
	count = number of bytes to read
	*/

	if(n < 0)
	{
		perror("Error in reading from client");
		exit(1);
	}

	printf("Message recieved from client: \t%s\n", buffer);

	n = write(new_sockfd, serv_to_cli, strlen(serv_to_cli));

	if(n < 0)
	{
		perror("Error in writing to client");
		exit(1);
	}

	close(sockfd);

	return 0;

}
