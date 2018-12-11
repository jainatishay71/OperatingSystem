#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

void concat(int argc,char *argv[])
{
	//printf("%d\n",argc);
	int y=0;
	for(int i=0;i<argc;i++)
	{
		if(strcmp(argv[i],">")==0)
			break;
		if(strcmp(argv[i],">>")==0)
			break;
		y++;
	}
	for(int i=1;i<y;i++)
	{
		char path[100];
		strcpy(path,"./");
		strcat(path,argv[i]);
		int fd = open(path,O_RDONLY);
		char buff[100];
		
		while(read(fd,buff,1))
			write(1,buff,1);
	}
}

int main(int argc,char *argv[])
{
	concat(argc,argv);
}
