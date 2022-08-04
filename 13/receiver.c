#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
void main()
{
        int server_socket=socket(AF_INET,SOCK_STREAM,0);
        char message[20];
        struct sockaddr_in server;
        server.sin_family=AF_INET;
        server.sin_port=htons(9095);
        server.sin_addr.s_addr=INADDR_ANY;


        int id=2;

        int binding=bind(server_socket,(struct sockaddr*) &server,sizeof(server));
        listen(server_socket,1);

        int client_id=accept(server_socket,NULL,NULL);
        recv(client_id,message,sizeof(message),0);
        printf("%s",message);
        close(server_socket);


}
