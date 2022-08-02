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

        char msg[60];
        recv(client1,msg,sizeof(msg),0);
        printf(" received message is %s",msg);
        char name[20];
        scanf("%s",name);
        send(client1,name,sizeof(name),0);

        char fcon[50];
        recv(client1,fcon,sizeof(fcon),0);
        printf("\n File content: ");
        printf("%s",fcon);


        close(client1);




}
