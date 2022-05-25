#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<math.h>
void reverse(char string[100],char rev[100])
{
  int len=strlen(string),k=0;
  for(int i=len-1;i>=0;i++)
  {
   rev[k]=string[i];
   k++;
  }
 
}
void main()
{
  char msg[100],revmsg[100];
  float floatnum,newnum;
  int choice,intnum,squared;
  int servfd=socket(AF_INET,SOCK_STREAM,0);
  if(servfd==-1)
   printf("\nSocket not created");
  struct sockaddr_in servaddr={0};
  
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(8080);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  
  bind(servfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

  listen(servfd,2);

  int client1=accept(servfd,NULL,NULL);
  if(client1==-1)
   printf("\n Couldn't find client");
  recv(client1,&choice,sizeof(choice),0);
  printf("choice from client1: %d\n",choice);
  if(choice==1)
  {
   
    read(client1,msg,sizeof(msg));
    printf("string: %s\n",msg);
    reverse(msg,revmsg);
  }
  if(choice==2)
  {
    recv(client1,&intnum,sizeof(intnum),0);
    printf("int num: %d\n",intnum);
    squared=intnum*intnum;
  }
  if(choice==3)
  {
    recv(client1,&floatnum,sizeof(floatnum),0);
    printf("float num : %f\n",floatnum);
    newnum=pow(floatnum,1.5);
  }

  
  int client2=accept(servfd,NULL,NULL);
  
  if(client2==-1)
   printf("\n Couldn't find client");
  if(choice==1)
  {
    write(client2,revmsg,sizeof(revmsg));
    //printf("string: %s\n",msg);
  }
  if(choice==2)
  {
 
    send(client2,&squared,sizeof(squared),0);
    //printf("int num: %d\n",intnum);
  }
  if(choice==3)
  {
    
    send(client2,&newnum,sizeof(newnum),0);
    //printf("float num : %f\n",floatnum);
  }
  


}
