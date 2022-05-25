#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main()
{
   char buffer[100];
   
   char message[]="helloam11";
   int server1=socket(AF_INET,SOCK_STREAM,0);

   struct sockaddr_in serveradr={0};
   serveradr.sin_family=AF_INET;
   serveradr.sin_port=htons(8080);
   serveradr.sin_addr.s_addr=INADDR_ANY;

   bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

   listen(server1,2);

   int client1=accept(server1,NULL,NULL);

   int n=read(client1,buffer,strlen(buffer));
   printf("%s",buffer );

}
