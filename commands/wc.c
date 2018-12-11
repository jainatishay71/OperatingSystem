#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
	FILE *fp;
	fp = fopen(argv[1],"r");
	int lc=0,wc=0,cc=0,flag=0;
	char ch;
	while((ch = fgetc(fp))!= EOF)
	{
		if(ch=='\n')
		{
			lc++;cc++;
			flag=1;
		}
		else if(ch==' ')
		{
			cc++;
			while(ch==' ')
			{
				cc++;
				ch=fgetc(fp);
			}
			if(ch=='\n')	
				lc++;
			wc++;
		}
		else
		{
			cc++;
			if(flag==1)
			{
				wc++;
				flag=0;
			}
		}
	}
	printf(" %d ",lc);
	printf("%d ",wc+1);
	printf("%d ",cc);
	printf("%s\n",argv[1]);
}
