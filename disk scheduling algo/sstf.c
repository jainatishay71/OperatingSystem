#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define INT_MAX 2147483647

int main()
{
	srand(time(NULL));
	int n;
	printf("Enter the no of cylinders:\n");
	scanf("%d",&n);
	int cylinder[n];
	for(int i=0;i<n;i++)
		cylinder[i]=rand()%200+1;
	printf("Cylinders are:\n");
	for(int i=0;i<n;i++)
		printf("%d ", cylinder[i]);
	printf("\n");
	int cost=0,head=cylinder[0];
	bool serviced[n];
	for(int i=0;i<n;i++)
		serviced[i]=false;
	serviced[0]=true;
	while(1)
	{
		int mn=INT_MAX,ind=-1;
		for(int i=0;i<n;i++)
		{
			if(serviced[i]==false)
			{
				if(mn>abs(head-cylinder[i]))
				{
					mn=abs(head-cylinder[i]);
					ind=i;
				}
			}
		}
		if(mn!=INT_MAX)
		{
			cost+=mn;
			serviced[ind]=true;
			head=cylinder[ind];
		}	
		else
			break;
	}
	printf("Total Cost is :%d\n", cost);
}