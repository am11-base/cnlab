#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main()
{
   char buffer[100];

   char message[]="helloam11";
   int server1=socket(AF_INET,SOCK_STREAM,0);

   struct sockaddr_in serveradr={0};
   serveradr.sin_family=AF_INET;
   serveradr.sin_port=htons(8082);
   serveradr.sin_addr.s_addr=INADDR_ANY;

   bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

   listen(server1,2);

   int client1=accept(server1,NULL,NULL);
   int x;
   recv(client1,&x,sizeof(x),0);
   do
   {
     printf("\n frame received %d",x);
     printf("\n Enter the last received frame : ");
     int data;
     scanf("%d",&data);
     send(client1,&data,sizeof(data),0);
     recv(client1,&x,sizeof(x),0);
   }while(x!=9);
   printf("\n frame received %d",x);
     close(client1);
     close(server1);

}
