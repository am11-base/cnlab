#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
struct node
{
        unsigned dist[20];
        unsigned from[20];
} rt[10];
int main()
{
        int costmat[20][20];
        int nodes,i,j,k,count=0;
        printf("\nEnter the number of nodes : ");
        scanf("%d",&nodes);//Enter the nodes
        printf("\nEnter the cost matrix :\n");
        for(i=0; i<nodes; i++)
        {
                for(j=0; j<nodes; j++)
                {
                        scanf("%d",&costmat[i][j]);
                        costmat[i][i]=0;
                        rt[i].dist[j]=costmat[i][j];//initialise the distance equal to cost matrix
                        rt[i].from[j]=j;
                }
        }
        do
        {
                count=0;
                for(i=0; i<nodes; i++) //We choose arbitary vertex k and we calculate the direct distance from the node i to k using the cost matrix
                        //and add the distance from k to node j
                        for(j=0; j<nodes; j++)
                                for(k=0; k<nodes; k++)
                                        if(rt[i].dist[j]>costmat[i][k]+rt[k].dist[j])
                                        {//We calculate the minimum distance
                                                rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
                                                rt[i].from[j]=k;
                                                count++;
                                        }
        } while(count!=0);

        int client1=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in clientadr={0};
        clientadr.sin_family=AF_INET;
        clientadr.sin_port=htons(8085);
        clientadr.sin_addr.s_addr=INADDR_ANY;


        int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

        if(status <0)
                printf("\n couldn't establish connection");

        char msg[50];
        sprintf(msg,"Number of nodes is %d.Enter the two nodes:",nodes);

        send(client1,&msg,sizeof(msg),0);
        int array1[2];
        read(client1,array1,sizeof(array1));
        printf("\nreceived message is %d %d ",array1[0],array1[1]);
        printf("\nShortest distance from %d to %d is %d through %d",array1[0],array1[1],rt[array1[0]].dist[array1[1]],rt[array1[0]].from[array1[1]]);
        close(client1);

}
