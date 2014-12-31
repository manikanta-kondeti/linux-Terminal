#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<strings.h>

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
	/* some processing before terminating. */
	execve("/bin/pwd", argv, envp);
	//execve
	return 0;
}
