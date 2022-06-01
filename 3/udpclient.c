#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
  //socket creation
  int client=socket(AF_INET,SOCK_DGRAM,0);
  if(client<0)
   printf("\n Error in creation of Socket");
  else
  {
    char buffer[100];
    struct sockaddr_in serveraddr={0};


    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(8080);
    serveraddr.sin_addr.s_addr=INADDR_ANY;


    int len=sizeof(serveraddr);

    sendto(client,"helloda",100,0,(struct sockaddr*)&serveraddr,len);
    printf("message sent to server \n");
    recvfrom(client,buffer,100,0,(struct sockaddr*)&serveraddr,&len);

    printf("message received from server: %s\n",buffer);
  }
}
