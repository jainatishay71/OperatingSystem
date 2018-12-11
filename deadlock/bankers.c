#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	int n,m;
	printf("Enter the no of processes:\n");
	scanf("%d",&n);
	printf("Enter the no of resources:\n");
	scanf("%d",&m);
	int allocation[n][m];
	int maxi[n][m];
	int available[m];
	int need[n][m];
	bool finish[n];
	for(int i=0;i<n;i++)
		finish[i]=false;
	for(int i=0;i<m;i++)
		available[i]=rand()%30+1;

	printf("Available Total Resources:\n");
	for(int i=0;i<m;i++)
		printf("%d ", available[i]);
	printf("\n");

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			maxi[i][j]=rand()%(available[j]);
			if(available[j]<0)
			{
				available[j]+=maxi[i][j];
				maxi[i][j]=0;
			}
			if(maxi[i][j]==0)
			{
				allocation[i][j]=0;
				need[i][j]=maxi[i][j];
			}
			else
			{
				allocation[i][j]=rand()%(maxi[i][j]);
				available[j]-=allocation[i][j];
				need[i][j]=maxi[i][j]-allocation[i][j];
			}
		}
	}
	printf("\n");
	printf("Allocated\tMaximum\t\tNeeded\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			printf("%d ", allocation[i][j]);
		}
		printf("\t\t");
		for(int j=0;j<m;j++)
		{
			printf("%d ", maxi[i][j]);
		}
		printf("\t\t");
		for(int j=0;j<m;j++)
		{
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}

	printf("Remaining Resources:\n");
	for(int i=0;i<m;i++)
		printf("%d ", available[i]);
	printf("\n");

	int cnt=0;
	while(1)
	{
		cnt++;
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(finish[i]==false)
			{
				flag=1;
				int q=0;
				for(int j=0;j<m;j++)
				{
					if(need[i][j]>available[j])
					{
						q=1;
						break;
					}
				}
				if(q==0)
				{
					for(int j=0;j<m;j++)
					{
						available[j]+=allocation[i][j];
						finish[i]=true;
					}
				}
			}
		}
		if(flag==0)
		{
			printf("No Deadlock\n");
			break;
		}
		if(cnt>1000)
		{
			printf("There exists a Deadlock and hence resources allocation not possible!\n");
			break;
		}
	}
}