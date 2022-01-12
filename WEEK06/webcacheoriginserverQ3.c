#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#define SIZE 200
#define CONTENTSIZE 1000
#define SA struct sockaddr
#define PORT 9995
                                                                                                                                                                        
                                                                                                                                                                        
struct response{
        char data[CONTENTSIZE];
        char contentType[SIZE];
        char responseStatus[SIZE];
        char date[SIZE];
};                                                                                                                                                                      
                                                                                                                                                                        
struct request{
        char method[SIZE];
        char url[SIZE];
        char contentType[SIZE];
};                                                                                                                                                                      
                                                                                                                                                                        
int main(){
                                                                                                                                                                        
        int serverfd=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
        if(serverfd<0){
                printf("Error in creating server side socket\n");
                exit(0);
        }                                                                                                                                                               
                                                                                                                                                                        
        else
                printf("Socket created successfully\n");
struct sockaddr_in servaddr;
                                                                                                                                                                        
        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_port=htons(PORT);                                                                                                                                  
        servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
                                                                                                                                                                        
        if(bind(serverfd,(SA*)&servaddr,sizeof(servaddr))<0){
                printf("Socket Bind failed\n");
                exit(0);
        }                                                                                                                                                               
                                                                                                                                                                        
        else
                printf("Socket bind successful!\n");
                                                                                                                                                                        
        if(listen(serverfd,1)!=0){
                printf("Listen failed\n");
                exit(0);
        }                                                                                                                                                               
                                                                                                                                                                        
        else
                printf("Server is listening!\n");
                                                                                                                                                                        
        int clientfd=accept(serverfd,NULL,NULL);
                                                                                                                                                                        
        struct request Request;
        struct response Response;
                                                                                                                                                                        
        read(clientfd,(char*)&Request,sizeof(Request));
                                                                                                                                                                        
        FILE* fp=fopen(Request.url,"rb");
                                                                                                                                                                        
        strcpy(Response.contentType,Request.contentType);                                                                                                               
                                                                                                                                                                        
        if(!fp){
                strcpy(Response.data,"None\0");
                strcpy(Response.responseStatus,"404 error: File not found\0");
        }                                                                                                                                                               
        else{ char buffer[CONTENTSIZE];
                while(fgets(buffer,CONTENTSIZE,fp))
                        strcpy(Response.data,buffer);                                                                                                                   
                                                                                                                                                                        
                strcpy(Response.responseStatus,"200 OK\0");
                struct stat attr;
                stat(Request.url,&attr);                                                                                                                                
                strcpy(Response.date,ctime(&attr.st_mtime));                                                                                                            
        }                                                                                                                                                               
                                                                                                                                                                        
        write(clientfd,(char*)&Response,sizeof(Response));
                                                                                                                                                                        
        close(clientfd);                                                                                                                                                
                                                                                                                                                                        
        return 0;
}                                                                                                                                                        