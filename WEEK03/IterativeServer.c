#include<stdio.h>                                                                                                                                                       
#include<sys/types.h>                                                                                                                                                   
#include<sys/socket.h>                                                                                                                                                  
#include<string.h>                                                                                                                                                      
#include<netinet/in.h>                                                                                                                                                  
#include<stdlib.h>                                                                                                                                                      
#define PORT 3564                                                                                                                                                       
#define MAX 100                                                                                                                                                         
#define SA struct sockaddr                                                                                                                                              
int main(){                                                                                                                                                             
        int sockfd,connfd;                                                                                                                                              
        struct sockaddr_in servaddr,clientaddr;                                                                                                                         
        int len,n;                                                                                                                                                      
        char msg[MAX];                                                                                                                                                  
        int i;                                                                                                                                                          
                                                                                                                                                                        
        sockfd=socket(AF_INET,SOCK_STREAM,0);                                                                                                                           
                                                                                                                                                                        
        if(sockfd==-1){                                                                                                                                                 
                printf("Error in creating socket!\n");                                                                                                                  
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        else                                                                                                                                                            
                printf("Socket created successfully\n");                                                                                                                
                                                                                                                                                                        
        bzero(&servaddr,sizeof(servaddr));                                                                                                                              

        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);                                                                                                                     
        servaddr.sin_port=htons(PORT);                                                                                                                                  
                                                                                                                                                                        
        if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0){                                                                                                          
                printf("Bind failed\n");                                                                                                                                
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        else                                                                                                                                                            
                printf("Bind successfully done\n");                                                                                                                     
                                                                                                                                                                        
                                                                                                                                                                        
        if(listen(sockfd,5)!=0){                                                                                                                                        
                printf("Listen failed!\n");                                                                                                                             
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        else                                                                                                                                                            
                printf("Server listening successfully\n");                                                                                                              

        for(i=0;i<5;i++){                                                                                                                                               

                printf("Server waiting for a new client connection\n");                                                                                                 
                len=sizeof(clientaddr);                                                                                                                                 
                                                                                                                                                                        
                connfd=accept(sockfd,(SA*)&clientaddr,&len);                                                                                                            
                                                                                                                                                                        
                if(connfd<0){                                                                                                                                           
                        printf("Server failed to accept the request\n");                                                                                                
                        exit(0);                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                else                                                                                                                                                    
                        printf("Server accepted the request successfully\n");                                                                                           
                                                                                                                                                                        
                while(1){                                                                                                                                               
                        n=recv(connfd,msg,MAX,0);                                                                                                                       
                        if(n==0){                                                                                                                                       
                                close(connfd);                                                                                                                          
                                break;                                                                                                                                  
                        }                                                                                                                                               
                        msg[n]=0;                                                                                                                                       
                        send(connfd,msg,n,0);                                                                                                                           
                        printf("Received:  %s\n",msg);                                                                                                                  
                }                                                                                                                                                       
        }                                                                                                                                                               
                                                                                                                                                                        
        return 0;                                                                                                                                                       
}                                                 