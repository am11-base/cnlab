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
        clientadr.sin_port=htons(8080);
        clientadr.sin_addr.s_addr=INADDR_ANY;


        int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

        if(status ==-1)
                printf("\n couldn't establish connection");

        int a[9]={0,1,2,3,4,5,6,7,8};
        int x[4];
        int size=3;
        int i=0,count=3;
        while(1)
        {
                //  printf("\n Sending %d package ",i);
                int flag=0;
                int arr[3],k=0;
                for(int i=1; i<=3-count; i++)
                {
                        arr[k]=x[i];
                        k++;
                }
                for(int j=k; j<3; j++)
                {
                        if(i>=9)
                                break;
                        arr[k]=a[i];
                        i++;

                        //printf("sending %d",arr[k]);
                        k++;
                }
                if(k<3)
                {
                        for(int i=k; i<3; i++)
                                arr[i]=-1;
                }
                printf("\n Sending");
                for(int i=0; i<3; i++)
                        printf("%d",arr[i]);

                if(i>=9)
                {
                        flag=1;
                        write(client1,arr,sizeof(arr));
                        send(client1,&flag,sizeof(flag),0);
                        exit(0);
                }
                write(client1,arr,sizeof(arr));
                send(client1,&flag,sizeof(flag),0);

                recv(client1,x,sizeof(x),0);
                count=3-x[0];

        }
        close(client1);

}
