#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
main(int argc,char *argv[])
{
	struct sockaddr_in s,c;
	int sockid,rval,slen,clen,flag=0;
	char sym[20],ip[20],dnsfile[20],dnsname[20];
	FILE *fptr;
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
	printf("DNS server is waiting for client\n");
	printf("Enter DNS filename: ");
	scanf("%s",dnsfile);
	fptr = fopen(dnsfile,"r");
	if(fptr == NULL){
		perror("\nError in opening file\n");
		exit(1);
	}
        clen=sizeof(c);
        rval=recvfrom(sockid,sym,sizeof(sym),0,(struct sockaddr*) &c,&clen);
        if(rval==-1){
                perror("ERR");
                exit(1);
        }
        printf("IP requested for %s \n",sym);
	while((fscanf(fptr,"%s%s",dnsname,ip)!=EOF)){
		if(strcmp(dnsname,sym)==0){
        		rval=sendto(sockid,ip,sizeof(ip),0,(struct sockaddr*) &c,clen);
        		if(rval==-1){
                		perror("\nError in sending IP address\n");
				exit(1);
			}
			flag = 1;
		}
		printf("\nFLag value in loop is %d\n",flag);
		if(flag==1) break;
	}
	if(flag==0){
		printf("\nInvalid Domain Name\n");
        	rval=sendto(sockid,"Not Found",sizeof("Not Found"),0,(struct sockaddr*) &c,clen);
        	if(rval==-1){
			perror("ERROR in sendind\n");
                	exit(1);
		}
        }
        fclose(fptr);
        close(sockid);
}
