#include "header.h"
                                                                                                                                                                        
int main(){
                                                                                                                                                                        
        struct sockaddr_in receiver_addr;
        int sender_sock=socket(AF_INET,SOCK_STREAM,0);
                                                                                                                                                                        
        receiver_addr.sin_family=AF_INET;                                                                                                                               
        receiver_addr.sin_port=htons(PORT);                                                                                                                             
        receiver_addr.sin_addr.s_addr=INADDR_ANY;                                                                                                                       
                                                                                                                                                                        
        int ret=connect(sender_sock,(struct sockaddr*)&receiver_addr,sizeof(receiver_addr));
                                                                                                                                                                        
        if(ret<0){
                printf("Error in connection\n");
                return 0;
        }
                                                                                                                                                                        
        printf("Connected to receiver on port %d\n",PORT);
                                                                                                                                                                        
        int next_seq_num=0;
        int window_begin=0;
                                                                                                                                                                        
        tcppacket packets[SIZE];                                                                                                                                        
        char response[SIZE],ack_response[SIZE];
        int seq_num_response;
                                                                                                                                                                        
        int i=0,j=0,count=0,retransmit=0;
        int num_packets;
                                                                                                                                                                        
        printf("Enter the number of packets to send\n");
        scanf("%d",&num_packets);
                                                                                                                                                                        
        send(sender_sock,&num_packets,sizeof(num_packets),0);
                                                                                                                                                                        
        FILE* fd;
        fd=fopen("packets.txt","r");
                                                                                                                                                                        
        if(!fd){
 printf("Error in opening the file\n");
                return 0;
        }
                                                                                                                                                                        
        printf("Window starting position - %d\nWindow ending point - %d\n\n",window_begin,window_begin+N-1);
                                                                                                                                                                        
        while(count<num_packets){
                                                                                                                                                                        
                while(i<num_packets && i<(window_begin+N)){
                                                                                                                                                                        
                        packets[i].data[0]='\0';
                        packets[i].header.seq_num=next_seq_num;                                                                                                         
                        packets[i].header.ack_flag=0;
                                                                                                                                                                        
                        if(fgets(packets[i].data,sizeof(packets[i].data),fd))
                                printf("Date to be sent: %s\n",packets[i].data);
                        else{
                                printf("No data found\n");
                                return 0;
                        }
                                                                                                                                                                        
                        printf("Do you want to drop the packet?1-Yes/0-No\n");
                        scanf("%d",&(packets[i].header.drop_flag));
                                                                                                                                                                        
                        printf("Packet number %d is sent(seq no %d)\n",i,packets[i].header.seq_num);
                                                                                                                                                                        
                        int sb=send(sender_sock,&packets[i],sizeof(tcppacket),0);
                                                                                                                                                                        
                        next_seq_num=nextseqnum(next_seq_num);                                                                                                          
                                                                                                                                                                        
                        i++;                                                                                                                                            
                }
                                                                                                                                                                        
                if(retransmit){
                                                                                                                                                                        
                        printf(".....RETRANSMISSION.....\n");
                                                                                                                                                                        
                        while(j<num_packets && j<(window_begin+N)){
		  printf("Resending packet %d\n",j);
                                                                                                                                                                        
                                                                                                                                                                        
                                packets[j].header.drop_flag=0;
                                                                                                                                                                        
                                packets[j].header.ack_flag=0;
                                                                                                                                                                        
                                int ll=send(sender_sock,&packets[j],sizeof(tcppacket),0);
                                                                                                                                                                        
                                j++;                                                                                                                                    
                                                                                                                                                                        
                        }                                                                                                                                               
                                                                                                                                                                        
                        printf("RETRANSMISSION COMPLETED...\n");
                                                                                                                                                                        
                        j=0;
                                                                                                                                                                        
                        retransmit=0;
                                                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                ack_response[0]='\0';
                                                                                                                                                                        
                seq_num_response=1;
                                                                                                                                                                        
                int rr=recv(sender_sock,&response,sizeof(response),0);
                                                                                                                                                                        
                sscanf(response,"%s %d",&ack_response,&seq_num_response);
                                                                                                                                                                        
                if(strcmp(ack_response,"ACK")==0){
                                                                                                                                                                        
                        printf("Packet number %d received(sequence number %d)\n\n",count,seq_num_response);
                                                                                                                                                                        
                        packets[count].header.ack_flag=1;
                                                                                                                                                                        
                        window_begin++;                                                                                                                                 
                                                                                                                                                                        
                        count++;                        
	    
 	                                                                                                                                                          
                        printf("Window start position - %d\nWindow end position - %d\n\n",min(window_begin,max_frame),min(max_frame,window_begin+N-1));
                                                                                                                                                                        
                }                                                                                                                                                       
                                                                                                                                                                        
                else{
                        printf("NEGATIVE ACK RECEIVED\n");
                                                                                                                                                                        
                        printf("Packet Number %d dropped(sequence number %d)\n\n",count,seq_num_response);
                                                                                                                                                                        
                        j=window_begin;                                                                                                                                 
                                                                                                                                                                        
                        retransmit=1;
                                                                                                                                                                        
                }                                                                                                                                                       
        }                                                                                                                                                               
                                                                                                                                                                        
        fclose(fd);                                                                                                                                                     
                                                                                                                                                                        
        close(sender_sock);                                                                                                                                             
                                                                                                                                                                        
        return 0;
}                                