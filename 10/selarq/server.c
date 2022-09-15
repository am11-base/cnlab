#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<stdlib.h>
void main()
{
    
        int server1=socket(AF_INET,SOCK_STREAM,0);

        struct sockaddr_in serveradr={0};
        serveradr.sin_family=AF_INET;
        serveradr.sin_port=htons(8084);
        serveradr.sin_addr.s_addr=INADDR_ANY;

        bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

        listen(server1,2);

        int client1=accept(server1,NULL,NULL);
        if(client1<0)
                printf("\n Not accepted");
        int x[3],flag=0;
        read(client1,x,sizeof(x));
        recv(client1,&flag,sizeof(flag),0);
        do
        {
                int nack[4],k=0;
                printf("\n frame received \n");
                for(int i=0; i<3; i++)
                {
                        if(x[i]!=-1) {
                                printf(" packet %d ",x[i]);
                                int ack;
                                printf(" Enter the aknowledgement(1/-1): ");
                                scanf("%d",&ack);
                                if(ack==-1)
                                {
                                        nack[++k]=x[i];
                                }
                        }
                }
                nack[0]=k;

                //printf("\n Enter the last received frame : ");
                if(flag==1)
                {
                  exit(0);
                }
                //scanf("%d",&data);
                write(client1,nack,sizeof(nack));
                read(client1,x,sizeof(x));
                recv(client1,&flag,sizeof(flag),0);

        } while(1);
        //printf("\n frame received %d",x);
        close(client1);
        close(server1);

}
