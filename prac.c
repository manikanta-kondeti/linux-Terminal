#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>

int main(int argc, char *argv[], char *envp[])
{
	char *string,str1[10];
	int i=0;
	char temp[100];
	char c = '\0';
	printf("[Mani_SHELL]");
	while(1) 
	{
		c = getchar();
		if(c == '\n')
		{
			printf("hii\n");
			temp="/bin"+string;
			printf("%s\n",temp);
			execve(str1,argv,envp);
		}
		string[i++];
	}
	printf("\n");
	return 0;
}
