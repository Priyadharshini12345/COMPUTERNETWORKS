#include<stdio.h>                                                                                                                                                       
#include<stdlib.h>                                                                                                                                                      
#include<string.h>                                                                                                                                                      
#include<unistd.h>                                                                                                                                                      
#include<pthread.h>                                                                                                                                                     
#include<netinet/in.h>                                                                                                                                                  
#include<sys/socket.h>                                                                                                                                                  
#include<sys/types.h>                                                                                                                                                   
#include<arpa/inet.h>                                                                                                                                                   
#include<fcntl.h>                                                                                                                                                       
#include<sys/sendfile.h>                                                                                                                                                
#define PORT 6000                                                                                                                                                       
#define SIZE 300                                                                                                                                                        
#define N 4                                                                                                                                                             
#define max_seq_num 3                                                                                                                                                   
#define max_frame 9                                                                                                                                                     
#define min(x,y) ((x)<(y) ? x : y)                                                                                                                                      
typedef struct tcpheader{                                                                                                                                               
                                                                                                                                                                        
        int drop_flag;                                                                                                                                                  
        int ack_flag;                                                                                                                                                   
        int seq_num;                                                                                                                                                    
                                                                                                                                                                        
}tcpheader;                                                                                                                                                             
                                                                                                                                                                        
                                                                                                                                                                        
typedef struct tcppacket{                                                                                                                                               
                                                                                                                                                                        
        tcpheader header;                                                                                                                                               
        char data[SIZE];                                                                                                                                                
                                                                                                                                                                        
}tcppacket;                                                                                                                                                             
                                                                                                                                                                        
                                                                                                                                                                        
int nextseqnum(int num){                                                                                                                                                
        if(num>=max_seq_num)                                                                                                                                            
                return 0;                                                                                                                                               
        return num+1;                                                                                                                                                   
}                                    