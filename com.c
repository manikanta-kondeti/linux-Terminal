#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
	char cmdStr[256], *user, hostname[256];

	memset(hostname, 0x00, sizeof(hostname));

	gethostname(hostname, sizeof(hostname));
	user = (char *)getenv("USER");

	if( user == NULL )
	{
		strcpy(user, "unknown");
	}

	while(1)
	{
		printf("%s@%s: ", user, hostname);
		memset(cmdStr, 0x00, sizeof(cmdStr));
		/*
		 * use fgets instead of gets. don't wanna be exploitable!
		 * 
		 * remember that fgets traps everything typed into the command
		 * line, event the carriage return!
		 */
		fgets(cmdStr, sizeof(cmdStr), stdin);

		if( strncmp("quit", cmdStr, 4) == 0 )
		{
			/*
			 * exit
			 */
			break;
		}
		else if( strncmp("set", cmdStr, 3) == 0 )
		{
			/*
			 * set an environment variable
			 */
			//setenv(parm1, parm2, true);
			printf("environ var not set\n");
		}
		else
		{
			/*
			 * Sure, I'm cheating.  You'd have to be a masochist (sp) to
			 * do otherwise.... or your professor requires it.
			 */
			system(cmdStr);
			/*
			 * futher thought says one could use execve()/execvp()
			 * to handle processes. but you'll want to parse out
			 * command line arguments and stuff
			 */
		}
	}

	return 0;
}
