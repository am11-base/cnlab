#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
   char message[50];
   int server1=socket(AF_INET,SOCK_STREAM,0);

   struct sockaddr_in serveradr={0};
   serveradr.sin_family=AF_INET;
   serveradr.sin_port=htons(8080);
   serveradr.sin_addr.s_addr=INADDR_ANY;
   int opt = 1;
        setsockopt(server1,SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));

   bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

   listen(server1,2);

   int client1=accept(server1,NULL,NULL);

   recv(client1,message,sizeof(message),0);
   printf("%s",message );
   int ar[2];
   scanf("%d %d",&ar[0],&ar[1]);
   write(client1,ar,sizeof(ar));
}
