#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <pthread.h>
#include<unistd.h>
void* getchopstick(void* arg)
{
  int num=*(int *)arg;
	int nsocket;
	nsocket=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9200);
	server_address.sin_addr.s_addr=INADDR_ANY;


	int connection_status=connect(nsocket,(struct sockaddr *) &server_address,sizeof(server_address));

	if(connection_status==-1)
	{
	printf("Error in creating connection");
	}

	int message[2];
	message[0]=num;
	message[1]=1;
	send(nsocket,message,sizeof(message),0);

	close(nsocket);

}
void* putchopstick(void* arg)
{
  int num=*(int *)arg;
	int nsocket;
	nsocket=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9200);
	server_address.sin_addr.s_addr=INADDR_ANY;


	int connection_status=connect(nsocket,(struct sockaddr *) &server_address,sizeof(server_address));
	if(connection_status==-1)
	{
	printf("Error in creating connection");
	}

	int message[2];
	message[0]=num;
	message[1]=0;
	send(nsocket,message,sizeof(message),0);

	close(nsocket);

}
void main()
{
  while(1){
	int i=0;
	pthread_t p1,p2,p3,p4,p5;
	pthread_create(&p1,NULL,getchopstick,&i);
	i++;
	pthread_create(&p2,NULL,getchopstick,&i);
	i++;
	pthread_create(&p3,NULL,getchopstick,&i);
	i++;
	pthread_create(&p4,NULL,getchopstick,&i);
	i++;
	pthread_create(&p5,NULL,getchopstick,&i);
	i++;
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	pthread_join(p5,NULL);
	i=0;
	pthread_create(&p1,NULL,putchopstick,&i);
	i++;
	pthread_create(&p2,NULL,putchopstick,&i);
	i++;
	pthread_create(&p3,NULL,putchopstick,&i);
	i++;
	pthread_create(&p4,NULL,putchopstick,&i);
	i++;
	pthread_create(&p5,NULL,putchopstick,&i);
	i++;
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	pthread_join(p5,NULL);



 }
}
