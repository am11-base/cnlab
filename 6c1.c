#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void main()
{
 int clientfd=socket(AF_INET,SOCK_STREAM,0);
 if(clientfd==-1)
  printf("\n Socket not created");
  
 struct sockaddr_in servaddr={0};
  
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(8080);
 servaddr.sin_addr.s_addr=INADDR_ANY;

 int serv=connect(clientfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
 
 if(serv==-1)
   printf("\n Connection not established");

 int choice;
 printf("\n 1.REVERSE A STRING ");
 printf("\n 2.SQUARE AN INTEGER");
 printf("\n 3.POWER A FLOAT");
 printf("\n ENTER THE CHOICE : ");
 scanf("%d",&choice);
 
 send(clientfd,&choice,sizeof(choice),0);
 if(choice==1)
  {
    char msg[10]="hello";
    printf("message sent");
    write(clientfd,msg,sizeof(msg));
    //printf("string: %s\n",msg);
  }
  if(choice==2)
  {
    int intnum=10;
    send(clientfd,&intnum,sizeof(intnum),0);
    //printf("int num: %d\n",intnum);
  }
  if(choice==3)
  {
    float floatnum=20.3;
    send(clientfd,&floatnum,sizeof(floatnum),0);
    //printf("float num : %f\n",floatnum);
  }
 close(clientfd);
 
 
}
