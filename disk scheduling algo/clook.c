#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define INT_MAX 2147483647
#define limit 200

int main()
{
	srand(time(NULL));
	int n,r;
	printf("Enter the no of cylinders:\n");
	scanf("%d",&n);
	int cylinder[n],present[limit+1];
	for(int i=0;i<=limit;i++)
		present[i]=0;
	for(int i=0;i<n;i++)
	{
		r=rand()%limit+1;
		cylinder[i]=r;
		present[cylinder[i]]=1;
	}	
	printf("Cylinders are:\n");
	for(int i=0;i<n;i++)
		printf("%d ", cylinder[i]);
	printf("\n");
	int cost=0,head=cylinder[0];
	bool serviced[n];
	for(int i=0;i<n;i++)
		serviced[i]=false;
	serviced[0]=true;
	int mn=INT_MAX,next;
	for(int i=1;i<n;i++)
	{
		if(abs(head-cylinder[i])<mn)
		{
			mn=abs(head-cylinder[i]);
			next=cylinder[i];
		}
	}
	if(next<head)
	{
		for(int i=head;i>=0;i--)
		{
			if(present[i]==1)
			{
				cost+=abs(head-i);
				head=i;
				present[i]=0;
			}
		}
		int q=0;
		head=limit;
		for(int i=head;i>=0;i--)
		{
			if(present[i]==1)
			{
				q=1;
				cost+=abs(head-i);
				head=i;
				present[i]=0;
			}
		}
		if(q)
		{
			cost+=abs(limit-head);
		}
	}
	else
	{
		for(int i=head;i<=limit;i++)
		{
			if(present[i]==1)
			{
				cost+=abs(head-i);
				head=i;
				present[i]=0;
			}
		}
		head=0;
		int q=0;
		for(int i=head;i<=limit;i++)
		{
			if(present[i]==1)
			{
				q=1;
				cost+=abs(head-i);
				head=i;
				present[i]=0;
			}
		}
		if(q)
		{
			cost+=head;
		}
	}

	printf("Total Cost is :%d\n", cost);
}