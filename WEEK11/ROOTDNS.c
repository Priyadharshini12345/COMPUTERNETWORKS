#include<stdio.h>                                                                                                                                                       
#include<stdlib.h>                                                                                                                                                      
#include<string.h>                                                                                                                                                      
#include<arpa/inet.h>                                                                                                                                                   
#include<sys/socket.h>                                                                                                                                                  
#include<sys/types.h>                                                                                                                                                   
#include<unistd.h>                                                                                                                                                      
#define ROOTPORT 8093                                                                                                                                                   
#define TLDPORT 8096                                                                                                                                                    
#define SIZE 200                                                                                                                                                        
                                                                                                                                                                        
int main(){                                                                                                                                                             
                                                                                                                                                                        
        int recvbytes,sendbytes;                                                                                                                                        
                                                                                                                                                                        
        int sockfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                                        

        if(sockfd<0){                                                                                                                                                   
                printf("Socket creation failed\n");                                                                                                                     
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        struct sockaddr_in host_addr,tld_addr,local_addr;                                                                                                               
        socklen_t length=sizeof(struct sockaddr_in);                                                                                                                    
                                                                                                                                                                        
        memset(&host_addr,0,sizeof(host_addr));                                                                                                                         
        memset(&tld_addr,0,sizeof(tld_addr));                                                                                                                           
        memset(&local_addr,0,sizeof(local_addr));                                                                                                                       
                                                                                                                                                                        
        host_addr.sin_family=AF_INET;                                                                                                                                   
        host_addr.sin_port=htons(ROOTPORT);                                                                                                                             
        host_addr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                               
                                                                                                                                                                        
        if(bind(sockfd,(struct sockaddr*)&host_addr,sizeof(host_addr))<0){                                                                                              
                printf("Bind failed\n");                                                                                                                                
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        while(1){                                                                                                                                                       
                                                                                                                                                                        
                int flag=0;                                                                                                                                             
                char buffer[SIZE],tldip[SIZE],root[SIZE],ip[SIZE],tld[SIZE],tempbuff[SIZE],linebuff[SIZE];                                                              
                                                                                                                                                                        
                char* iptemp,*temp;                                                                                                                                     
                                                                                                                                                                        
                recvbytes=recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&local_addr,&length);                                                               

                if(strncmp(buffer,"exit",4)==0) exit(0);                                                                                                                
                                                                                                                                                                        
                int i=0,j=0,k=0;                                                                                                                                        
                                                                                                                                                                        
                ip[0]='\0';                                                                                                                                             
                linebuff[0]='\0';                                                                                                                                       


                while(buffer[i++]!='.');                                                                                                                                
                                                                                                                                                                        

                while(buffer[i++]!='.');                                                                                                                                
                                                                                                                                                                        
                while(buffer[i]!=' ' && buffer[i]!='\0'){                                                                                                               

                        root[k++]=buffer[i];                                                                                                                            
                        i++;                                                                                                                                            

                }                                                                                                                                                       
                                                                                                                                                                        
                root[k]='\0';                                                                                                                                           
                                                                                                                                                                        
                printf("Request received for %s\n",root);                                                                                                               
                FILE* fd=fopen("rootdns.txt","r");                                                                                                                      
                                                                                                                                                                        
                if(!fd){                                                                                                                                                
                        printf("Error in opening the file\n");                                                                                                          
                        exit(0);                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                while(fgets(linebuff,sizeof(linebuff),fd)){                                                                                                             
                                                                                                                                                                        
                        strcpy(tempbuff,linebuff);                                                                                                                      
                                                                                                                                                                        
                        temp=strtok(tempbuff," ");                                                                                                                      
                                                                                                                                                                        
                        if(flag==0 && strncmp(temp,root,strlen(temp))==0){                                                                                              
                                                                                                                                                                        
                                iptemp=strtok(NULL,"\n");                                                                                                               
                                                                                                                                                                        
                                for(i=0;*iptemp!='\0';i++,iptemp++)                                                                                                     
                                        ip[i]=*iptemp;                                                                                                                  
                                                                                                                                                                        
                                ip[i]='\0';                                                                                                                             
                                                                                                                                                                        
                                flag=1;                                                                                                                                 
                                                                                                                                                                        
                                break;                                                                                                                                  
                                                                                                                                                                        
                        }                                                                                                                                               

                }                                                                                                                                                       
                                                                                                                                                                        
                fclose(fd);                                                                                                                                             
                                                                                                                                                                        
//              if(strcmp(ip,"")==0){                                                                                                                                   
//                                                                                                                                                                      
//                      sendbytes=sendto(sockfd,"404 Error: Not found",strlen("404 Error: Not found")+1,0,(struct sockaddr*)&local_addr,length);                        
//                      printf("404 Error: Not found\n");                                                                                                               
//              }                                                                                                                                                       
                                                                                                                                                                        
//              else{                                                                                                                                                   
                                                                                                                                                                        
                        int tldfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                         

                        if(tldfd<0){                                                                                                                                    
                                printf("Error in socket creation\n");                                                                                                   
                                exit(0);                                                                                                                                
                        }                                                                                                                                               
                                                                                                                                                                        
                        tld_addr.sin_family=AF_INET;                                                                                                                    
                        tld_addr.sin_port=htons(TLDPORT);                                                                                                               
                        tld_addr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                
                                                                                                                                                                        
                        sendbytes=sendto(tldfd,buffer,strlen(buffer)+1,0,(struct sockaddr*)&tld_addr,length);                                                           
                                                                                                                                                                        
                        recvbytes=recvfrom(tldfd,tldip,sizeof(tldip),0,NULL,NULL);                                                                                      
                                                                                                                                                                        
                        sendbytes=sendto(sockfd,tldip,strlen(tldip)+1,0,(struct sockaddr*)&local_addr,length);                                                          
                                                                                                                                                                        
                        printf("Server IP address: %s\n\n",tldip);                                                                                                      
                                                                                                                                                                        
                        close(tldfd);                                                                                                                                   
//              }                                                                                                                                                       
                                                                                                                                                                        
        }                                                                                                                                                               

                                                                                                                                                                        
        close(sockfd);                                                                                                                                                  
                                                                                                                                                                        
        return 0;                                                                                                                                                       
}                                                                                                                                                                       
                                                                                                                                                                        
