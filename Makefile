CC = clang
CFLAGS = -g
ROOT = .
all: server client


clean:
	rm -f server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c



client: client.c
	$(CC) $(CFLAGS) -o client client.c