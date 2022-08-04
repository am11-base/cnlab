#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{

   int client1=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in clientadr={0};
  clientadr.sin_family=AF_INET;
  clientadr.sin_port=htons(8078);
  clientadr.sin_addr.s_addr=INADDR_ANY;


  int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

  if(status ==-1)
    printf("\n couldn't establish connection");

  char msg[]="http://www.tkmce.ac.in";
  send(client1,msg,sizeof(msg),0);
  char msg1[1000];
  recv(client1,msg1,sizeof(msg1),0);
  printf(" received message is %s ",msg1);

  close(client1);


}
