#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>
#include<errno.h>
#include<sys/types.h>
#include<wait.h>

int main(int argc, char **argv, char **envp)
{
	char str[100],hostname[100],*user;
	getcwd(str,256);
	printf("pwd - %s\n",str);
	memset(hostname, 0x00, sizeof(hostname));//initialising the hostname string
	gethostname(hostname, sizeof(hostname));//gets the host name
	printf("hostname - %s\n",hostname);
	user=(char *)getenv("USER");
	printf("username - %s\n",user);
	printf("[%s@%s:%s]\n",user,hostname,str);
	char *cmd1=NULL,s[100],cmd[100];
	printf("hii\n");
	fgets(cmd,256,stdin);
	printf("hii\n");
	cmd1=strtok(cmd," ");
	printf("hii\n");
	printf("%s\n",cmd1);
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		printf("Hello World in Child !\n");
		execve("/bin/cd", argv, envp);
	}
	else
	{
		wait(NULL);
	printf("Hello World in parent !\n");
		return 0;
	}
	return 0;
}
