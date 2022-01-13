#include<stdio.h>                                                                                                                                                       
#include<stdlib.h>                                                                                                                                                      
#include<arpa/inet.h>                                                                                                                                                   
#include<string.h>                                                                                                                                                      
#include<unistd.h>                                                                                                                                                      
#include<sys/socket.h>                                                                                                                                                  
#include<sys/types.h>                                                                                                                                                   
#define LOCALPORT 8090                                                                                                                                                  
#define ROOTPORT 8093                                                                                                                                                   
#define SIZE 200                                                                                                                                                        
                                                                                                                                                                        
int main(){                                                                                                                                                             

        int sockfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                                        

        if(sockfd<0){                                                                                                                                                   
                printf("Socket creation failed\n");                                                                                                                     
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        struct sockaddr_in host_addr,clientaddr;                                                                                                                        
                                                                                                                                                                        
        socklen_t length=sizeof(struct sockaddr_in);                                                                                                                    
                                                                                                                                                                        
        int recvbytes,sendbytes;                                                                                                                                        
                                                                                                                                                                        
        memset(&host_addr,0,sizeof(host_addr));                                                                                                                         
        memset(&clientaddr,0,sizeof(clientaddr));                                                                                                                       
                                                                                                                                                                        
        host_addr.sin_family=AF_INET;                                                                                                                                   
        host_addr.sin_port=htons(LOCALPORT);                                                                                                                            
        host_addr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                               
                                                                                                                                                                        
        if(bind(sockfd,(struct sockaddr*)&host_addr,sizeof(host_addr))<0){                                                                                              
                printf("Bind failed\n");                                                                                                                                
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        while(1){                                                                                                                                                       
                                                                                                                                                                        
                char root[SIZE],rootip[SIZE],buffer[SIZE];                                                                                                              

                recvbytes=recvfrom(sockfd,buffer,sizeof(buffer)+1,0,(struct sockaddr*)&clientaddr,&length);                                                             
                                                                                                                                                                        
                if(strncmp(buffer,"exit",4)==0) exit(0);                                                                                                                
                                                                                                                                                                        
                printf("Request from client: %s\n",buffer);                                                                                                             
                                                                                                                                                                        
                strcpy(root,buffer);                                                                                                                                    
                                                                                                                                                                        
                int rootfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                                

                if(rootfd<0){                                                                                                                                           
                        printf("Socket creation failed\n");                                                                                                             
                        exit(0);                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                struct sockaddr_in root_addr;                                                                                                                           
                                                                                                                                                                        
                root_addr.sin_family=AF_INET;                                                                                                                           
                root_addr.sin_port=htons(ROOTPORT);                                                                                                                     
                root_addr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                       
                                                                                                                                                                        
                                                                                                                                                                        
                sendbytes=sendto(rootfd,root,strlen(root)+1,0,(struct sockaddr*)&root_addr,length);                                                                     
                                                                                                                                                                        
                recvfrom(rootfd,rootip,sizeof(rootip),0,NULL,NULL);                                                                                                     
                                                                                                                                                                        
                printf("Server IP Address: %s\n\n",rootip);                                                                                                             
                                                                                                                                                                        
                sendbytes=sendto(sockfd,rootip,strlen(rootip)+1,0,(struct sockaddr*)&clientaddr,length);                                                                
                                                                                                                                                                        
                close(rootfd);                                                                                                                                          
                                                                                                                                                                        
        }                                                                                                                                                               
                                                                                                                                                                        
        close(sockfd);                                                                                                                                                  
                                                                                                                                                                        
        return 0;                                                                                                                                                       
}                                                                                                                                                                                   
 
