#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>

void parse(char *in,char **argv)
{
	while(*in != '\0')
	{
		while(*in == ' ' || *in == '\t' || *in == '\n')
			*in++ = '\0';
		*argv++ = in;
		while(*in != '\0' && *in != ' ' && *in != '\t' && *in != '\n')
			in++;
	}
	*argv = '\0';
}

void execute(char **argv)
{
	pid_t pid;
	int status;
	if((pid = fork())<0)
	{
		printf("*** ERROR: forking child process failed\n");
	        exit(1);
	}
	else if(pid == 0)
	{
		if(execvp(*argv,argv)<0)
		{
//			printf("ERROR execution failed\n");
			exit(1);
		}
	}
	else
	{
		while(wait(&status)!=pid)
			;
	}
}

int main(void)
{
	printf("\n");
	char in[1024];
	char *argv[64];
	while(1)
	{
		printf("$ ");
		fgets(in,1024,stdin);
		in[strlen(in)-1] = '\0';
		printf("\n");
		parse(in,argv);
		if( strcmp( argv[0],"exit" )==0 )
			exit(0);
		execute(argv);
	}
}
