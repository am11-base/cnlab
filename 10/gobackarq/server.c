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
   serveradr.sin_port=htons(8080);
   serveradr.sin_addr.s_addr=INADDR_ANY;

   bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));
   int opt = 1;
        setsockopt(server1,SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));

   listen(server1,2);

   int client1=accept(server1,NULL,NULL);
   if(client1<0)
    printf("\n Not accepted");
   int x[3];
   read(client1,x,sizeof(x));
   int data;
   do
   {
     printf("\n frame received ");
     for(int i=0;i<3;i++)
     {
       if(x[i]!=-1)
      printf(" %d ",x[i]);
    }
     printf("\n Enter the last received frame : ");

     scanf("%d",&data);
     write(client1,&data,sizeof(data));
     read(client1,x,sizeof(x));
   }while(data!=8);
   //printf("\n frame received %d",x);
     close(client1);
     close(server1);

}
