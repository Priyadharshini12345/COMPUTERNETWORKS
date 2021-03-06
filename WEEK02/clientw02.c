#include<stdio.h>                                                                                                                                                       
#include<stdlib.h>                                                                                                                                                      
#include<string.h>                                                                                                                                                      
#include<sys/socket.h>                                                                                                                                                  
#include<sys/types.h>                                                                                                                                                   
#include<netdb.h>                                                                                                                                                       
#define MAX 100                                                                                                                                                         
#define PORT 3030                                                                                                                                                       
#define SA struct sockaddr                                                                                                                                              
                                                                                                                                                                        
void func(int sockfd){                                                                                                                                                  
        char buff[MAX];                                                                                                                                                 
        int n;                                                                                                                                                          
                                                                                                                                                                        
        for(;;){                                                                                                                                                        
                n=0;                                                                                                                                                    
                bzero(buff,sizeof(buff));                                                                                                                               
                                                                                                                                                                        
                printf("Enter the message from the client:\n");                                                                                                         
                while((buff[n++]=getchar())!='\n')                                                                                                                      
                        ;                                                                                                                                               
                write(sockfd,buff,sizeof(buff));                                                                                                                        
                bzero(buff,sizeof(buff));                                                                                                                               
                read(sockfd,buff,sizeof(buff));                                                                                                                         
                printf("From server: %s\n",buff);                                                                                                                       
                if(strncmp(buff,"exit",4)==0){                                                                                                                          
                        printf("Client exits.\n");                                                                                                                      
                        break;                                                                                                                                          
                }                                                                                                                                                       
        }                                                                                                                                                               
}                                                                                                                                                                       
                                                                                                                                                                        

int main(){                                                                                                                                                             
        int sockfd,connfd;                                                                                                                                              
        struct sockaddr_in servaddr,cli;                                                                                                                                
        char buf[200];                                                                                                                                                  
        char msg[200]="Message from the client\n";                                                                                                                      
                                                                                                                                                                        
        sockfd=socket(AF_INET,SOCK_STREAM,0);                                                                                                                           
                                                                                                                                                                        
        if(sockfd==-1){                                                                                                                                                 
                printf("Socket creation failed\n");                                                                                                                     
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Socket successfully created\n");                                                                                                                
        bzero(&servaddr,sizeof(servaddr));                                                                                                                              
                                                                                                                                                                        
        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                                
        servaddr.sin_port=htons(PORT);                                                                                                                                  
                                                                                                                                                                        
        connfd=connect(sockfd,(SA*)&servaddr,sizeof(servaddr));                                                                                                         
        if(connfd<0){                                                                                                                                                   
                printf("Client failed to connect with the server\n");                                                                                                   
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Successfully connected to the server\n");                                                                                                       
                                                                                                                                                                        
        func(sockfd);                                                                                                                                                   
                                                                                                                                                                        
        close(sockfd);                                                                                                                                                  
}                                 