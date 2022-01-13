#include<stdio.h>                                                                                                                                                       
#include<string.h>                                                                                                                                                      
#include<unistd.h>                                                                                                                                                      
#include<stdlib.h>                                                                                                                                                      
#include<sys/socket.h>                                                                                                                                                  
#include<sys/types.h>                                                                                                                                                   
#include<arpa/inet.h>                                                                                                                                                   
#define AUTHPORT 8097                                                                                                                                                   
                                                                                                                                                                        
#define SIZE 200                                                                                                                                                        
                                                                                                                                                                        
int main(){                                                                                                                                                             
                                                                                                                                                                        

        int recvbytes,sendbytes;                                                                                                                                        

        int sockfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                                        
                                                                                                                                                                        
        if(sockfd<0){                                                                                                                                                   
                printf("Socket creation failed\n");                                                                                                                     
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        struct sockaddr_in host_addr,tld_addr;                                                                                                                          
                                                                                                                                                                        
        socklen_t length=sizeof(struct sockaddr_in);                                                                                                                    
                                                                                                                                                                        
        memset(&host_addr,0,sizeof(host_addr));                                                                                                                         
        memset(&tld_addr,0,sizeof(tld_addr));                                                                                                                           
                                                                                                                                                                        
        host_addr.sin_family=AF_INET;                                                                                                                                   
        host_addr.sin_port=htons(AUTHPORT);                                                                                                                             
        host_addr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                               
                                                                                                                                                                        
        if(bind(sockfd,(struct sockaddr*)&host_addr,sizeof(host_addr))<0){                                                                                              
                printf("Bind failed\n");                                                                                                                                
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        while(1){                                                                                                                                                       
                                                                                                                                                                        
                char buffer[SIZE],ip[SIZE],linebuff[SIZE],tempbuff[SIZE];                                                                                               
                                                                                                                                                                        
                char* iptemp,*temp;                                                                                                                                     
                                                                                                                                                                        
                int flag=0;                                                                                                                                             
                                                                                                                                                                        
                recvbytes=recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&tld_addr,&length);                                                                 
                                                                                                                                                                        
                if(recvbytes<0){ printf("Error in receiving\n"); exit(0); }                                                                                             
                                                                                                                                                                        
                if(strncmp(buffer,"exit",4)==0){ close(sockfd); exit(0); }                                                                                              
                                                                                                                                                                        
                printf("Request received for %s \n",buffer);                                                                                                            
                                                                                                                                                                        
                FILE* fd=fopen("authdns.txt","r");                                                                                                                      
                                                                                                                                                                        
                if(!fd){                                                                                                                                                
                        printf("Cannot open the file\n");                                                                                                               
                        exit(0);                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                                                                                                                                                                        
                ip[0]='\0';                                                                                                                                             
                linebuff[0]='\0';                                                                                                                                       
                                                                                                                                                                        
                while(fgets(linebuff,sizeof(linebuff),fd)){                                                                                                             
                                                                                                                                                                        
                        strcpy(tempbuff, linebuff);                                                                                                                     
                        temp = strtok(tempbuff, " ");                                                                                                                   

                        if(flag == 0 && strncmp(temp, buffer, strlen(temp)) == 0) {                                                                                     

                                flag = 1;                                                                                                                               

                                iptemp = strtok(NULL, "\n");                                                                                                            
                                int i;                                                                                                                                  

                                for(i = 0; *iptemp != '\0'; i++, iptemp++)                                                                                              
                                                                                                                                                                        
                                        ip[i] = *iptemp;                                                                                                                

                                ip[i] = '\0';                                                                                                                           
                                                                                                                                                                        
                                break;                                                                                                                                  
                        }                                                                                                                                               
                                                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                fclose(fd);                                                                                                                                             
                                                                                                                                                                        
                //if(strcmp(ip,"")==0){                                                                                                                                 
                                                                                                                                                                        
                // {                                                                                                                                                    

                  //     sendbytes = sendto(sockfd, "404 Error: Not found", strlen("404 Error: Not found") + 1, 0, (struct sockaddr*)&tld_addr, length);                
                    //   printf("404 Error: Not found\n\n");                                                                                                            

              // }                                                                                                                                                      
              //  else {                                                                                                                                                
                        sendbytes=sendto(sockfd,ip,strlen(ip)+1,0,(struct sockaddr*)&tld_addr,length);                                                                  
                        printf("Server IP Address: %s\n\n",ip);                                                                                                         
                //}                                                                                                                                                     
                                                                                                                                                                        
        }                                                                                                                                                               
                                                                                                                                                                        
        close(sockfd);                                                                                                                                                  
                                                                                                                                                                        
        return 0;                                                                                                                                                       
}   