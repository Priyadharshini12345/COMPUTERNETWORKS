#include<stdio.h>                                                                                                                                                       
#include<string.h>                                                                                                                                                      
#include<stdlib.h>                                                                                                                                                      
#include<unistd.h>                                                                                                                                                      
#include<sys/types.h>                                                                                                                                                   
#include<sys/socket.h>                                                                                                                                                  
#include<netinet/in.h>                                                                                                                                                  

int main(){                                                                                                                                                             
        int clientfd = socket(AF_INET,SOCK_STREAM,0);                                                                                                                   
        struct sockaddr_in server_address;                                                                                                                              
        server_address.sin_family = AF_INET;                                                                                                                            
        server_address.sin_port = htons(3542);                                                                                                                          
        server_address.sin_addr.s_addr = INADDR_ANY;                                                                                                                    

        int connStatus = connect(clientfd,(struct sockaddr *)&server_address,sizeof(server_address));                                                                   
        if(connStatus<0){                                                                                                                                               
                printf("error in connecting\n");                                                                                                                        
                return -1;                                                                                                                                              
        }                                                                                                                                                               
        char buf[200], responseToServer[200];                                                                                                                           
        while(1){                                                                                                                                                       
        recv(clientfd,&buf,sizeof(buf),0);                                                                                                                              
        printf("%s", buf);                                                                                                                                              
        if(strcmp(buf,"Logged in\n")==0 || strcmp(buf,"Registered user\n")==0 || strcmp(buf,"Invalid password\n")==0)                                                   
                break;                                                                                                                                                  
        scanf("%s",responseToServer);                                                                                                                                   
        send(clientfd,responseToServer,sizeof(responseToServer),0);                                                                                                     
        }                                                                                                                                                               
        close(clientfd);                                                                                                                                                
        return 0;                                                                                                                                                       
}                                           