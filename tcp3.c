#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
   char message[]="hello";
   int server1=socket(AF_INET,SOCK_STREAM,0);
   
   struct sockaddr_in serveradr={0};
   serveradr.sin_family=AF_INET;
   serveradr.sin_port=htons(9090);
   serveradr.sin_addr.s_addr=INADDR_ANY;
    
   bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

   listen(server1,2);

   int client1=accept(server1,NULL,NULL);

   send(client1,message,sizeof(message),0);


}
