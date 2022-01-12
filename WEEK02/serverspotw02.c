#include<stdio.h>                                                                                                                                                       
#include<sys/types.h>                                                                                                                                                   
#include<netdb.h>                                                                                                                                                       
#include<stdlib.h>                                                                                                                                                      
#include<netinet/in.h>                                                                                                                                                  
#include<sys/socket.h>                                                                                                                                                  
#include<string.h>                                                                                                                                                      
#define MAX 100                                                                                                                                                         
#define PORT 3030                                                                                                                                                       
#define SA struct sockaddr                                                                                                                                              
                                                                                                                                                                        
void func(int sockfd){                                                                                                                                                  
        char buff[MAX];                                                                                                                                                 
        int n;                                                                                                                                                          
                                                                                                                                                                        
        for(;;){                                                                                                                                                        
                n=0;                                                                                                                                                    
                bzero(buff,MAX);                                                                                                                                        
                read(sockfd,buff,sizeof(buff));                                                                                                                         
                printf("Username from the client: %s\n",buff);                                                                                                          
                bzero(buff,MAX);                                                                                                                                        
                printf("Enter the message from the server side:\n");                                                                                                    

                while((buff[n++]=getchar())!='\n')                                                                                                                      
                        ;                                                                                                                                               
                write(sockfd,buff,sizeof(buff));                                                                                                                        

                if(strncmp("exit",buff,4)==0){                                                                                                                          
                        printf("Server exits\n");                                                                                                                       
                        break;                                                                                                                                          
                }                                                                                                                                                       
        }                                                                                                                                                               
}                                                                                                                                                                       


int main(){                                                                                                                                                             
        int sockfd,connfd,len;                                                                                                                                          
        struct sockaddr_in servaddr,cli;                                                                                                                                
                                                                                                                                                                        
        sockfd=socket(AF_INET,SOCK_STREAM,0);                                                                                                                           
                                                                                                                                                                        
        if(sockfd==-1){                                                                                                                                                 
                printf("Socket creation failed.\n");                                                                                                                    
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Socket successfully created.\n");                                                                                                               
        bzero(&servaddr,sizeof(servaddr));                                                                                                                              
        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);                                                                                                                     
        servaddr.sin_port=htons(PORT);                                                                                                                                  
                                                                                                                                                                        
        if(bind(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0){                                                                                                            
                printf("Bind socket failed\n");                                                                                                                         
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Socket successfully binded\n");                                                                                                                 
                                                                                                                                                                        
        if(listen(sockfd,1)!=0){                                                                                                                                        
                printf("Listen failed\n");                                                                                                                              
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Server is Listening successfully\n");                                                                                                           
                                                                                                                                                                        
        len=sizeof(cli);                                                                                                                                                
                                                                                                                                                                        
        connfd=accept(sockfd,(SA*)&cli,&len);                                                                                                                           
                                                                                                                                                                        
        if(connfd<0){                                                                                                                                                   
                printf("Server does'nt accept the request\n");                                                                                                          
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
        else                                                                                                                                                            
                printf("Server accepted the request successfully\n");                                                                                                   
                                                                                                                                                                        

        func(connfd);                                                                                                                                                   
        close(sockfd);                                                                                                                                                  
                                                                                                                                                                        
        return 0;                                                                                                                                                       
}                                      