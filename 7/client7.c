#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
  int clientfd;
  struct sockaddr_in servaddr={0};
  if((clientfd=socket(AF_INET,SOCK_STREAM,0))<0)
  {
    printf("\n Socket Not Created" );
    exit(0);
  }
  printf("\n Socket Created" );
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(8080);
  servaddr.sin_addr.s_addr=INADDR_ANY;

  if(connect(clientfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
    printf("\nConnection Not Established" );
    exit(0);
  }
  printf("\nConnection Established" );
  while(1)
  {

    char msg[10];
    printf("\n Enter the msg: ");
    scanf("%s",msg );
    send(clientfd,msg,sizeof(msg),0);
    if(strcmp(msg,"exit")==0)
    {
      close(clientfd);
      exit(0);
    }
  }
}
