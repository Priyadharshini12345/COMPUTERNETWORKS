#include<stdio.h>                                                                                                                                                       
#include<sys/types.h>                                                                                                                                                   
#include<sys/socket.h>                                                                                                                                                  
#include<string.h>                                                                                                                                                      
#include<stdlib.h>                                                                                                                                                      
#include<netdb.h>                                                                                                                                                       
#include<netinet/in.h>                                                                                                                                                  
#define PORT 3564                                                                                                                                                       
#define SA struct sockaddr                                                                                                                                              
#define MAX 100                                                                                                                                                         
                                                                                                                                                                        
int main(){                                                                                                                                                             
        int sockfd;                                                                                                                                                     
        struct sockaddr_in servaddr;                                                                                                                                    
        char msg1[MAX],msg2[MAX];                                                                                                                                       
        int n;                                                                                                                                                          
                                                                                                                                                                        
        sockfd=socket(AF_INET,SOCK_STREAM,0);                                                                                                                           
                                                                                                                                                                        
        if(sockfd==-1){                                                                                                                                                 
                printf("Socket creation failed!\n");                                                                                                                    
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        else                                                                                                                                                            
                printf("Socket created successfully!\n");                                                                                                               
                                                                                                                                                                        
        bzero(&servaddr,sizeof(servaddr));                                                                                                                              
                                                                                                                                                                        
        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                                
        servaddr.sin_port=htons(PORT);                                                                                                                                  
                                                                                                                                                                        
        if((connect(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0){                                                                                                       
                printf("Connection failed\n");                                                                                                                          
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        else                                                                                                                                                            
                printf("Connection established successfully\n");                                                                                                        
                                                                                                                                                                        
        while(1){                                                                                                                                                       
                printf("Enter message to send to the server\n");                                                                                                        
                fgets(msg1,MAX,stdin);                                                                                                                                  
                if(strncmp(msg1,"exit",4)==0)                                                                                                                           
                        break;                                                                                                                                          
                n=strlen(msg1)+1;                                                                                                                                       
                send(sockfd,msg1,n,0);                                                                                                                                  
                n=recv(sockfd,msg2,MAX,0);                                                                                                                              
                printf("Received message from the server: %s\n",msg2);                                                                                                  
        }                                                                                                                                                               
                                                                                                                                                                        
        return 0;                                                                                                                                                       
}                                                                                                                                                                       
                                             