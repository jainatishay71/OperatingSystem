#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	int n;
	printf("Enter the no of pages:\n");
	scanf("%d",&n);
	int pages[n];
	for(int i=0;i<n;i++)
		pages[i]=rand()%10+1;
	printf("Total Pages are as follows:\n");
	for(int i=0;i<n;i++)
		printf("%d ", pages[i]);
	printf("\n");
	int m;
	printf("Enter the no of frames:\n");
	scanf("%d",&m);
	int frames[m];
	for(int i=0;i<m;i++)
		frames[i]=0;
	int curr=0,pf=0;
	printf("Condition of frames:\n");
	for(int i=0;i<n;i++)
	{
		int q=0;
		for(int j=0;j<m;j++)
		{
			if(pages[i]==frames[j])
			{
				q=1;
				break;
			}
		}
		if(!q)
		{
			frames[curr]=pages[i];
			curr=(curr+1)%m;
			pf++;
		}	
		for(int i=0;i<m;i++)
			printf("%d ", frames[i]);
		printf("\n");
	}
	printf("Total no of page faults: %d\n",pf);
	printf("\n");
}