#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
int server_fd,new_socket;
int opt =1;
long valread;
struct sockaddr_in address;
int addrlen = sizeof(address);

char *xerxes = "Hey from Xer server";

//creating socket file descriptor
if((server_fd = socket(AF_INET, SOCK_STREAM,0)) == 0)
{
perror("socket failed");
exit(EXIT_FAILURE);
}

if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
{
perror("setsockopt");
exit(EXIT_FAILURE);
}

address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);

memset(address.sin_zero, '\0', sizeof(address.sin_zero));

if (bind(server_fd,(struct sockaddr *)&address, sizeof(address))<0)
{
perror("bind failed");
exit(EXIT_FAILURE);
}

if(listen(server_fd,4)<0)
{
perror("In listen");
exit(EXIT_FAILURE);
}

while(1)
{
printf("\nWaiting for connection\n\n");

if((new_socket = accept(server_fd,(struct sockaddr *)&address, (socklen_t *)&addrlen))<0)
{
perror("In accept");
exit(EXIT_FAILURE);
}
send(new_socket, xerxes, strlen(xerxes),0);
printf("Message from server sent\n");
char buffer[30000] = {0};
valread = read( new_socket, buffer, 30000);
printf("%s\n",buffer);
close(new_socket);
}

return 0;
}