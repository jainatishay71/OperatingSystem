#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

int main(int argc,char *argv[])
{
	DIR *dp = opendir(argv[1]);
	struct dirent *dnt = readdir(dp);
	while(dnt!=NULL)
	{
		printf("%s\n",dnt->d_name);
		dnt = readdir(dp);
	}
}
