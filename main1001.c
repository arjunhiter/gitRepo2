
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <pthread.h>

#define SERVPORT 10000
#define MAXDATASIZE 1000

#define P2P_INVALID_THREAD (0)
static pthread_t gThreadId = P2P_INVALID_THREAD;


#define P2P_DBG_PRINT(content)     content

#define BACKLOG 10

#ifndef TRUE
/** Value representing the boolean/logical value false. */
#define FALSE 0
/** Value representing the boolean/logical value true. */
#define TRUE (!FALSE)
#endif

typedef char boolean;

typedef struct
{
	int     Length;
	char  Data[100]; 
}SocketMsg_Info_t;

int P2P_GetClient()
{
	int sockfd,sendbytes;
	struct hostent *host;
	struct sockaddr_in serv_addr;
	
	 /*  
	if(argc < 2){
		fprintf(stderr,"Please enter the server's hostname!\n");
		exit(1);
	}
	//if((host=gethostbyname(argv[1]))==NULL){*/
	if((host=gethostbyname("127.0.0.1"))==NULL){
		perror("gethostbyname");
		exit(1);
	}
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
	serv_addr.sin_addr=*((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero),8);
	if(connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(struct sockaddr))==-1){
		perror("connect");
		exit(1);
	}

	return sockfd;
}

void P2P_SendMsg(int sockfd)
{
	int sendbytes;
	while(1)
	{
		SocketMsg_Info_t pDo;

		bzero(&pDo,sizeof(SocketMsg_Info_t));
		
		if (&pDo != NULL)
		{
			gets(pDo.Data);
			pDo.Length = strlen(pDo.Data);
			/*scanf("%s", pDo.Data);
			//printf("input msg:%s\n",pDo.Data);*/
			if((sendbytes=send(sockfd, &pDo, sizeof(SocketMsg_Info_t), 0))==-1){
				perror("send");
				exit(1);
			}
		}
	}

}

void* 
P2P_Thread(void* arg)
{
	struct sockaddr_in server_sockaddr,client_sockaddr;
	int sin_size,recvbytes;
	int sockfd,client_fd;
	char* buf = NULL;

	buf = (char*)malloc(MAXDATASIZE);
       if (buf == NULL)
       {
		perror("buf");
       }
	bzero(buf,MAXDATASIZE);
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	printf("socket success!,sockfd=%d\n",sockfd);
	server_sockaddr.sin_family=AF_INET;
	server_sockaddr.sin_port=htons(SERVPORT);
	server_sockaddr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(server_sockaddr.sin_zero),8);
	if(bind(sockfd,(struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(1);
	}
	printf("bind success!\n");
	if(listen(sockfd,BACKLOG)==-1){
		perror("listen");
		exit(1);
	}
	printf("listening....\n");
	if((client_fd=accept(sockfd,(struct sockaddr *)&client_sockaddr,&sin_size))==-1){
		perror("accept");
		exit(1);
	}
	
	while(1)
	{
		SocketMsg_Info_t* pDo = NULL;
		
		if((recvbytes=recv(client_fd,buf,MAXDATASIZE,0))==-1){
			perror("recv");
			exit(1);
		}
		
		pDo = (SocketMsg_Info_t *)buf;
		
		if (pDo != NULL)
		{
			 if (pDo->Length > 0)
		 	{
	 			printf("received a msg :%s\n", pDo->Data);
				/*printf("received a connection :%d\n",recvbytes);*/
				printf("received msg len :%d\n", pDo->Length);				
		 	}
		}
		
	}
	close(sockfd);
}

boolean 
P2P_StartThread(void)
{
	boolean result = FALSE;
	int ret = 0;

	ret = pthread_create(&gThreadId, 
	                                              NULL, &P2P_Thread, NULL);
	if (ret != 0)
	{
		 P2P_DBG_PRINT(printf("\n[%s][%d][%s()] Create P2P server thread failed.\n", 
		       __FILE__, __LINE__, __FUNCTION__);)
	}
	else
	{
		 P2P_DBG_PRINT(printf("\n[%s][%d][%s()] Create P2P server thread succeeded.\n", 
		       __FILE__, __LINE__, __FUNCTION__);)
		 result = TRUE;
	}
	return result;
}
 
int main1001(void)
{
	boolean ret = FALSE;
	int gClientfd = -1;

	ret = P2P_StartThread();

	if (ret == FALSE)
	{
	printf("start thread error.");
	}

	while (1)
	{
	  	gClientfd = P2P_GetClient();
		if (gClientfd > 0)
		{
			P2P_SendMsg(gClientfd);
		}	
	}

	return ret;
}

