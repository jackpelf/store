/*
gcc server.c -o server
*/
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_ad;
	server_ad.sin_family = AF_INET;
	server_ad.sin_port = htons(2333);
	server_ad.sin_addr.s_addr = htonl(INADDR_ANY);
	if( bind(server_fd, (struct sockaddr*)&server_ad, sizeof(server_ad)) == -1)
	{
		perror("bind error");
		exit(1);
	}
	if( listen(server_fd, 20) == -1)
	{
		perror("listen error");	
		exit(1);
	}
	
	struct sockaddr_in client_ad;
	socklen_t s_len = sizeof(client_ad);
	while(1)
	{
		int conn = accept(server_fd, (struct sockaddr*)&client_ad, &s_len);
		if(conn < 0)
		{
			perror("accept error");
			exit(1);
		}
		pid_t pid = fork();
		if( pid == 0)
		{
			char buf[0x100];
			while(1)
			{
				int len = recv(conn, buf, sizeof(buf), 0);
				buf[len] = 0;
				if( !strcmp(buf, "exit") )
					break;
				puts(buf);
				send(conn, buf, len, 0);
			}
			close(conn);
		}
	}
	close(server_fd);
	return 0;
}
