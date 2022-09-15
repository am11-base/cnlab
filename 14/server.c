#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void main()
{

        int server1=socket(AF_INET,SOCK_STREAM,0);

        struct sockaddr_in serveradr={0};
        serveradr.sin_family=AF_INET;
        serveradr.sin_port=htons(8081);
        serveradr.sin_addr.s_addr=INADDR_ANY;

        int opt = 1;
        setsockopt(server1,SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));

        bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

        listen(server1,2);

        struct sockaddr_in client_addr;
        socklen_t client_len;

        int client1=accept(server1,(struct sockaddr*)&client_addr,&client_len);
        if(client1<0)
        {
                printf("\n Connection not accepted");
                exit(0);
        }


        char message[]={"Welcome to FTP Server.\n 1.Upload 2.Download "};
        send(client1,message,sizeof(message),0);
        int opt1;
        recv(client1,&opt1,sizeof(opt),0);
        char message2[]={"Enter file name : "};
        send(client1,message2,sizeof(message2),0);
        char fname[20];
        recv(client1,fname,sizeof(fname),0);
        char content[50];
        FILE *fp;

        if(opt1==2){
        fp=fopen(fname,"r");
        if(access(fname,F_OK)==0)
        {
                fgets(content, 50, fp);
        }
        else
                strcpy(content,"File not found");
        send(client1,content,sizeof(content),0);
      }
      else
      {
        fp=fopen(fname,"w");
        char command[]={"Enter the file content"};
        send(client1,command,sizeof(command),0);
        char content[30];
        recv(client1,content,sizeof(content),0);
        fputs(content,fp);
      }

        close(server1);

        close(client1);




}
