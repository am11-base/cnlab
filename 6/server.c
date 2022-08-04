#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
void main()
{
        int server_socket=socket(AF_INET,SOCK_STREAM,0);
//define the server address
        struct sockaddr_in server_address;
        server_address.sin_family=AF_INET;

        int chopstick[4];

        for(int i=0; i<5; i++)
        {
                chopstick[i]=0;
        }
        server_address.sin_port=htons(9200);
        server_address.sin_addr.s_addr=INADDR_ANY; //communication bw the same machine

//binding the socket with specified IP
        bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));

//listening for connection
        listen(server_socket,10);

        while(1)
        {
                int client_socket1= accept(server_socket,NULL,NULL);
                int message[2],philno;
                recv(client_socket1,&message,sizeof(message),0);

                philno=message[0];
                if(message[1]==1)
                {

                        if(chopstick[philno]==0 && chopstick[(philno+1)%5]==0)
                        {
                                printf("philosopher %d has obtained the chopstick \n",philno);
                                chopstick[philno]=1;
                                chopstick[(philno+1)%5]=1;
                        }

                        else
                        {
                                printf("%d cant obtain the chopstick\n",philno);
                        }

                }

                else if(message[1]==0)
                {

                        if(chopstick[philno]==1 && chopstick[(philno+1)%5]==1)
                        {
                                printf("philosopher %d has put down the chopstick \n",philno);
                                chopstick[philno]=0;
                                chopstick[(philno+1)%5]=0;
                        }
                        else
                        {
                                chopstick[philno]=0;
                                chopstick[(philno+1)%5]=0;

                        }

                }

        }
}
