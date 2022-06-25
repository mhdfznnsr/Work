#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<string.h>
main(int argc,char *argv[])
{
	struct sockaddr_in s,c;
	int sockid,rval,slen,clen,newsid;
	char m1[20],m2[255];
	time_t t;
	system("clear");
	if(argc<3)
	{
		printf("\n Usecase error: %s IP addr, Port \n",argv[0]);
		exit(1);
	}
	sockid=socket(AF_INET,SOCK_STREAM,0);
	if(sockid==-1){
		perror("SOCK_CRE_ERR");
		exit(1);
        }
        printf("Socket Created:\n");
        s.sin_family=AF_INET;
        s.sin_addr.s_addr=inet_addr(argv[1]);
        s.sin_port=htons(atoi(argv[2]));
        rval=bind(sockid,(struct sockaddr*) &s,sizeof(s));
        if(rval==-1){
                perror("Bind Error");
                exit(1);
        }
        printf("Successfully binded\n");
	rval = listen(sockid,5);
        if(rval==-1){
                perror("Error in listening\n");
                exit(1);
        }
	printf("\nListening\n");
        clen=sizeof(c);
	newsid = accept(sockid,(struct sockaddr *)&c,&clen);
	printf("\nAccepting");
        rval=recv(newsid,m1,sizeof(m1),0);
        if(rval==-1){
                perror("ERR");
                exit(1);
        }
        printf("Message received: %s \n",m1);
	t = time(0);
	strcpy(m1,ctime(&t));
        rval=send(newsid,m1,sizeof(m1),0);
        if(rval==-1){
                perror("ERR");
                exit(1);
        }
        printf("Response send");
        close(sockid);
}
