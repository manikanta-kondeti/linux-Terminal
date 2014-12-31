#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>



static char  *search_path[100];
int attach_path(char *cmd)
{
	char ret[100];
	int index;
	int fd;
	bzero(ret, 100);
	for(index=0;search_path[index]!=NULL;index++) {
		strcpy(ret, search_path[index]);
		strncat(ret, cmd, strlen(cmd));
		if((fd = open(ret, O_RDONLY)) > 0) {
			strncpy(cmd, ret, strlen(ret));
			close(fd);
			return 0;
		}
	}
	return 0;
}







int main(int argc, char *argv[], char *envp[])
{
	char c,tmp[10];
	/* do some initializations. */
	while(c != '\n') 
	{
		c = getchar();
		printf("%c\n",c);
		switch(c) 
		{
			case '\n': /* parse and execute. */
				bzero(tmp, sizeof(tmp));
				break;
			default: strncat(tmp, &c, 1);
				break;
		}
	}
	printf("%d\n",attach_path(tmp));
	printf("%s\n",tmp);
	/* some processing before terminating. */
	execve("/bin/tmp", argv, envp);
	//execve
	return 0;
}
