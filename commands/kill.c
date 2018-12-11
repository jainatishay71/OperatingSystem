#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>

int main(int argc,char *argv[])
{
	if(argc<3)
	{
		printf("The objective cannot be achieved due to fewer arguments\n");
		exit(0);
	}
	int k = kill((pid_t)atoi(argv[2]),atoi(argv[1]+1));
	if(k==0)
	{
		printf("The signal has been received successfully\n");
	}
	else
	{
		printf("The signal can't be received\n");
	}
}

