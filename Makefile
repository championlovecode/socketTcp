##by pa fone 2011.02.21
all:server client clent_un
	echo "pafone make "
server: socket_server.o
	gcc -o server socket_server.o
client: socket_client.o
	gcc -o client socket_client.o

clent_un:clent_un.o
	gcc -o un clent_un.o

%.o:%.c
	gcc -c $< -o $@
clean:
	rm -f server client *.o

