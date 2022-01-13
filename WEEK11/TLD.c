#include<stdio.h>                                                                                                                                                       
#include<stdlib.h>                                                                                                                                                      
#include<arpa/inet.h>                                                                                                                                                   
#include<string.h>                                                                                                                                                      
#include<unistd.h>                                                                                                                                                      
#include<sys/types.h>                                                                                                                                                   
#include<sys/socket.h>                                                                                                                                                  
#define TLDPORT 8096                                                                                                                                                    
#define AUTHPORT 8097                                                                                                                                                   
#define SIZE 200                                                                                                                                                        
                                                                                                                                                                        
int main(){                                                                                                                                                             

        int recvbytes,sendbytes;                                                                                                                                        
                                                                                                                                                                        
        int sockfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                                        
        if(sockfd<0){                                                                                                                                                   
                printf("Socket creation failed\n");                                                                                                                     
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        struct sockaddr_in host_addr,auth_addr,root_addr;                                                                                                               
        socklen_t length=sizeof(struct sockaddr_in);                                                                                                                    
                                                                                                                                                                        
        memset(&host_addr,0,sizeof(host_addr));                                                                                                                         
        memset(&auth_addr,0,sizeof(auth_addr));                                                                                                                         
        memset(&root_addr,0,sizeof(root_addr));                                                                                                                         
                                                                                                                                                                        
        host_addr.sin_family=AF_INET;                                                                                                                                   
        host_addr.sin_port=htons(TLDPORT);                                                                                                                              
        host_addr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                                               
                                                                                                                                                                        
        if(bind(sockfd,(struct sockaddr*)&host_addr,sizeof(host_addr))<0){                                                                                              
                printf("Bind failed\n");                                                                                                                                
                exit(0);                                                                                                                                                
        }                                                                                                                                                               
                                                                                                                                                                        
        while(1){                                                                                                                                                       
                                                                                                                                                                        
                char buffer[SIZE],root[SIZE],tld[SIZE],authip[SIZE],linebuff[SIZE],tempbuff[SIZE],ip[SIZE];                                                             
                char* iptemp,*temp;                                                                                                                                     
                                                                                                                                                                        
                int flag=0;                                                                                                                                             
                                                                                                                                                                        
                recvbytes=recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&root_addr,&length);                                                                
                                                                                                                                                                        
                int i = 0, j = 0, k = 0;                                                                                                                                
                                                                                                                                                                        
                if(strncmp(buffer,"exit",4)==0) { close(sockfd); exit(0); }                                                                                             
                                                                                                                                                                        
                linebuff[0]='\0';                                                                                                                                       

                                                                                                                                                                        
                while(buffer[i++] != '.');                                                                                                                              

                while(buffer[i] != '.') {                                                                                                                               

                        tld[j++] = buffer[i++];                                                                                                                         

                }                                                                                                                                                       

                                                                                                                                                                        
                tld[j++] = buffer[i++];                                                                                                                                 

                while(buffer[i] != ' ' && buffer[i] != '\0') {                                                                                                          

                        tld[j++] = buffer[i];                                                                                                                           
                        i++;                                                                                                                                            
                }                                                                                                                                                       
                                                                                                                                                                        
                tld[j]='\0';                                                                                                                                            
                ip[0]='\0';                                                                                                                                             
                                                                                                                                                                        
                printf("Request received for %s\n",tld);                                                                                                                
                                                                                                                                                                        
                FILE* fd=fopen("tlddns.txt","r");                                                                                                                       

                                                                                                                                                                        
                if(!fd){                                                                                                                                                
                                                                                                                                                                        
                        printf("Error in opening the file\n");                                                                                                          
                                                                                                                                                                        
                        exit(0);                                                                                                                                        
                                                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        

                while(fgets(linebuff,sizeof(linebuff),fd)){                                                                                                             

                        strcpy(tempbuff,linebuff);                                                                                                                      

                       temp= strtok(tempbuff," ");                                                                                                                      

                        if(flag==0 && strncmp(temp,root,strlen(temp))==0){                                                                                              
                                                                                                                                                                        
                                flag=1;                                                                                                                                 

                                iptemp=strtok(NULL,"\n");                                                                                                               

                                for(i=0;*iptemp!='\0';i++,iptemp++)                                                                                                     
                                                                                                                                                                        
                                        ip[i]=*iptemp;                                                                                                                  

                                ip[i]='\0';                                                                                                                             
                                                                                                                                                                        
                                break;                                                                                                                                  

                        }                                                                                                                                               

                }                                                                                                                                                       
                                                                                                                                                                        
                fclose(fd);                                                                                                                                             
                                                                                                                                                                        

  //              if(strcmp(ip,"")==0){                                                                                                                                 
    //                                                                                                                                                                  
      //               sendbytes=sendto(sockfd,"404 Error: Not found",strlen("404 Error: Not found")+1,0,(struct sockaddr*)&root_addr,length);                          
        //              printf("404 Error: Not found\n\n");                                                                                                             
//              }                                                                                                                                                       
//                                                                                                                                                                      
//              else{                                                                                                                                                   

                        int authfd=socket(AF_INET,SOCK_DGRAM,0);                                                                                                        

                        if(authfd<0){                                                                                                                                   
                                printf("Error in socket creation\n");                                                                                                   
                                exit(0);                                                                                                                                
                        }                                                                                                                                               

                        auth_addr.sin_family=AF_INET;                                                                                                                   
                        auth_addr.sin_port=htons(AUTHPORT);                                                                                                             
                        auth_addr.sin_addr.s_addr=inet_addr("127.0.0.1");                                                                                               

                        sendbytes=sendto(authfd,buffer,strlen(buffer)+1,0,(struct sockaddr*)&auth_addr,length);                                                         

                        recvbytes=recvfrom(authfd,authip,sizeof(authip),0,NULL,NULL);                                                                                   
                                                                                                                                                                        
                        sendbytes=sendto(sockfd,authip,strlen(authip)+1,0,(struct sockaddr*)&root_addr,length);                                                         
                                                                                                                                                                        
                        printf("Server IP Address: %s\n\n",authip);                                                                                                     
                                                                                                                                                                        
                        close(authfd);                                                                                                                                  
                                                                                                                                                                        
        //      }                                                                                                                                                       
                                                                                                                                                                        
        }                                                                                                                                                               
        close(sockfd);                                                                                                                                                  
                                                                                                                                                                        
        return 0;                                                                                                                                                       
}                         