#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <string.h>
#include<stdlib.h>
#include <curl/curl.h>
size_t static curl_write(void *buffer, size_t size, size_t nmemb, void *userp)
{
     userp += strlen(userp);  // Skipping to first unpopulated char
     memcpy(userp, buffer, nmemb);  // Populating it.
     return nmemb;
}
void main()
{
   char message[50];
   int server1=socket(AF_INET,SOCK_STREAM,0);

   struct sockaddr_in serveradr={0};
   serveradr.sin_family=AF_INET;
   serveradr.sin_port=htons(8081);
   serveradr.sin_addr.s_addr=INADDR_ANY;

   bind(server1,(struct sockaddr*)&serveradr,sizeof(serveradr));

   listen(server1,2);

   int client1=accept(server1,NULL,NULL);

   recv(client1,message,sizeof(message),0);
   char *rstr=(char *)malloc(1000);
   CURL *curl;
   CURLcode response;

   curl_global_init(CURL_GLOBAL_ALL);

   curl = curl_easy_init();
   if(curl) {
       curl_easy_setopt(curl, CURLOPT_URL,message);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, rstr);
       response = curl_easy_perform(curl);
       long req;
       curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &req);
       printf("Request size: %ld bytes\n", req);

       if(response != CURLE_OK) {
           fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
       } else {
         printf("working");

          //sprintf(rstr,"%d",response);
          //printf("%s",rstr);
          send(client1,rstr,1500,0);
       }
       curl_easy_cleanup(curl);
   }
   curl_global_cleanup();
   free(rstr);
   close(client1);
   close(server1);


}
