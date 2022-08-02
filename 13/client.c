#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{

   int client1=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in clientadr={0};
  clientadr.sin_family=AF_INET;
  clientadr.sin_port=htons(8080);
  clientadr.sin_addr.s_addr=INADDR_ANY;


  int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));


  if(status ==-1)
    printf("\n couldn't establish connection");

  char msg[60];
  recv(client1,msg,sizeof(msg),0);
  printf(" received message is %s",msg);
  int x;
  scanf("%d",&x);
  send(client1,&x,sizeof(x),0);
  if(x==1)
  {
    char command1[20],command2[20];
    char mailid[20],mail[20];
    recv(client1,command1,sizeof(command1),0);
    printf("%s",command1);
    scanf("%s",mailid);
    send(client1,mailid,sizeof(mailid),0);
    recv(client1,command2,sizeof(command2),0);
    printf("%s",command2);
    scanf("%s",mail);
    send(client1,mail,sizeof(mail),0);

  }



}
