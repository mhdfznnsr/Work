#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
main(int argc,char *argv[])
{
	struct sockaddr_in s,c;
	int sockid,rval,slen,clen;
	char m1[20],m2[255];
	system("clear");
	if(argc<3)
	{
		printf("\n Usecase error: %s IP addr, Port \n",argv[0]);
		exit(1);
	}
	sockid=socket(AF_INET,SOCK_DGRAM,0);
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
        clen=sizeof(c);
        rval=recvfrom(sockid,m1,sizeof(m1),0,(struct sockaddr*) &c,&clen);
        if(rval==-1){
                perror("ERR");
                exit(1);
        }
        printf("Message received\n");
        rval=sendto(sockid,m1,sizeof(m1),0,(struct sockaddr*) &c,clen);
        if(rval==-1){
                perror("ERR");
                exit(1);
        }
        printf("Response send");
        close(sockid);
}
