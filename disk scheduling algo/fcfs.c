#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
	for(int i=1;i<n;i++)
	{
		cost+=(abs(cylinder[i]-head));
		head=cylinder[i];
	}
	printf("Total Cost is :%d\n", cost);
}