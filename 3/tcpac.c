#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
    bzero(buffer,256);
   int client1=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in clientadr={0};
  clientadr.sin_family=AF_INET;
  clientadr.sin_port=htons(8080);
  clientadr.sin_addr.s_addr=INADDR_ANY;


  int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

  if(status ==-1)
    printf("\n couldn't establish connection");

  char msg="ameen";
  int n=write(status,"ameen",strlen(msg));


}
