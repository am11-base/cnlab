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
        int i;
        printf("Enter the number of clients : ");
        scanf("%d",&i);


        while(i>0){
        int client1=accept(server1,NULL,NULL);

        pid_t child;
        if((child=fork())==0)
        {
        close(server1);
        int pid=getpid();
        char message[]={"Welcome to FTP Server.\n Enter the filename:"};
        send(client1,message,sizeof(message),0);
        char fname[20];
        bzero(fname,sizeof(fname));
        recv(client1,fname,sizeof(fname),0);
        char content[100];
        bzero(content,sizeof(content));
        FILE *fp;

        fp=fopen(fname,"r");
        if(access(fname,F_OK)==0)
        {
                fgets(content, 100, fp);
        }
        else
                strcpy(content,"File not found");
        send(client1,content,sizeof(content),0);
        char process[20];
        sprintf(process,"Process id : %d",pid);
        send(client1,process,sizeof(process),0);


        }
        else
         i--;
      }




}
