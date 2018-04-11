#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

int main() {

//creates a socket
int s = socket(AF_INET, SOCK_STREAM, 0);

//check if it fails to create
if(s == -1) {
  perror("socket failed");
  exit(2);
}

//set up an internet socket address where server listens to 
struct sockaddr_in addr;
addr.sin_addr.s_addr = INADDR_ANY;
addr.sin_family = AF_INET;
addr.sin_port = htons(4443);

//bind socket to address
if(bind(s, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) {
  perror("bind failed");
  exit(2);
}

//begin listening
if(listen(s, 2)) {
  perror("listen failed");
  exit(2);
}

//accept an incoming connection
struct sockaddr_in client_addr;
socklen_t client_addr_length = sizeof(struct sockaddr_in);
int client_socket = accept(s, (struct sockaddr*)&client_addr, &client_addr_length);

if(client_socket == -1) {
  perror("accept failed");
  exit(2);
}

//read from client
char buffer[256];
	int bytes_read = read(client_socket, buffer, 256);
	if(bytes_read < 0) {
		perror("read failed");
		exit(2);
	}

for(int i = 0; i < strlen(buffer); i++){
	buffer[i] = toupper(buffer[i]);
}

//send message back to client
write(client_socket, buffer, strlen(buffer));

close(client_socket);
close(s);

}


