#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#define SIZE 200
#define CONTENTSIZE 1000
                                                                                                                                                                        
                                                                                                                                                                        
struct request{
        char method[SIZE],url[SIZE];
        char contentType[SIZE];
};                                                                                                                                                                      
struct response{
        char data[CONTENTSIZE];
        char contentType[SIZE],responseStatus[SIZE];
};                                                                                                                                                                      
                                                                                                                                                                        
int main(){
        int clientfd=socket(AF_INET,SOCK_STREAM,0);
        if(clientfd<0){
                printf("Socket creation failed\n");
                exit(0);
        }                                                                                                                                                               
        else
                printf("Socket creation successful!\n");
                                                                                                                                                                        
        struct sockaddr_in serveraddr;
                                                                                                                                                                        
        serveraddr.sin_family=AF_INET;                                                                                                                                  
        serveraddr.sin_port=htons(8897);
        serveraddr.sin_addr.s_addr=INADDR_ANY;                                                                                                                          
                                                                                                                                                                        
        int len=sizeof(serveraddr);
                                                                                                                                                                        
        int connfd=connect(clientfd,(struct sockaddr*)&serveraddr,len);  
        if(connfd<0){
                printf("Error in establishing connection\n");
                exit(0);
        }
        else
                printf("Successful connection\n");
                                                                                                                                                                        
        struct request Request;
        struct response Response;
                                                                                                                                                                        
        printf("Enter the method type\n");
        scanf("%s",Request.method);
                                                                                                                                                                        
        printf("Enter the url(Filename)\n");
        scanf("%s",Request.url);
                                                                                                                                                                        
        printf("Enter the content type\n");
        scanf("%s",Request.contentType);
                                                                                                                                                                        
        write(clientfd,(char*)&Request,sizeof(Request));
                                                                                                                                                                        
        read(clientfd,(char*)&Response,sizeof(Response));
                                                                                                                                                                        
        if(strcmp(Request.method,"GET")==0){
                printf("Response status: %s\n",Response.responseStatus);
                printf("Content Type: %s\n",Response.contentType);
                printf("Data: %s\n",Response.data);
        }
        else if(strcmp(Request.method,"DELETE")==0){
                printf("Response status: %s\n",Response.responseStatus);
                printf("Content Type: %s\n",Response.contentType);
                printf("Data: %s\n",Response.data);
        }
                                                                                                                                                                        
        close(clientfd);                                                                                                                                                
                                                                                                                                                                        
        return 0;
}                       