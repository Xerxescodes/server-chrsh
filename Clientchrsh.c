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

for (;;){
bzero(chrsh, MAX);
read(sockfd, chrsh, sizeof(chrsh));

printf("Enter message:");
n = 0;
while((chrsh[n++] = getchar())!='\n');

write(sockfd, chrsh, sizeof(chrsh));
bzero(chrsh,sizeof(chrsh));
read(sockfd,chrsh,sizeof(chrsh));
printf("From Server: %s",chrsh);

if(strcmp(chrsh,"exit",4)==0){
printf("Client Exit.....\n");
break;
}}}

int main()
{
int sockfd,connfd;
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

if(connect(sockfd, (XR*)&servaddr, sizeof(servaddr))!=0){
printf("Connection to server failed..!!");
exit(0);
}else
printf("Connected to server successfully!");

func(sockfd);
close(sockfd);
}

return 0;
}