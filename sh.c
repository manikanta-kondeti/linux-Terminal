#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>
#include<errno.h>
#include<sys/types.h>
#include<wait.h>
struct process{
	pid_t pid;
	char name[100];
	int flag;
};
typedef struct process process;
int processlen = 0;
process p1[100];
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
void sig_handler1(int signum){
	printf("signal %d\n",signum);
	if(signum == 2 || signum == 20){
		printf("\nEnter \"quit\" to terminate the program\n");
	}
	//signal(SIGINT, sig_handler1);
	//signal(SIGTSTP, sig_handler1);
	return;
}
void  signal_handler(int sig)
{
	//	printf("Guru Prakash\n");
	int sign;
	int z = waitpid(WAIT_ANY,NULL,WNOHANG);
	//printf("guru pid current = %d\n",z);
	int i;

	for(i = 0; i< processlen; i++)
	{
		if (p1[i].pid == z)
		{
			printf("exited normally\n");
			p1[i].flag = -1;
			break;
		}
	}
	return ;
}
int main( int argc, char *argv[] )
{
	signal(SIGINT,  sig_handler1);
	signal(SIGTSTP, sig_handler1);

	char  *user, hostname[256],pwd[256],d[100];
	char *cmd1=NULL,*cmd2=NULL,temp[256];

	memset(hostname, 0x00, sizeof(hostname));//initialising the hostname string
	gethostname(hostname, sizeof(hostname));//gets the host name
	user = (char *)getenv("USER");//gets the user

	if( user == NULL )
	{
		strcpy(user, "unknown");
	}

	int i;
	for (i = 0;i < 100;i++)
		p1[i].flag = 0;
	//int processlen = 0;
	int s = 5;
	char pd[100];
	getcwd(pd,100);
	while(1)
	{
		pid_t main1 = getpid();

		int i,flag = 0;
		getcwd(pwd,256);
		/*if(strcmp(pd,))
		  {

		  }*/
		sleep(1);
		printf("[%s@%s %s] ", user, hostname,pwd);

		char cmdStr[256];
		//	memset(cmdStr, 0x00, sizeof(cmdStr));
		fgets(cmdStr,256,stdin);
		//	printf("the command is %s\n",cmdStr);


		int j = 0;
		cmd1 = strtok(cmdStr," ");
		if (cmd1[strlen(cmd1)-1] == '\n'){
			//printf("adsf\n");
			cmd1[strlen(cmd1)-1] = '\0';
			cmd2 = "";
		}

		else{
			cmd2 = strtok(NULL," ");
			cmd2[strlen(cmd2)-1] = '\0';
		}
		//	printf("'%s' '%s'\n",cmd1,cmd2);
		if(strcmp(cmd1,"quit") == 0)
		{
			//	printf(" sachin guru\n");
			exit(0);
		}

		//cmd2[strlen(cmd2)-1]='\0';

		//user defined function
		if ((cmd1[0] == 'h' && cmd1[1] == 'i' && cmd1[2] == 's' && cmd1[3] == 't') || (cmd1[0] == '!'))
		{

			if(cmd1[0] == '!')
			{
				int l = in(cmd1,5);
				pid_t pid = fork();
				if(pid == 0){
					printf("%d %s\n",processlen-l,p1[processlen-l].name);
					_exit(0);
				}
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[processlen].pid = pid;
					strcpy(temp,cmd1);
					strcpy(p1[processlen].name,strcat(temp,cmd2));
					p1[processlen++].flag = 0;// process is alive
					continue;

				}
			}
			else if(cmd1[4] != '\0')
			{
				int l = in(cmd1,4);
				pid_t pid = fork();
				if(pid == 0)
				{
					int e;
					for(e = processlen-1;e >=processlen-l;e--)
					{
						printf("%d %s\n",processlen-e-1,p1[e].name);
					}
					_exit(0);
				}
				else{
					int hello;
					pid = wait(&hello);
					p1[processlen].pid = pid;
					strcpy(temp,cmd1);
					strcpy(p1[processlen].name,strcat(temp,cmd2));
					p1[processlen++].flag = 0;// process is alive
					continue;
				}


			}
			else
			{
				pid_t pid = fork();
				if(pid == 0)
				{
					int e;
					for(e = processlen-1;e >=0;e--)
					{
						printf("%d %s\n",processlen-e-1,p1[e].name);
					}
					_exit(0);
				}
				else{
					int hello;
					pid = 	wait(&hello);
					p1[processlen].pid = pid;
					strcpy(temp,cmd1);
					strcpy(p1[processlen].name,strcat(temp,cmd2));
					p1[processlen++].flag = 0;// process is alive
					continue;
				}

			}

		}

		if (strcmp(cmd1,"pid") == 0)
		{

			if(strcmp(cmd2,"current") == 0)
			{

				pid_t pid = fork();
				if (pid == 0)
				{
					int q,count= 0;
					for (q = 0 ; q < processlen; q++)
					{
						if (p1[q].flag == 1)
							printf("%d %s %d\n",count++,p1[q].name,p1[q].pid);
					}
					_exit(0);
				}
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[processlen].pid = pid;
					strcpy(temp,cmd1);
					strcpy(p1[processlen].name,strcat(temp,cmd2));
					p1[processlen++].flag = 0;// process is alive
					continue;

				}
			}
			else if(strcmp(cmd2,"all") == 0)
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					int q,count= 0;
					for (q = 0 ; q < processlen; q++)
					{
						printf("%d %s %d\n",count++,p1[q].name,p1[q].pid);
					}
					_exit(0);
				}
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[processlen].pid = pid;
					strcpy(temp,cmd1);
					strcpy(p1[processlen].name,strcat(temp,cmd2));
					p1[processlen++].flag = 0;// process is alive
					continue;

				}

			}
			else
			{
				pid_t pid = fork();
				if (pid == 0){
					printf("pid = %d\n",main1);
					_exit(0);
				}
				else
				{
					int hello;
					pid = 	wait(&hello);
					p1[processlen].pid = pid;
					strcpy(temp,cmd1);
					strcpy(p1[processlen].name,strcat(temp,cmd2));
					p1[processlen++].flag = 0;// process is alive
					continue;
				}
			}

		}
		//if(strcmp(cmd1,"./a.out"))
		pid_t pid = fork();

		if(pid == 0)// child process
		{
			getcwd(pd,100);
			processlen = 0;
			//process p1[100];
			for (i = 0;i < 100;i++)
				p1[i].flag = 0;

			//printf("%s %s\n",cmd1,cmd2);

			if (strcmp(cmd1,"cd") == 0)
			{
				_exit(0);
			}
			//printf("in child%s %s\n",cmd1,cmd2);
			if (strcmp(cmd2,"") == 0)
			{
				//printf("guru\n");
				if (strcmp(cmd1,"./a.out") != 0)
					execlp(cmd1,cmd1,NULL);
			}
			else{

				if (strcmp(cmd1,"./a.out") != 0){
					printf("%s %s\n",cmd1,cmd2);
					execlp(cmd1,cmd1,cmd2,NULL);}
			}
			//	printf("in child%s %s\n",cmd1,cmd2);

			if (strcmp(cmd1,"./a.out") != 0)
				_exit(0);
			printf("chow\n");
		}
		else if(strcmp(cmd2,"&") == 0 || cmd1[strlen(cmd1)-1] == '&')
		{
			//printf("bg process\n");
			p1[processlen].pid = pid;
			strcpy(temp,cmd1);
			strcpy(p1[processlen].name,strcat(temp,cmd2));
			p1[processlen++].flag = 1;// process is alive

			if(strcmp(cmd1,"cd") == 0)
			{
				chdir(cmd2);
				//printf("cwd = %s\n",getcwd(d,100));
			}
			int status;
			signal(SIGCHLD,signal_handler);
			//	 printf("kanta\n");
			//pid_t p = wait(&status);

			//p1[processlen++].flag = -1;


			sleep(1);
		}
		else
		{
			p1[processlen].pid = pid;
			strcpy(temp,cmd1);
			//	printf("qwer %s %s %d\n",cmd1,cmd2,strcmp(cmd1,"cd"));
			strcpy(p1[processlen].name,strcat(temp,cmd2));
			p1[processlen].flag = 1;// process is alive

			if(strcmp(cmd1,"cd") == 0)
			{
				//	printf("cwd = %s\n",getcwd(d,100));
				if(strcmp(cmd2,"")== 0)
				{
					chdir(pd);
				}
				else
				{
					chdir(cmd2);
				}
			}
			int status;
			pid_t p = wait(&status);

			p1[processlen++].flag = -1;

			//	printf("parent\n");
		}
	}

	return 0;
}
