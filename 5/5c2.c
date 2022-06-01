#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
void main()
{
        int choice,squared;
        float floatnum;
        char string[100];
        int clientfd=socket(AF_INET,SOCK_STREAM,0);
        if(clientfd==-1)
                printf("\n Socket not Created");

        struct sockaddr_in servaddr={0};

        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(8080);
        servaddr.sin_addr.s_addr=INADDR_ANY;

        int serv=connect(clientfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

        if(serv==-1)
                printf("\n Connection Not established between client 2 and server");

        recv(clientfd,&choice,sizeof(choice),0);
        if(choice==1)
        {
         read(clientfd,string,sizeof(string));
         printf("\n Received String: %s",string );

        }
        else if(choice==2)
        {
          recv(clientfd,&squared,sizeof(squared),0);
          printf("\n Received integer : %d ",squared);
        }
        else if(choice==3)
        {
          recv(clientfd,&floatnum,sizeof(floatnum),0);
          printf("\n Received float : %f ",floatnum);
        }
        close(clientfd);
}
