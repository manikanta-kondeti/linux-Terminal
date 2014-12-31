#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>
#include<errno.h>
#include<sys/types.h>
#include<wait.h>


struct Process
{
	pid_t pid;
	char name[100];
	int flag_status;
};

typedef struct Process P;


int plen = 0;
P p1[100];
int z;


int in(char *s,int x)
{
	int l = strlen(s);
	int i,sum = 0;
	for(i = x;i <l;i++)
	{
		sum = sum*10 + s[x]-48;
	}	
	return sum;

}



void sig_handler1(int signum)
{
	printf("signal %d\n",signum);
	if(signum == 2 || signum == 20)
	{
		printf("\nEnter \"quit\" to terminate the program\n");
	}
	return;
}
void  signal_handler(int sig)
{
	int sign;
	z = waitpid(WAIT_ANY,NULL,WNOHANG);
	int i;

	for(i = 0; i< plen; i++)
	{
		if (p1[i].pid == z)
		{
			p1[i].flag_status = -1;
			break;
		}
	}
	return ;
}



int main( int argc, char *argv[] )
{
	signal(SIGINT,  sig_handler1);
	signal(SIGTSTP, sig_handler1);

	char  *user, hostname[256],pwd[256];
	char *c1=NULL,*c2=NULL,temp[256],d[100],pd[100];

	memset(hostname, 0x00, sizeof(hostname));
	gethostname(hostname, sizeof(hostname));
	user = (char *)getenv("USER");

	if( user == NULL )
	{
		strcpy(user, "unknown");
	}
	int i;
	for (i = 0;i < 100;i++)
	{
		p1[i].flag_status = 0;
	}
	while(1)
	{
		pid_t main1 = getpid();

		int i,flag = 0;
		getcwd(pwd,256);
		printf("[%s@%s %s] ", user, hostname,pwd);

		char string[256];
		fgets(string,256,stdin);
		int j = 0;
		c1 = strtok(string," ");
		if (c1[strlen(c1)-1] == '\n')
		{
			c1[strlen(c1)-1] = '\0';
			c2 = "";
		}

		else
		{
			c2 = strtok(NULL," ");
			c2[strlen(c2)-1] = '\0';
		}
		printf("'%s' '%s'\n",c1,c2);
		if(strcmp(c1,"quit") == 0)
		{
			exit(0);
		}

		if (strcmp(c1,"hist")==0 || (c1[0] == '!'))
		{

			if(c1[0] == '!')
			{
				int l = in(c1,5);
				pid_t pid = fork();
				if(pid == 0){
					printf("%d %s\n",plen-l,p1[plen-l].name);
					_exit(0);
				}
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[plen].pid = pid;
					strcpy(temp,c1);
					strcpy(p1[plen].name,strcat(temp,c2));
					p1[plen++].flag_status = 0;// process is alive
					continue;

				}
			}
			else if(c1[4] != '\0')
			{
				int l = in(c1,4);
				pid_t pid = fork();
				if(pid == 0)
				{
					int e;
					for(e = plen-1;e >=plen-l;e--)
					{
						printf("%d %s\n",plen-e-1,p1[e].name);
					}
					_exit(0);
				}
				else{
					int hello;
					pid = wait(&hello);
					p1[plen].pid = pid;
					strcpy(temp,c1);
					strcpy(p1[plen].name,strcat(temp,c2));
					p1[plen++].flag_status = 0;// process is alive
					continue;
				}


			}
			else
			{
				pid_t pid = fork();
				if(pid == 0)
				{
					int e;
					for(e = plen-1;e >=0;e--)
					{
						printf("%d %s\n",plen-e-1,p1[e].name);
					}
					_exit(0);
				}
				else{
					int hello;
					pid = 	wait(&hello);
					p1[plen].pid = pid;
					strcpy(temp,c1);
					strcpy(p1[plen].name,strcat(temp,c2));
					p1[plen++].flag_status = 0;
					continue;
				}

			}

		}

		if (strcmp(c1,"pid") == 0)
		{

			if(strcmp(c2,"current") == 0)
			{

				pid_t pid = fork();
				if (pid == 0)
				{
					int q,count= 0;
					for (q = 0 ; q < plen; q++)
					{
						if (p1[q].flag_status == 1)
						{
							printf("%d %s %d\n",count++,p1[q].name,p1[q].pid);
						}
					}
				}
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[plen].pid = pid;
					strcpy(temp,c1);
					strcpy(p1[plen].name,strcat(temp,c2));
					p1[plen++].flag_status = 0;
					continue;

				}
			}
			else if(strcmp(c2,"all") == 0)
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					int q,count= 0;
					for (q = 0 ; q < plen; q++)
					{
						printf("%d %s %d\n",count++,p1[q].name,p1[q].pid);
					}
				}
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[plen].pid = pid;
					strcpy(temp,c1);
					strcpy(p1[plen].name,strcat(temp,c2));
					p1[plen++].flag_status = 0;
					continue;

				}

			}
			else
			{
				pid_t pid = fork();
				if (pid == 0)
					printf("pid = %d\n",main1);
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[plen].pid = pid;
					strcpy(temp,c1);
					strcpy(p1[plen].name,strcat(temp,c2));
					p1[plen++].flag_status = 0;
					continue;
				}
			}

		}
		pid_t pid = fork();
		if(pid == 0)
		{
			getcwd(pd,100);
			plen = 0;
			for (i = 0;i < 100;i++)
			{
				p1[i].flag_status = 0;
			}

			printf("%s %s\n",c1,c2);

			if (strcmp(c1,"cd") == 0)
			{
				_exit(0);
			}
			if (strcmp(c2,"") == 0)
			{
				if (strcmp(c1,"./a.out") != 0)
				{
					execlp(c1,c1,NULL);
				}
			}
			else
			{

				if (strcmp(c1,"./a.out") != 0)
				{
					printf("%s %s\n",c1,c2);
					execlp(c1,c1,c2,NULL);
				}
			}

			if (strcmp(c1,"./a.out") != 0)
			{
				_exit(0);
			}
		}
		else if(strcmp(c2,"&") == 0 || c1[strlen(c1)-1] == '&')
		{
			printf("bg process\n");
			p1[plen].pid = pid;
			strcpy(temp,c1);
			strcpy(p1[plen].name,strcat(temp,c2));
			p1[plen++].flag_status = 1;
		
			int status;
			signal(SIGCHLD,signal_handler);
		}
		else
		{
			p1[plen].pid = pid;
			strcpy(temp,c1);
			strcpy(p1[plen].name,strcat(temp,c2));
			p1[plen].flag_status = 1;

			if(strcmp(c1,"cd") == 0)
			{
				printf("cwd = %s\n",getcwd(d,100));
				if(strcmp(c2,"")== 0)
				{
					chdir(pd);
				}
				else
				{
					chdir(c2);
				}
			}
			int status;
			pid_t p = wait(&status);

			p1[plen++].flag_status = -1;

		}
	}

	return 0;
}

