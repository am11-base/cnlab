#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main()
{
  int clientfd=socket(AF_INET,SOCK_DGRAM,0);
  if(clientfd<0)
   printf("\n Error in creating client socket");
  struct sockaddr_in servaddr={0};
   
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(8080);
  servaddr.sin_addr.s_addr=INADDR_ANY;

 int len=sizeof(servaddr);
 
   printf("msg sent to server\n");
   float array1[3];
   int msg[5]={4,1,2,3,4};
   sendto(clientfd,msg,sizeof(msg),0,(struct sockaddr*)&servaddr,len);
   recvfrom(clientfd,array1,sizeof(array1),0,(struct sockaddr*)&servaddr,&len);
   printf("max : %.2f\n",array1[1]);
   printf("min : %.2f\n",array1[0]);
   printf("avg : %.2f\n",array1[2]);

  
}
