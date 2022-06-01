#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
void calculate(int a[],int n,float array[3])
{
 int max=a[1],min=a[1],sum=a[1];
 for(int i=2;i<=n;i++)
 {
   if(a[i]>max)
     max=a[i];
   if(a[i]<min)
    min=a[i];
   sum+=a[i];

 }
 float avg=(float)sum/n;
/* printf("max : %d",max);
 printf("min : %d",min);
 printf("avg : %.2f",avg);*/

 array[0]=(float)min;
 array[1]=(float)max;
 array[2]=(float)avg;
}
void main()
{
  int buffer[100];
  int servfd=socket(AF_INET,SOCK_DGRAM,0);
  if(servfd == -1)
     printf("\n SOCKET NOT CREATED");
  
  struct sockaddr_in servaddr={0};
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(8080);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  
  bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
 
  struct sockaddr_in clientadr={0};
  int len1=sizeof(clientadr);
  int n=recvfrom(servfd,buffer,sizeof(buffer),0,(struct sockaddr*)&clientadr,&len1);
  int len=buffer[0];
 // printf("size= %d",len);
  printf("array from client :");
  for(int i=1;i<=len;i++)
    printf(" %d ",buffer[i]);

  float array1[3];
  calculate(buffer,len,array1);
  sendto(servfd,array1,sizeof(array1),0,(struct sockaddr*)&clientadr,len1);
}






























