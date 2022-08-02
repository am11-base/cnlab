#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 10


void Dijkstra(int cost[MAX][MAX], int n, int start,int end) {
        int distance[MAX], pred[MAX];
        int visited[MAX], count, mindistance, nextnode, i, j;



        for (i = 0; i < n; i++) {
                distance[i] = cost[start][i];
                pred[i] = start;
                visited[i] = 0;
        }

        distance[start] = 0;
        visited[start] = 1;
        count = 1;

        while (count < n - 1) {
                mindistance = 999;

                for (i = 0; i < n; i++)
                        if (distance[i] < mindistance && !visited[i]) {
                                mindistance = distance[i];
                                nextnode = i;
                        }

                visited[nextnode] = 1;
                for (i = 0; i < n; i++)
                        if (!visited[i])
                                if (mindistance + cost[nextnode][i] < distance[i]) {
                                        distance[i] = mindistance + cost[nextnode][i];
                                        pred[i] = nextnode;
                                }
                count++;
        }
        printf("\nDistance from %d to %d: %d(through %d)", start,end,distance[end],pred[end]);


}
int main()
{
        int Graph[MAX][MAX],n;

        printf("Enter the number of nodes: ");
        scanf("%d",&n);
        printf("Enter the cost matrix(999 if no edge)\n");

        for(int i=0; i<n; i++)
        {
                for(int j=0; j<n; j++)
                        scanf("%d",&Graph[i][j]);
        }




        int client1=socket(AF_INET,SOCK_STREAM,0);
        struct sockaddr_in clientadr={0};
        clientadr.sin_family=AF_INET;
        clientadr.sin_port=htons(8080);
        clientadr.sin_addr.s_addr=INADDR_ANY;


        int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

        if(status ==-1)
                printf("\n couldn't establish connection");

        char msg[50];
        sprintf(msg,"Number of nodes is %d.Enter the two nodes:",n);

        send(client1,&msg,sizeof(msg),0);
        int array1[2];
        read(client1,array1,sizeof(array1));
        printf("\nreceived message is %d %d ",array1[0],array1[1]);

        Dijkstra(Graph, n, array1[0],array1[1]);
        //printf("\nShortest distance from %d to %d is %d through %d");
        return 0;
}
