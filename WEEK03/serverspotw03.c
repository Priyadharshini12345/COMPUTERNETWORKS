#include<stdio.h>                                                                                                                                                       
#include<string.h>                                                                                                                                                      
#include<stdlib.h>                                                                                                                                                      
#include<unistd.h>                                                                                                                                                      
#include<sys/types.h>                                                                                                                                                   
#include<sys/socket.h>                                                                                                                                                  
#include<netinet/in.h>                                                                                                                                                  

struct credential{                                                                                                                                                      
        char uname[200];                                                                                                                                                
        char pwd[200];                                                                                                                                                  
};                                                                                                                                                                      
int main(){                                                                                                                                                             
        int serverfd = socket(AF_INET,SOCK_STREAM,0);                                                                                                                   
        struct credential s[5];                                                                                                                                         
        int count = 0;                                                                                                                                                  

        if(serverfd<0)                                                                                                                                                  
                printf("error in socket creation\n");                                                                                                                   
        printf("socket established\n");                                                                                                                                 
        struct sockaddr_in server_address;                                                                                                                              
        server_address.sin_family = AF_INET;                                                                                                                            
        server_address.sin_port = htons(3542);                                                                                                                          
        server_address.sin_addr.s_addr = INADDR_ANY;                                                                                                                    

        int connStatus = bind(serverfd,(struct sockaddr *)&server_address,sizeof(server_address));                                                                      
        if(connStatus<0){                                                                                                                                               
                printf("error in establishing server\n");                                                                                                               
                return -1;                                                                                                                                              
        }                                                                                                                                                               
        printf("Server established\n");                                                                                                                                 
        printf("listening on port : %d\n",ntohs(server_address.sin_port));                                                                                              

        listen(serverfd,1);                                                                                                                                             
while(count<5){                                                                                                                                                         
                int clientfd = accept(serverfd,NULL,NULL);                                                                                                              
                                                                                                                                                                        
                char buf[200],msg[200] = "Enter your username: ";                                                                                                       
                send(clientfd,msg,sizeof(msg),0);                                                                                                                       
                recv(clientfd,buf,sizeof(buf),0);                                                                                                                       
                int i = 0;                                                                                                                                              
                for(i=0;i<count;i++){                                                                                                                                   
                        if(strcmp(s[i].uname,buf) == 0)                                                                                                                 
                                break;                                                                                                                                  
                }                                                                                                                                                       
                if(i == count){                                                                                                                                         
                        strcpy(msg,"Username doesn't exist...Register first...\nEnter your username: ");                                                                
                        send(clientfd,msg,sizeof(msg),0);                                                                                                               
                        recv(clientfd,buf,sizeof(buf),0);                                                                                                               
                        strcpy(s[count].uname,buf);                                                                                                                     
                        strcpy(msg,"Enter your password: ");                                                                                                            
                        send(clientfd,msg,sizeof(msg),0);                                                                                                               
                        recv(clientfd,buf,sizeof(buf),0);                                                                                                               
                        strcpy(s[count].pwd,buf);                                                                                                                       
                        strcpy(msg,"Registered user\n");                                                                                                                
                        send(clientfd,msg,sizeof(msg),0);                                                                                                               
                        count++;                                                                                                                                        
                }                                                                                                                                                       
else{                                                                                                                                                                   
                        strcpy(msg,"Enter your password: ");                                                                                                            
                        send(clientfd,msg,sizeof(msg),0);                                                                                                               
                        recv(clientfd,buf,sizeof(buf),0);                                                                                                               
                        if(strcmp(s[i].pwd,buf) == 0){                                                                                                                  
                                strcpy(msg,"Logged in\n");                                                                                                              
                                send(clientfd,msg,sizeof(msg),0);                                                                                                       
                        }                                                                                                                                               
                        else{                                                                                                                                           
                                strcpy(msg,"Invalid password\n");                                                                                                       
                                send(clientfd,msg,sizeof(msg),0);                                                                                                       
                        }                                                                                                                                               
                                                                                                                                                                        
                }                                                                                                                                                       
        }                                                                                                                                                               
                                                                                                                                                                        
        close(serverfd);                                                                                                                                                
        return 0;                                                                                                                                                       
}                                                      