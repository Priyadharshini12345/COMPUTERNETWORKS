#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 3562
#define SA struct sockaddr
#define MAX 100
                                                                                                                                                                        
struct student{
        int reg_no;
        char name[100];
        int year;
};                                                                                                                                                                      
                                                                                                                                                                        
void func(int sockfd){
                                                                                                                                                                        
        struct student s;
                                                                                                                                                                        
        //bzero(s,sizeof(s));
                                                                                                                                                                        
        printf("Enter the student registration number\n");
        scanf("%d",&s.reg_no);
                                                                                                                                                                        
        printf("Enter the student name\n");
        scanf("%s",s.name);
                                                                                                                                                                        
        printf("Enter the year in which the student is currently studying\n");
        scanf("%d",&s.year);
                                                                                                                                                                        
        write(sockfd,(void*)&s,sizeof(s));
                                                                                                                                                                        
}
                                                                                                                                                                        
int main(){
                                                                                                                                                                        
        int sockfd,connfd;
        struct sockaddr_in servaddr,cli;
         sockfd=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
        if(sockfd==-1){
                printf("Socket creation failed\n");
                return 0;
        }                                                                                                                                                               
        else
                printf("Socket creation successful!\n");
                                                                                                                                                                        
        bzero(&servaddr,sizeof(servaddr));
                                                                                                                                                                        
        servaddr.sin_family=AF_INET;                                                                                                                                    
        servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
        servaddr.sin_port=htons(PORT);                                                                                                                                  
                                                                                                                                                                        
        connfd=connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
                                                                                                                                                                        
        if(connfd<0){
                printf("Error in establishing connection with the server\n");
                return 0;
        }                                                                                                                                                               
        else
                printf("Connection established successfully\n");
                                                                                                                                                                        
        func(sockfd);                                                                                                                                                   
                                                                                                                                                                        
        close(sockfd);                                                                                                                                                  
                                                                                                                                                                        
        return 0;
}