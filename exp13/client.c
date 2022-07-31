#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdio.h>

int i=0;
void client()
{
  int clientfd=socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in serv={0};
  serv.sin_family=AF_INET;
  serv.sin_port=htons(8080);
  serv.sin_addr.s_addr=INADDR_ANY;

 int msg[5]={1,2,3,4,5};
  if(connect(clientfd,(struct sockaddr*)&serv,sizeof(serv))<0)
  {
    printf("\n Connection not established");
  }
  else
  {
    send(clientfd,&msg[i],sizeof(msg[i]),0);
    i++;

    close(clientfd);
  }
}
void main()
{
  for(int i=0;i<5;i++)
  {
    sleep(1);
    client();
  }
}
