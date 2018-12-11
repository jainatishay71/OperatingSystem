#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INT_MIN -2147483647

int min(int a,int b)
{
	if(a<b)
		return a;
	return b;
}

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
			if(curr<m)
			{
				frames[curr]=pages[i];
				pf++;
				curr++;
			}
			else
			{
				int ind=-1;
				int temp[m];
				for(int j=0;j<m;j++)
					temp[j]=-1;
				for(int j=0;j<m;j++)
				{
					for(int k=i+1;k<n;k++)
					{
						if(pages[k]==frames[j] && temp[j]==-1)
						{
							temp[j]=k;
							break;
						}
					}
				}
				int mx=INT_MIN;
				for(int j=0;j<m;j++)
				{
					if(mx<temp[j])
					{
						mx=temp[j];
						ind=j;
					}
					if(temp[j]==-1)
					{
						ind=j;
						break;
					}
				}
				frames[ind]=pages[i];
				pf++;
			}
		}
		for(int j=0;j<m;j++)
			printf("%d ", frames[j]);
		printf("\n");
	}
	printf("Total page faults:%d\n",pf);
	printf("\n");
}