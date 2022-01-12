#include "header.h"

int main(){
                                                                                                                                                                        
        struct sockaddr_in receiver_addr;
                                                                                                                                                                        
        int receiver_socket=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
        if(receiver_socket<0){
                                                                                                                                                                        
                printf("Error in socket creation\n");
                return 0;
                                                                                                                                                                        
        }                                                                                                                                                               
                                                                                                                                                                        
        printf("Socket created\n");
                                                                                                                                                                        
        receiver_addr.sin_family=AF_INET;                                                                                                                               
        receiver_addr.sin_port=htons(PORT);                                                                                                                             
        receiver_addr.sin_addr.s_addr=INADDR_ANY;                                                                                                                       
                                                                                                                                                                        
        int ret=bind(receiver_socket,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr));
                                                                                                                                                                        
        if(ret<0){
                                                                                                                                                                        
                printf("Error in binding\n");
                return 0;
        }                                                                                                                                                               
                                                                                                                                                                        
        printf("Bind successful\n");
                                                                                                                                                                        
        if(listen(receiver_socket,N)<0){
                printf("Error in listening\n");
                return 0;
        }                                                                                                                                                               
                                                                                                                                                                        
        printf("Listening to port %d\n\n",PORT);
                                                                                                                                                                        
        int sender_sock=accept(receiver_socket,NULL,NULL);

         int next_seq_num=0,count=0;
                                                                                                                                                                        
        char response[SIZE];
        tcppacket packet[SIZE];                                                                                                                                         
                                                                                                                                                                        
        int num_packet=0;
                                                                                                                                                                        
        recv(sender_sock,&num_packet,sizeof(num_packet),0);
                                                                                                                                                                        
        printf("Number of packets=%d\n",num_packet);
                                                                                                                                                                        
        while(1){
                                                                                                                                                                        
                response[0]='\0';
                int rb=recv(sender_sock,&packet[count],sizeof(tcppacket),0);
                                                                                                                                                                        
                if(count==num_packet){
                        printf("CLOSING CONNECTION\n");
                        close(sender_sock);                                                                                                                             
                        break;
                }                                                                                                                                                       
                                                                                                                                                                        
                printf("Packet with seq num %d received \n",packet[count].header.seq_num);
                                                                                                                                                                        
                if(packet[count].header.seq_num==next_seq_num){
                                                                                                                                                                        
                        if(packet[count].header.drop_flag==1){
                                                                                                                                                                        
                                printf("Packet Number %d dropped(seq num %d)\n",count,packet[count].header.seq_num);
                                bzero(&packet[count],sizeof(tcppacket));
                                sprintf(response,"NACK %d",next_seq_num);
                                int sb=send(sender_sock,&response,sizeof(response),0);
                        }                                                                                                                                               
                                                                                                                                                                        
                        else{
                                printf("Packet number %d received successfully(seq num %d)\n",count,packet[count].header.seq_num);
                                printf("The data: %s\n",packet[count].data);
                                packet[count].header.ack_flag=1;
                                sprintf(response,"ACK %d",next_seq_num);
	               next_seq_num=nextseqnum(next_seq_num);                                                                                                  
                                rb=send(sender_sock,&response,sizeof(response),0);
                                count++;                                                                                                                                
                        }                                                                                                                                               
                                                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                else
                        bzero(&packet[count],sizeof(tcppacket));
                                                                                                                                                                        
                printf("\n");
        }                                                                                                                                                               
                                                                                                                                                                        
        close(receiver_socket);                                                                                                                                         
                                                                                                                                                                        
        return 0;
}                                      