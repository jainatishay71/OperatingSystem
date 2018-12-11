#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define max_items 15

sem_t mutex,cempty,cfull;
int buff[max_items],in=0,out=0;

void *producer(void *args)
{
	int d=0;
	while(1)
	{
		sem_wait(&cempty);
		sem_wait(&mutex);

		int r = rand()%100+1;
		buff[in] = r;
		in = (in+1)%max_items;
		printf("Item Produced %d\n", r);
		d++;

		sem_post(&cfull);
		sem_post(&mutex);

		if(d==1000)
			break;
	}
}

void *consumer(void *args)
{
	int d=0;
	while(1)
	{
		sem_wait(&cfull);
		sem_wait(&mutex);

		int r = buff[out];
		out = (out+1)%max_items;
		printf("Item Consumed %d\n", r);
		d++;

		sem_post(&cempty);
		sem_post(&mutex);
		if(d==1000)
			break;
	}
}

int main()
{
	srand(time(NULL));

	pthread_t prod,cons;
	sem_init(&mutex,0,1);
	sem_init(&cfull,0,0);
	sem_init(&cempty,0,max_items);

	pthread_create(&prod,NULL,&producer,NULL);
	pthread_create(&cons,NULL,&consumer,NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
}