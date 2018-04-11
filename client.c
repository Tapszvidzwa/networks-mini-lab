#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#define size 256



int main(int argc, const char * argv[]){

 //read input from the client
 char msg[size];

//get the input
 if(fgets(msg, size, stdin) == NULL) {
    perror("Something wrong with read\n");
 }
	//sets up ip address
	struct hostent* server = gethostbyname(argv[1]);
	if(server == NULL) {
		fprintf(stderr, "Unable to find host %s\n", argv[1]);
		exit(1);
	}
//sets up socket
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if(s == -1) {
		perror("socket failed");
		exit(2);
	}

//initialize socket address
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(4443)
	};

//specify address
	bcopy((char*)server->h_addr, (char*)&addr.sin_addr.s_addr, server->h_length);

//connect to server
	if(connect(s, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) {
		perror("connect failed");
		exit(2);
	}

//write to the server
write(s, msg, strlen(msg));

//read from server
	char buffer[256];
	int bytes_read = read(s, buffer, 256);
	if(bytes_read < 0) {
		perror("read failed");
		exit(2);
	}

	printf("Server sent: %s\n", buffer);

	close(s);
}