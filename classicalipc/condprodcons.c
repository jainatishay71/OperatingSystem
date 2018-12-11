#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define max_items 15

pthread_mutex_t mutex;
pthread_cond_t cond1,cond2;

int buff[max_items],in=0,out=0;

void *producer(void *args)
{
	int f=0,d=0;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if((in+1)%max_items==out)
			pthread_cond_wait(&cond1,&mutex);

		if(in==out)
			f=1;

		int r = rand()%100+1;
		buff[in] = r;
		printf("Item Produced %d\n", r);
		in = (in+1)%max_items;
		d++;

		if(f)
		{
			pthread_cond_signal(&cond2);
			f=0;
		}
		pthread_mutex_unlock(&mutex);
		if(d==1000)
			break;
	}
}

void *consumer(void *args)
{
	int f=0,d=0;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(in==out)
			pthread_cond_wait(&cond2,&mutex);

		if((in+1)%max_items==out)
			f=1;

		int r = buff[out];
		printf("Item Consumed %d\n", r);
		out = (out+1)%max_items;
		d++;

		if(f)
		{
			pthread_cond_signal(&cond1);
			f=0;
		}
		pthread_mutex_unlock(&mutex);
		if(d==1000)
			break;
	}
}

int main()
{
	srand(time(NULL));

	pthread_t prod,cons;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond1,NULL);
	pthread_cond_init(&cond2,NULL);

	pthread_create(&prod,NULL,&producer,NULL);
	pthread_create(&cons,NULL,&consumer,NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
}