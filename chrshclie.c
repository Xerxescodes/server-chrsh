#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
int sock = 0;
long valread;
char buffer[30000] = {0};
struct sockaddr_in serv_addr;
char *xer = "Hey from Client";

if ((sock = socket(AF_INET, SOCK_STREAM, 0))<0)
{
printf("socket creation error\n");
return -1;
}

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);

if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
{
printf("Invalid address/ Address not allowed\n");
return -1;
}

if (connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
{
printf("connection failure!!!\n");
return -1;
}
send(sock, xer, strlen(xer),0);
printf("Message from client sent\n");
valread = read( new_socket, buffer, 30000);
printf("%s\n",buffer);
close(sock);

return 0;
}