#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define SERVPORT 5555
#define DEST_IP "192.168.1.158"
int main(int argc, char **argv)
{
    int sockfd,sock_dt;
    printf("#####################################################\n");
    printf("socket test      by pafone   19th,April,2009\n");
    printf("#####################################################\n");
    struct sockaddr_in my_addr;//local ip info
    struct sockaddr_in dest_addr; //destnation ip info
    if(argc != 3)
    {
        printf("useage:socket_client ipaddress port\n eg:socket_client \/par             192.168.1.158 5555");
        return -1;
    }
    int destport = atoi(argv[2]);
    //if(-1 == (sockfd = socket(AF_INET,SOCK_STREAM,0)) )
    if(-1 == (sockfd = socket(PF_UNIX,SOCK_STREAM,0)) )
    {
        perror("error in create socket\n");
        exit(0);
    }
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(destport);
    dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
//    bzero(&dest_addr.sin_zero,0,8);
    memset(&dest_addr.sin_zero,0,8);
//connect
    if(-1 == connect(sockfd,(struct sockaddr*)&dest_addr,sizeof(struct sockaddr)))
    {
        perror("connect error\n");
        exit(0);
    }
    int n_send_len;
    n_send_len = send(sockfd,"-f00k you.\n-why?\n-how\n",strlen("-fuck you.\n-why?\n-how\n"),0);
    printf("%d bytes sent\n",n_send_len);
    n_send_len = send(sockfd,"-**** you.\n-why?\n-how\n",strlen("-fuck you.\n-why?\n-how\n"),0);
    printf("%d bytes sent\n",n_send_len);
    while(1);
    close(sockfd);
}
