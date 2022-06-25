#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
main(int argc,char *argv[])
{
	struct sockaddr_in s;
	int sockid,rval,slen;
	char sym[20],ip[255];
	system("clear");
	if(argc<3)
	{
		printf("\n Usecase error: %s IP addr, Port \n",argv[0]);
		exit(1);
	}
	sockid=socket(AF_INET,SOCK_DGRAM,0);
	if(sockid==-1)
	{
		perror("Sock_CRT_ERR:");
		exit(1);
	}
	s.sin_family=AF_INET;
	s.sin_addr.s_addr=inet_addr(argv[1]);
	s.sin_port=htons(atoi(argv[2]));
	
	printf("Enter the symbolic name:\n");
	scanf("%s",sym);
	slen=sizeof(s);
	rval=sendto(sockid,sym,sizeof(sym),0,(struct sockaddr*)&s,slen);
	if(rval==-1)
	{
		perror("ERR_IN_SND");
		exit(1);
	}
	printf("Waiting for response from DNS server \n");
	rval=recvfrom(sockid,ip,sizeof(ip),0,(struct sockaddr*)&s,&slen);
	if(rval==-1)
	{
		perror("ERR_IN_RCV");
		exit(1);
	}
	printf("IP address of %s is %s\n",sym,ip);
	close(sockid);
}
 

