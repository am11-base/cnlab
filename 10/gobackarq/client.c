#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{

   int client1=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in clientadr={0};
  clientadr.sin_family=AF_INET;
  clientadr.sin_port=htons(8083);
  clientadr.sin_addr.s_addr=INADDR_ANY;


  int status=connect(client1,(struct sockaddr*)&clientadr,sizeof(clientadr));

  if(status ==-1)
    printf("\n couldn't establish connection");

  int a[9]={0,1,2,3,4,5,6,7,8};
  int size=3;
  int i=0;
  while(i!=9)
  {
    printf("\n Sending %d package ",i);
    int arr[3],k=0;
    for(int j=i;j<(i+3);j++)
    {
      if(j>=9)
       break;
      arr[k]=a[j];
      printf("%d",arr[k]);
      k++;
    }
    if(k<3)
    {
      for(int i=k;i<3;i++)
       arr[i]=-1;
    }
    write(client1,arr,sizeof(arr));
    int x;
    recv(client1,&x,sizeof(x),0);
    i=x+1;

  }
  close(client1);

}
