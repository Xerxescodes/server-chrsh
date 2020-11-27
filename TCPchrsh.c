#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define MAX 80
#define PORT 8080
#define XR struct sockaddr
int clientno =0;

void func(int sockfd)
{
char chrsh[MAX];
int i;
clientno++;

for (;;){
bzero(chrsh, MAX);
read(sockfd, chrsh, sizeof(chrsh));

printf("Client %d",&clientno,"says: %s\t To client :",chrsh);
bzero(chrsh, MAX);
n = 0;

while((chrsh[n++] = getchar())!='\n');
write(sockfd, chrsh, sizeof(chrsh));

if(strcmp("exit",chrsh,4)==0){
printf("Server Exit.....\n");
break;
}}}

int main()
{
int sockfd,connfd,len;
struct sockaddr_in servaddr, cli;

if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == 0)
{
perror("socket failed");
exit(0);
}else
printf("Socket successfully created...\n");
bzero(&servaddr, sizeof(servaddr));

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = hton1(INADDR_ANY);
servaddr.sin_port = htons(PORT);

if (bind(sockfd,(XR*)&servaddr, sizeof(servaddr))<0)
{
perror("bind failed");
exit(0);
}else
printf("Socket successfully binded...\n");

if(listen(sockfd,4)<0)
{
perror("In listen");
exit(0);
}else
printf("Server listening......");

len = sizeof(cli);
while(1)
{
printf("\nWaiting for connection\n\n");

if(connfd = accept(sockfd,(XR*)&cli,&len)<0)
{
perror("In accept");
exit(0);
}else
printf("Client connected successfully");
func(connfd);
close(sockfd);
}

return 0;
}