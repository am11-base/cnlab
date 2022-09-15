#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
int bucket[5];
void* printbucket(void* _)
{
        for(int i=0; i<5; i++)
        {
                sleep(3);
                printf("\n Received packet %d",bucket[i] );
        }
}
void* server(void* _)
{
        int servfd=socket(AF_INET,SOCK_STREAM,0);
        int clientfd;
        struct sockaddr_in serv={0};
        serv.sin_family=AF_INET;
        serv.sin_port=htons(8089);
        serv.sin_addr.s_addr=INADDR_ANY;


        if(bind(servfd,(struct sockaddr*)&serv,sizeof(serv))<0)
        {
                printf("\n Binding not established");
        }
        else
        {

                listen(servfd,5);
                for(int i=1; i<=5; i++)
                {
                        clientfd=accept(servfd,NULL,NULL);
                        int x;
                        recv(clientfd,&x,sizeof(x),0);
                        //printf("%d",x );
                        bucket[i]=x;
                }

        }
        close(servfd);
        close(clientfd);
}
void main()
{
        pthread_t t1,t2;
        sleep(1);
        pthread_create(&t1,NULL,server,NULL);
        pthread_create(&t2,NULL,printbucket,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
}
