a#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
  int servfd;
  struct sockaddr_in servaddr={0};
  if((servfd=socket(AF_INET,SOCK_STREAM,0))<0)
  {
    printf("\n Socket Not Created" );
    exit(0);
  }
  printf("\n Socket Created" );
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(8080);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  if(bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
  {
    printf("\n Binding not Successfull");
    exit(0);
  }
  printf("\n Binding Successfull");
  listen(servfd,5);
  while(1)
  {
    int new=accept(servfd,NULL,NULL);
    if(new<0)
    {
      printf("\n Connection not accepted");
      exit(0);
    }
    pid_t child;
    if((child=fork())==0)
    {
        close(servfd);
      while(1)
      {
        char msg[10];
        recv(new,msg,sizeof(msg),0);
        printf("\n Client: %s",msg );
        if(strcmp(msg,"exit")==0)
         exit(0);
        bzero(msg,sizeof(msg));

      }

    }
  }

}
