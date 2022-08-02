#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
void main()
{

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
        {
                printf("\n Connection not accepted");
                exit(0);
        }


        char message[]={"Welcome to SMTP Server.\n 1.Compose 2.Exit Choose an option:"};
        send(client1,message,sizeof(message),0);
        int x;
        recv(client1,&x,sizeof(x),0);
        if(x==1)
        {

                char message1[]={"Enter the mail id: "};
                send(client1,message1,sizeof(message1),0);
                char mailid[20];
                recv(client1,mailid,sizeof(mailid),0);
                char message2[]={"Enter the message: "};
                send(client1,message2,sizeof(message2),0);
                char mailmsg[20];
                recv(client1,mailmsg,sizeof(mailmsg),0);
                int inc;
                if(strcmp(mailid,"test@gmail.com")==0)
                 inc=0;
                else
                 inc=1;
                int server_socket2=socket(AF_INET,SOCK_STREAM,0);

                struct sockaddr_in serveradd1;
                serveradd1.sin_family=AF_INET;
                serveradd1.sin_port=htons(9091+inc);
                serveradd1.sin_addr.s_addr=INADDR_ANY;

                int connection=connect(server_socket2,(struct sockaddr *) &serveradd1,sizeof(serveradd1));
                send(server_socket2,mailmsg,sizeof(mailmsg),0);
                close(server_socket2);


        }
        close(server1);


}
