#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("The objective can't be completed due to fewer arguments\n");
		exit(0);
	}
	char path[100];
	strcpy(path,"./");
	strcat(path,argv[1]);
	int r = unlink(path);
	if(r==0)
	{
		printf("The selected file has been removed.\n");
	}
	else
	{
		printf("Some error occured!\n");
	}
}

