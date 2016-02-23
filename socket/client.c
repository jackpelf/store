/*
gcc client.c -o client
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_ad;
	memset(&server_ad, 0, sizeof(server_ad));
	server_ad.sin_family = AF_INET;
	server_ad.sin_port = htons(2333);
	server_ad.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if( connect(client_fd, (struct sockaddr*)&server_ad, sizeof(server_ad)) < 0 )
	{
		perror("connect error");
		exit(1);
	}
	
	char buf[0x100];
	while(1)
	{
		gets(buf);
		send(client_fd, buf, strlen(buf), 0);
		if( !strcmp(buf, "exit") )
		{
			sleep(1);
			break;
		}
		recv(client_fd, buf, sizeof(buf), 0);
		puts(buf);
	}
	close(client_fd);
	return 0;
}
