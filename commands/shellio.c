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
		printf("ERROR: Forking child process failed\n");
	        exit(1);
	}
	else if(pid == 0)
	{
		//printf("entered into child\n");
		int i=0,in=0,out=0,app=0;
		while(argv[i])
		{
			if(strcmp(argv[i],"<")==0)
			{
				in=1;
				break;
			}
			if(strcmp(argv[i],">")==0)
			{
				out=1;
				break;
			}
			if(strcmp(argv[i],">>")==0)
			{
				app=1;
				break;
			}
			i++;
		}
		i++;
		if(out)
		{
			int fd1 = open(argv[i],O_WRONLY | O_CREAT | O_TRUNC , 644);
			dup2(fd1,STDOUT_FILENO);
			close(fd1);
		}
		if(app)
		{
			int fd2 = open(argv[i],O_WRONLY | O_APPEND);
			dup2(fd2,STDOUT_FILENO);
			close(fd2);
		}
		if(in)
		{
			int fd3 = open(argv[i],O_RDONLY);
			dup2(fd3,STDIN_FILENO);
			close(fd3);
			char *targv[64];
			char line[1024];
			fgets(line,1024,stdin);
			line[strlen(line)-1] = '\0';
			parse(line,targv);
			execute(targv);
			exit(1);
		}
		if(execvp(*argv,argv)<0)
		{
			printf("ERROR execution failed\n");
			exit(1);
		}
		exit(1);
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
	while(1)
	{
		char in[1024];
		char *argv[64];
		printf("$ ");
		fgets(in,1024,stdin);
		in[strlen(in)-1] = '\0';
		printf("\n");
		parse(in,argv);
		if( strcmp( argv[0],"exit" )==0 )
		{
			exit(0);
		}
		execute(argv);
	}
}
