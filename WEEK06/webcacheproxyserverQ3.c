#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/socket.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#define SA struct sockaddr
#define PORT 8100
#define SIZE 200
#define CONTENTSIZE 1000
                                                                                                                                                                        
struct request{
        char method[SIZE];
        char url[SIZE];
        char contentType[SIZE];
};                                                                                                                                                                      
                                                                                                                                                                        
struct response{
        char data[CONTENTSIZE];
        char contentType[SIZE];
        char responseStatus[SIZE];
        char date[SIZE];
};                                                                                                                                                                      
                                                                                                                                                                        
int main(){
                                                                                                                                                                        
        int serverfd=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
        if(serverfd<0){
                printf("Socket creation failed\n");
                exit(0);
        }
                                                                                                                                                                        
        else
                printf("Socket created successfully!\n");
struct sockaddr_in servaddr;
                                                                                                                                                                        
        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_port=htons(PORT);                                                                                                                                  
        servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
                                                                                                                                                                        
        if(bind(serverfd,(SA*)&servaddr,sizeof(servaddr))<0){
                printf("Bind failed\n");
                exit(0);
        }                                                                                                                                                               
                                                                                                                                                                        
        else
                printf("Bind successful!\n");
                                                                                                                                                                        
        if(listen(serverfd,1)!=0){
                printf("Listen failed\n");
                exit(0);
        }                                                                                                                                                               
                                                                                                                                                                        
        else
                printf("Listen successful!\n");
                                                                                                                                                                        
        int connfd1=accept(serverfd,NULL,NULL);
                                                                                                                                                                        
        if(connfd1<0){
                printf("Connection failed\n");
                exit(0);
        }                                                                                                                                                               
                                                                                                                                                                        
        else
                printf("Connection established with the proxy server\n");
                                                                                                                                                                        
        struct request Request;
        struct response Response;
                                                                                                                                                                        
        read(connfd1,(char*)&Request,sizeof(Request));FILE* fp=fopen(Request.url,"rb");
                                                                                                                                                                        
                int clientfd=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
                if(clientfd<0){
                        printf("Socket creation by the proxy server failed\n");
                        exit(0);
                }                                                                                                                                                       
                                                                                                                                                                        
                else
                        printf("Socket creation successful!\n");
                                                                                                                                                                        
                struct sockaddr_in seraddr;
                                                                                                                                                                        
                seraddr.sin_family=AF_INET;                                                                                                                             
                seraddr.sin_port=htons(9995);
                seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
                                                                                                                                                                        
                int len=sizeof(seraddr);
                                                                                                                                                                        
                int connfd=connect(clientfd,(SA*)&seraddr,len);
                                                                                                                                                                        
                if(connfd<0){
                        printf("Connection failed\n");
                        exit(0);
                }                                                                                                                                                       
                                                                                                                                                                        
                else
                        printf("Connection successful!\n");
                                                                                                                                                                        
                write(clientfd,(char*)&Request,sizeof(Request));
                read(clientfd,(char*)&Response,sizeof(Response));
                                                                                                                                                                        
                if(!fp){
                                                                                                                                                                        
                FILE* fptr;
                                                                                                                                                                        
                fptr=fopen(Request.url,"w");if(fptr==NULL)
                        printf("Error in creating file\n");
                else
                        fprintf(fptr,"%s",Response.data);
                                                                                                                                                                        
                write(connfd1,(char*)&Response,sizeof(Response));
                                                                                                                                                                        
                printf("Response status: %s\n",Response.responseStatus);
                printf("Content Type: %s\n",Response.contentType);
                printf("Data: %s\n",Response.data);
                printf("Last modified Date: %s\n",Response.date);
                                                                                                                                                                        
                }                                                                                                                                                       
        else{
                                                                                                                                                                        
                char currdate[SIZE];
                struct stat attr;
                stat(Request.url,&attr);                                                                                                                                
        //      currdate=ctime(&attr.st_mtime);
                                                                                                                                                                        
                if(strcmp(ctime(&attr.st_mtime),Response.date)<1){
                                                                                                                                                                        
                        remove(Request.url);                                                                                                                            
                                                                                                                                                                        
                        FILE* fptr=fopen(Request.url,"w");
                                                                                                                                                                        
                        if(fptr==NULL)
                                printf("Error in opening file\n");
                        else{
                                                                                                                                                                        
                                fprintf(fptr,"%s",Response.data);
                        }                                                                                                                                               
                                                                                                                                                                        
                }                                                                                                                                                       
                char buffer[CONTENTSIZE];
                fp=fopen(Request.url,"rb");
                                                                                                                                                                        
                while(fgets(buffer,CONTENTSIZE,fp))  strcpy(Response.contentType,Request.contentType);                                                                                                       
                                                                                                                                                                        
                strcpy(Response.responseStatus,"200 OK\0");
                                                                                                                                                                        
                strcpy(Response.date,ctime(&attr.st_mtime));                                                                                                            
                                                                                                                                                                        
                write(connfd1,(char*)&Response,sizeof(Response));
                                                                                                                                                                        
        }                                                                                                                                                               
                                                                                                                                                                        
        close(serverfd);                                                                                                                                                
                                                                                                                                                                        
        return 0;
}                                                                                                                                                                       
               
                                                                                                                                                                        
                                                                                                                                                     
