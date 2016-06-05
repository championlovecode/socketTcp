#include <sys/types.h>  
#include <sys/socket.h>  
#include <stdio.h>  
#include <sys/un.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <stddef.h>  
#include <malloc.h>


//#define	CMD_SOCK "/var/run/rtpproxy.sock"
#define	CMD_SOCK "/run/rtpproxy.sock"
static const char *cmd_sock = CMD_SOCK;

 
/* 
 * Create a UNIX-domain socket address in the Linux "abstract namespace". 
 * 
 * The socket code doesn't require null termination on the filename, but 
 * we do it anyway so string functions work. 
 */  
int makeAddr(const char* name, struct sockaddr_un* pAddr, socklen_t* pSockLen)  
{  
    int nameLen = strlen(name);  
    if (nameLen >= (int) sizeof(pAddr->sun_path) -1)  /* too long? */  
        return -1;  
    pAddr->sun_path[0] = '\0';  /* abstract namespace */  
    strcpy(pAddr->sun_path+1, name);  
    pAddr->sun_family = AF_UNIX;  
    *pSockLen = 1 + nameLen + offsetof(struct sockaddr_un, sun_path);  
    return 0;  
}  
  
  
int main(int argc,char *argv[])  
{  
    int sockfd;  
    socklen_t len;  
    struct sockaddr_un address;  
    int result;  
    char ch = 'A';  

    //create socket   
   
    sockfd = socket(PF_UNIX, SOCK_STREAM, 0);  
    
    //name the server socket  
    //makeAddr("server_socket", &address, &len);  
    address.sun_family = AF_UNIX;  
    strcpy(address.sun_path,cmd_sock);  
    //address.sun_path[0]=0;  


    len = sizeof(address);  


	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockfd,sizeof sockfd);

    //len =  strlen(SERVER_NAME)  + offsetof(struct sockaddr_un, sun_path);  
    //connect to server  
    result = connect(sockfd, (struct sockaddr*)&address, len);  
    if(result == -1)  
    {  
        perror("opps:client1");  
        exit(1);  
    }  
    //communicate with server socket  

    int icount =0;
    int charlen = 0;
    int charlentmp = 0;
    icount=argc;
    printf("\nicount = %d\n",icount);


    int i =0;
    for(i =1;i<icount;i++)
    {
	printf("\nargv[%d]=%s",i,argv[i]);
	charlen += strlen(argv[i]);
    }

    		
    charlen += argc;
    
    printf("\nSpace Num = %d\n",argc);
    printf("\ncharlen = %d\n",charlen);


    char *mallocspace=(char *)malloc(100); 
	
    while(1)  
    {  
        //scanf("%c",&ch); 
	int j=0;

        for(i=1;i<=icount;i++)
        {
		printf("\nargv[i]=%s\n",argv[i]);
		memcpy(&mallocspace[j],&argv[i],strlen(argv[i]));
		j = strlen(argv[i]);
		mallocspace[j] ="\0";
		printf("\nmallocspace=%s\n",mallocspace[j]);
			
	}  
	
	for(i =0;i< charlen;i++)
	{
		printf("%s",mallocspace[i]);
	}

        write(sockfd, mallocspace,j);  

        printf("send to server:%s\n",argv[1]);
  
	char cmd[20] = ""; 
        read(sockfd, &cmd, 20);  
        printf("read from server:%s\n",cmd);  
        sleep(1);	
	  
          
    }  
    exit(0);  
  
}  
