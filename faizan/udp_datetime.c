#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>
#include<string.h>
main(int argc,char* argv[]){
	time_t t;
	int sockid,rval,clen;
	struct sockaddr_in s,c;
	char m1[255],m2[255];
	system("clear");
	if(argc<3){
		printf("\nUsage %s IP Address, PortNO. ",argv[0]);
		exit(1);
	}
	sockid = socket(AF_INET,SOCK_DGRAM,0);
	if(sockid==-1){
		perror("SOCK_CRE_ERR");
		exit(1);
	}
	printf("Socket Created.");
	s.sin_family = AF_INET;
	s.sin_addr.s_addr = inet_addr(argv[1]);
	s.sin_port = htons(atoi(argv[2]));
	rval = bind(sockid,(struct sockaddr*) &s,sizeof(s));
	if(rval == -1){
		perror("Bind Error");
		exit(1);
	}
	printf("Successfully Binded.");
	clen = sizeof(c);
	rval = recvfrom(sockid,m1,sizeof(m1),0,(struct sockaddr*) &c,&clen);
	if(rval==-1){
		perror("ERR");
		exit(1);
	}
	printf("Message Received.\n");
	t = time(0);
	strcpy(m2,ctime(&t));
	rval = sendto(sockid,m2,sizeof(m2),0,(struct sockaddr*) &c,clen);
	if(rval==-1){
		perror("ERR");
		exit(1);
	}
	printf("Response Sent.\n");
	close(sockid);
}
