#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#define CONTENTSIZE 1000
#define SA struct sockaddr
#define SIZE 200
#define PORT 8100
struct request{
        char method[SIZE];
        char url[SIZE];
        char contentType[SIZE];
};                                                                                                                                                                      
                                                                                                                                                                        
struct response{
        char data[CONTENTSIZE];
        char responseStatus[SIZE];
        char contentType[SIZE];
        char date[SIZE];
};                                                                                                                                                                      
                                                                                                                                                                        
int main(){
                                                                                                                                                                        
        int clientfd=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
        if(clientfd<0){
                printf("Client Socket creation failed\n");
                exit(0);
        }                                                                                                                                                               
                                                                                                                                                                        
        else
                printf("Socket creation successful!\n");
                                                                                                                                                                        
        struct sockaddr_in servaddr;
                                                                                                                                                                        
        servaddr.sin_family=AF_INET;   servaddr.sin_port=htons(PORT);                                                                                                                                  
        servaddr.sin_addr.s_addr=INADDR_ANY;                                                                                                                            
                                                                                                                                                                        
        int len=sizeof(servaddr);
                                                                                                                                                                        
        int connfd=connect(clientfd,(SA*)&servaddr,len);
                                                                                                                                                                        
        if(connfd<0){
                printf("Error in establishing connection\n");
                exit(0);
        }
                                                                                                                                                                        
        else
                printf("Connection established successfully\n");
                                                                                                                                                                        
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
                                                                                                                                                                        
        printf("Content type: %s\n",Response.responseStatus);
                                                                                                                                                                        
        printf("Response status: %s\n",Response.contentType);
                                                                                                                                                                        
        printf("Data:%s\n",Response.data);printf("Last Modified Date: %s\n",Response.date);
                                                                                                                                                                        
        close(clientfd);                                                                                                                                                
                                                                                                                                                                        
        return 0;
}        