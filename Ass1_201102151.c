#include <stdio.h>
#include<wait.h>
#include<signal.h>
#include <stdlib.h>
#include<sys/types.h>
#include <string.h>
#include<errno.h>
#include <unistd.h>


struct Node
{
	pid_t pid;
	char name[100];
	int flag_status;
};

typedef struct Node P;



int atoin(char *string,int num);

int global_zombie;
P p1[100];

int plen = 0;

void  sh(int s)
{
	int i;
	global_zombie = waitpid(WAIT_ANY,NULL,WNOHANG);
	for(i = 0; i< plen; i++)
	{
		if (p1[i].pid == global_zombie)
		{
			p1[i].flag_status = -1;
			break;
		}
	}
	return;
}


void sh1(int s)
{
	if(s == 2 || s == 20)
	{
		printf("....  Please enter 'quit'  ....");
	}
	return;
}



int main( )
{

	int initializer;
	for (initializer=0;initializer<100;initializer++)
	{
		p1[initializer].flag_status = 0;
	}

	char *c1=NULL,*c2=NULL;

	char  *user, hostname[256],pwd[256],temp[256],d[100],pd[100];


	user = (char *)getenv("USER");

	memset(hostname, 0x00, sizeof(hostname));
	gethostname(hostname, sizeof(hostname));

	signal(SIGTSTP, sh1);
	signal(SIGINT,  sh1);
	while(1)
	{
		pid_t parent_pid = getpid();

		int i,flag=0,j=0;
		getcwd(pwd,256);
		printf("[%s@%s %s] ", user, hostname,pwd);

		char string[256];
		fgets(string,256,stdin);
		//		int j = 0;
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
		if(strcmp(c1,"quit") == 0)
		{
			exit(0);
		}
		if (strcmp(c1,"hist")==0 || (c1[0] == '!'))
		{
			if(c1[4] != '\0')
			{
				int val = atoin(c1,4);
				pid_t pid = fork();
				if(pid == 0)
				{
					int i;
					for(i=plen-1;i>=plen-val;i--)
					{
						printf("%d %s\n",plen-i-1,p1[i].name);
					}
					_exit(0);
				}
				else
				{
					int hello;

					pid = wait(&hello);

					p1[plen].pid = pid;

					strcpy(temp,c1);

					strcpy(p1[plen].name,strcat(temp,c2));
					p1[plen++].flag_status = 0;

					continue;

				}


			}
			else if(c1[0] == '!')
			{
				int val = atoin(c1,5);
				pid_t pid = fork();
				if(pid == 0)
				{
					printf("%d %s\n",plen-val,p1[plen-val].name);

					_exit(0);
				}
				else
				{
					int g;
					pid=wait(&g);


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
				if(pid == 0)
				{
					int e;
					for(e=plen-1;e >=0;e--)
					{
						printf("%d %s\n",plen-e-1,p1[e].name);
					}
					_exit(0);
				}
				else
				{
					int hello;
					pid = wait(&hello);
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
					_exit(0);
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
					_exit(0);
				}
				else
				{
					int dc;
					pid = 	wait(&dc);
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
				{
					printf("pid = %d\n",parent_pid);
					_exit(0);
				}
				else
				{
					int hello;
					pid = wait(&hello);
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

			//printf("%s %s\n",c1,c2);

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
			p1[plen].pid = pid;

			strcpy(temp,c1);

			strcpy(p1[plen].name,strcat(temp,c2));

			p1[plen++].flag_status = 1;

			signal(SIGCHLD,sh);



			sleep(1);
		}
		else
		{

			p1[plen].flag_status = 1;

			p1[plen].pid = pid;

			strcpy(temp,c1);

			strcpy(p1[plen].name,strcat(temp,c2));


			if(strcmp(c1,"cd") == 0)
			{

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

int atoin(char *string,int num)
{
	int l = strlen(string);
	int i,sum = 0;
	for(i = num;i <l;i++)
	{
		sum = sum*10 + string[num]-48;
	}	
	return sum;

}

