#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include <time.h>
#include<stdlib.h>
//#include<process.h>
void main()
{
  int servfd=socket(AF_INET,SOCK_DGRAM,0);
  if(servfd<0)
  {
    printf("\n Socket not Created");
    exit(0);
  }
  struct sockaddr_in serv={0};
  serv.sin_family=AF_INET;
  serv.sin_port=htons(8081);
  serv.sin_addr.s_addr=INADDR_ANY;

  if((bind(servfd,(struct sockaddr*)&serv,sizeof(serv)))<0)
  {
    printf("\n not binded not Created");
    exit(0);
  }

  struct sockaddr_in client={0};

  while(1){
    //pid_t child;
    //if((child=fork())==0)
    //{

      int len=sizeof(client);
      char buffer[20];
      recvfrom(servfd,buffer,20,0,(struct sockaddr*)&client,&len);
      printf("\n%s",buffer);
      if(strcmp(buffer,"timerequest")==0)
      {
        time_t mytime = time(NULL);
        char * time_str = ctime(&mytime);
        time_str[strlen(time_str)-1] = '\0';
        printf("%s",time_str);
        sendto(servfd,time_str,100,0,(struct sockaddr*)&client,len);
      }
      else
       sendto(servfd,"Not able to process",100,0,(struct sockaddr*)&client,len);
    //}
  }


}
