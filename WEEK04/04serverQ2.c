#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#define PORT 3562
#define SA struct sockaddr
                                                                                                                                                                        
struct student{
        int reg_no;
        char name[100];
        int year;
};                                                                                                                                                                      
                                                                                                                                                                        
void func(int sockfd){
                                                                                                                                                                        
        struct student s;
                                                                                                                                                                        
        //bzero(s,sizeof(s));
                                                                                                                                                                        
        read(sockfd,(struct student*)&s,sizeof(s));
                                                                                                                                                                        
        printf("Details received from the client:\n");
                                                                                                                                                                        
        printf("Student registration number: %d\n",s.reg_no);
                                                                                                                                                                        
        printf("Student name: %s\n",s.name);
                                                                                                                                                                        
        printf("Student year: %d\n",s.year);
                                                                                                                                                                        
}                                                                                                                                                                       
                                                                                                                                                                        
int main(){
                                                                                                                                                                        
        int sockfd,connfd;
        struct sockaddr_in servaddr,clientaddr;
	  sockfd=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
        if(sockfd<0){
                printf("Error in socket creation\n");
                return 0;
        }                                                                                                                                                               
        else
                printf("Socket successfully created\n");
                                                                                                                                                                        
        bzero(&servaddr,sizeof(servaddr));
                                                                                                                                                                        
        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);                                                                                                                     
        servaddr.sin_port=htons(PORT);                                                                                                                                  
                                                                                                                                                                        
        if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0){
                printf("Error in binding\n");
                return 0;
        }                                                                                                                                                               
        else
                printf("Binding successful\n");
                                                                                                                                                                        
        if(listen(sockfd,1)!=0){
                printf("Server is not listening\n");
                return 0;
        }                                                                                                                                                               
        else
                printf("Server is listening successfully\n");
                                                                                                                                                                        
        int len=sizeof(clientaddr);
                                                                                                                                                                        
        connfd=accept(sockfd,(SA*)&clientaddr,&len);                                                                                                                    
                                                                                                                                                                        
        if(connfd<0){
                printf("Server failed to accept the request from the client\n");
                return 0;
        }                                                                                                                                                               
        else
	
                printf("Server accepted the request successfully\n");
                                                                                                                                                                        
        func(connfd);                                                                                                                                                   
                                                                                                                                                                        
        close(sockfd);                                                                                                                                                  
                                                                                                                                                                        
        return 0;
}                    
                                                                                                                                                                        
                                                                                                                             