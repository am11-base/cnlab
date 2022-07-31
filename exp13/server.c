#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdio.h>
int bigmessage[5];
void* print(void* _)
{
  for(int i=0;i<5;i++)
  {
    sleep(3);
    printf("\n %d",bigmessage[i] );
  }
}
void* server(void* _)
{
  int servfd=socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in serv={0};
  serv.sin_family=AF_INET;
  serv.sin_port=htons(8080);
  serv.sin_addr.s_addr=INADDR_ANY;

 int msg[5]={1,2,3,4,5};
  if(bind(servfd,(struct sockaddr*)&serv,sizeof(serv))<0)
  {
    printf("\n Binding not established");
  }
  else
  {
    listen(servfd,5);
    for(int i=1;i<=5;i++)
    {
      int clientfd=accept(servfd,NULL,NULL);
      int x;
      recv(clientfd,&x,sizeof(x),0);
      printf("%d",x );
      bigmessage[i]=x;
    }

  }
  close(servfd);
  close(clientfd);
}
void main()
{
  pthread_t t1,t2;
  sleep(1);
  pthread_create(&t1,NULL,server,NULL);
  pthread_create(&t2,NULL,print,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
}
