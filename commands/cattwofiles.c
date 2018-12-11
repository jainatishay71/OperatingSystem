#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

void concat(char s[100],char t[100])
{
	char path[100];
	strcpy(path,"./");
	strcpy(path,s);
	int fd1 = open(path,O_RDONLY);
	
	strcpy(path,"./");
	strcpy(path,t);
	int fd2 = open(path,O_RDONLY);
	
	char buff[100];
	
	while(read(fd1,buff,1))
		write(1,buff,1);
	while(read(fd2,buff,1))
		write(1,buff,1);
}

int main(int argc,char *argv[])
{
	concat(argv[1],argv[2]);
}
