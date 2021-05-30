#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/stat.h>  
#include <sys/msg.h>  

#define MSG_FILE "main801.c"
#define BUFSZ 512
#define PERM S_IRUSR|S_IWUSR  
struct message{
	long msg_type;
	char msg_text[BUFSZ];
};

int main801(void)
{
	int qid;
	key_t key;
	int len;
	struct message msg;

	puts("main801 enter.");

	if((key=ftok(MSG_FILE,'a'))==-1){
		printf("ftok error");
		exit(1);
	}
	printf( "key = %x\n", key);

	if((qid=msgget( IPC_PRIVATE, 0666 ))==-1){
		printf("msgget error");
		/*exit(1);*/
	}
	printf("opened queue %d\n",qid);
	puts("Please enter the message to queue:");
	if((fgets((&msg)->msg_text,BUFSZ,stdin))==NULL){
		puts("no message");
		exit(1);
	}
	msg.msg_type = getpid();
	len = strlen(msg.msg_text);
	if((msgsnd(qid,&msg,len,0))<0){
		printf("message posted");
		exit(1);
	}
	if(msgrcv(qid,&msg,BUFSZ,0,0)<0){
		printf("msgrcv");
		exit(1);
	}
	printf("message is:%s\n",(&msg)->msg_text);
	if((msgctl(qid,IPC_RMID,NULL))<0){
		printf("msgctl");
		exit(1);
	}
	exit(0);
#if 0	
	int i=0;
	for ( i = 1; i < 256; ++ i )
	    printf( "key = %x\n", ftok( "/tmp", i ) );

	return 0;
#endif

}

