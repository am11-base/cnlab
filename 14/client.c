#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdlib.h>
void main()
{

        int client1=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in clientadr={0};
        clientadr.sin_family=AF_INET;
        clientadr.sin_port=htons(8081);
        clientadr.sin_addr.s_addr=INADDR_ANY;


        int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

        if(status<0){
                printf("\n couldn't establish connection");
                exit(0);
              }

        char msg[60],msg2[60];
        int opt;
        recv(client1,msg,sizeof(msg),0);
        printf(" received message is %s",msg);
        scanf("%d",&opt);
        getchar();
        send(client1,&opt,sizeof(opt),0);
        recv(client1,msg2,sizeof(msg),0);
        printf(" received message is %s",msg2);
        char name[20];
        scanf("%s",name);
        getchar();
        send(client1,name,sizeof(name),0);


        if(opt==2){
        char fcon[50];
        recv(client1,fcon,sizeof(fcon),0);
        printf("\n File content: ");
        printf("%s",fcon);
      }
      else
      {
        char writecon[20];
        printf("\n Enter content: ");
        fgets(writecon,20,stdin);
        send(client1,writecon,sizeof(writecon),0);
      }

        close(client1);




}
