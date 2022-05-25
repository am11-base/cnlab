#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main()
{
  //socket creation
  int server=socket(AF_INET,SOCK_DGRAM,0);
  if(server<0)
   printf("\n Error in creation of Socket");
  else
  {
    char buffer[100];
    struct sockaddr_in serveraddr={0};
    struct sockaddr_in clientaddr={0};

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(8080);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    bind(server,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    int len=sizeof(clientaddr);

    recvfrom(server,buffer,100,0,(struct sockaddr*)&clientaddr,&len);
    printf("received from client : %s",buffer );
    strcat(buffer,"is received");
    sendto(server,buffer,100,0,(struct sockaddr*)&clientaddr,len);

  }
}
