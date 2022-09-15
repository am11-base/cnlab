#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{

   int client1=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in clientadr={0};
  clientadr.sin_family=AF_INET;
  clientadr.sin_port=htons(8082);
  clientadr.sin_addr.s_addr=INADDR_ANY;


  int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

  if(status ==-1)
    printf("\n couldn't establish connection");

  int a[10]={0,1,2,3,4,5,6,7,8,9};
  int i=0;
  while(i!=10)
  {
    printf("\n Sending %d package ",i);
    send(client1,&a[i],sizeof(a[i]),0);
    int x;
    recv(client1,&x,sizeof(x),0);
    if(x==i)
     i++;
    else
    i=x+1;

  }
  close(client1);

}
