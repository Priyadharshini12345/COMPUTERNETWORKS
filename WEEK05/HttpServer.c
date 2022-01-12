#include<stdio.h>                                                                                                                                                       
#include<stdlib.h>                                                                                                                                                      
#include<string.h>                                                                                                                                                      
#include<netinet/in.h>                                                                                                                                                  
#include<sys/types.h>                                                                                                                                                   
#include<sys/socket.h>                                                                                                                                                  
#include<unistd.h>                                                                                                                                                      
#define SIZE 200                                                                                                                                                        
#define CONTENTSIZE 1000                                                                                                                                                
struct response{                                                                                                                                                        
        char data[CONTENTSIZE];                                                                                                                                         
        char contentType[SIZE];                                                                                                                                         
        char responseStatus[SIZE];                                                                                                                                      
};                                                                                                                                                                      
                                                                                                                                                                        
struct request{                                                                                                                                                         
        char method[SIZE],url[SIZE];                                                                                                                                    
        char contentType[SIZE];                                                                                                                                         
};                                                                                                                                                                      
                                                                                                                                                                        
int main(){                                                                                                                                                             
        int serverfd=socket(AF_INET,SOCK_STREAM,0);                                                                                                                     

        if(serverfd<0){                                                                                                                                                 
                printf("Socket creation failed\n");                                                                                                                     
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Socket creation successful!\n");                                                                                                                
                                                                                                                                                                        
        struct sockaddr_in serveraddr;                                                                                                                                  
                                                                                                                                                                        
        serveraddr.sin_family=AF_INET;                                                                                                                                  
        serveraddr.sin_port=htons(8897);                                                                                                                                
        serveraddr.sin_addr.s_addr=INADDR_ANY;                                                                                                                          
                                                                                                                                                                        
        if(bind(serverfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){                                                                                          
                printf("Bind failed\n");                                                                                                                                
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Bind successful!\n");                                                                                                                           
                                                                                                                                                                        
        if(listen(serverfd,1)<0){                                                                                                                                       
                printf("Listen failed\n");                                                                                                                              
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Listen successful!\n");                                                                                                                         
                                                                                                                                                                        
        for(;;){                                                                                                                                                        
                                                                                                                                                                        
        int clientfd=accept(serverfd,NULL,NULL);                                                                                                                        

                struct request Request;                                                                                                                                 
                struct response Response;                                                                                                                               
                                                                                                                                                                        
        read(clientfd,(char*)&Request,sizeof(Request));                                                                                                                 
                                                                                                                                                                        
        if(strcmp(Request.method,"GET")==0){                                                                                                                            
                                                                                                                                                                        
                FILE* fp=fopen(Request.url,"rb");                                                                                                                       
                if(!fp){                                                                                                                                                
                        strcpy(Response.data,"None\0");                                                                                                                 
                        strcpy(Response.responseStatus,"404 error: File not found\0");                                                                                  
                }                                                                                                                                                       
                else{                                                                                                                                                   
                        char buffer[CONTENTSIZE];                                                                                                                       
                                                                                                                                                                        
                        while(fgets(buffer,sizeof(buffer),fp))                                                                                                          
                                strcpy(Response.data,buffer);                                                                                                           
                        strcpy(Response.responseStatus,"200 OK\0");                                                                                                     
                }
        }                                                                                                                                                               
                                                                                                                                                                        
        else if(strcmp(Request.method,"DELETE")==0){                                                                                                                    
                if(remove(Request.url)==0){                                                                                                                             
                        strcpy(Response.responseStatus,"200 OK\0");                                                                                                     
                        strcpy(Response.data,"Sucess\0");                                                                                                               
                }                                                                                                                                                       
                else{                                                                                                                                                   
                        strcpy(Response.responseStatus,"404 error: File not found\0");                                                                                  
                        strcpy(Response.data,"Failed\0");                                                                                                               
                }                                                                                                                                                       
        }                                                                                                                                                               
                strcpy(Response.contentType,Request.contentType);                                                                                                       
                write(clientfd,(char*)&Response,sizeof(Response));                                                                                                      
                                                                                                                                                                        
        }                                                                                                                                                               
                                                                                                                                                                        
                return 0;                                                                                                                                               
}                  