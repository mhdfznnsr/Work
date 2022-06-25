#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
main(int argc,char *argv[])
{
	struct sockaddr_in s;
	int sockid,rval,slen;
	char M1[20],M2[255];
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
	
	printf("Enter Message \n");
	scanf("%s",M1);
	slen=sizeof(s);
	rval=sendto(sockid,M1,sizeof(M1),0,(struct sockaddr*)&s,slen);
	if(rval==-1)
	{
		perror("ERR_IN_SND");
		exit(1);
	}
	printf("Message sent succesfully \n");
	rval=recvfrom(sockid,M2,sizeof(M2),0,(struct sockaddr*)&s,&slen);
	if(rval==-1)
	{
		perror("ERR_IN_RCV");
		exit(1);
	}
	printf("Message received  is %s\n",M2);
	close(sockid);
}
 

