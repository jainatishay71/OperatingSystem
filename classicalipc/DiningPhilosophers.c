// this is a program to simulate the dining philosophers problem
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#define K 5

pthread_t philosophers[K];
pthread_cond_t pcon[K];
pthread_mutex_t pmut[K];
sem_t sticks[K];

void* PickStick(void* n)
{
	int i = *(int*)n,j;
	time_t hunger,think;
	struct timespec t;
	for(j=0;j<5;j++)
	{
		printf("%d---%d\n",i+1,j);
		if(i%2==0)
		{
			sem_wait(&sticks[i]);
			sem_wait(&sticks[(i+1)%K]);
		}
		else
		{
			sem_wait(&sticks[(i+1)%K]);
			sem_wait(&sticks[i]);
		}
		//eating
		pthread_mutex_lock(&pmut[i]);
		hunger = (time_t)(1+rand()%3);
		printf("philosopher-%d is eating for %d seconds\n",i+1,(int)hunger);
		clock_gettime(CLOCK_REALTIME, &t);
		t.tv_sec+= hunger;//t.tv_nsec = 0;
		if(1)
		pthread_cond_timedwait(&pcon[i],&pmut[i],&t);
		pthread_mutex_unlock(&pmut[i]);
		if(i%2==0)
		{
			sem_post(&sticks[(i+1)%K]);
			sem_post(&sticks[i]);
		}
		else
		{
			sem_post(&sticks[i]);
			sem_post(&sticks[(i+1)%K]);
		}
		think = (time_t)(1+rand()%3);
		printf("philosopher-%d is thinking for %d seconds\n",i+1,(int)think);
		clock_gettime(CLOCK_REALTIME, &t);
		t.tv_sec+= think;t.tv_nsec = 0;
		pthread_mutex_lock(&pmut[i]);
		if(1)
		pthread_cond_timedwait(&pcon[i],&pmut[i],&t);
		pthread_mutex_unlock(&pmut[i]);
	}
	printf("philosopher-%d left\n",i+1);
}

int main()
{
	srand(time(NULL));
	int pi[K],i;
	for(i=0;i<K;i++)
	{
		pthread_mutex_init(&pmut[i],NULL);
		pthread_cond_init(&pcon[i],NULL);
		sem_init(&sticks[i],0,1);
	}
	for(i=0;i<K;i++)
	{
		pi[i] = i;
		pthread_create(&philosophers[i],NULL,PickStick,(void*)&pi[i]);
	}
	for(i=0;i<K;i++)
	{
		pthread_join(philosophers[i],NULL);
	}
}
