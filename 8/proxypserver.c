#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <string.h>
#include<stdlib.h>

void main()
{

   int server1=socket(AF_INET,SOCK_STREAM,0);

   struct sockaddr_in serveradr={0};
   serveradr.sin_family=AF_INET;
   serveradr.sin_port=htons(8078);
   serveradr.sin_addr.s_addr=INADDR_ANY;

   bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

   listen(server1,2);
   int client=accept(server1,NULL,NULL);

   char message[50];
   recv(client,message,sizeof(message),0);


  int clientp=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in clientadr={0};
  clientadr.sin_family=AF_INET;
  clientadr.sin_port=htons(8075);
  clientadr.sin_addr.s_addr=INADDR_ANY;


  int status=connect(clientp,(struct sockaddr*)&clientadr,sizeof(clientadr));

  if(status ==-1)
    printf("\n couldn't establish connection");

  send(clientp,message,sizeof(message),0);
  char msg1[1000];
  recv(clientp,msg1,1500,0);

  send(client,msg1,1500,0);

  close(server1);
  close(clientp);
}
