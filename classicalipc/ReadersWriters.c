// This is a simulation of readers-writers problem with pthreads and exclusive and shared lock implementation


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

struct Node
{
	int data;
	struct Node* next;
};

// this is the linked list which will be used as a buffer for the process

struct Node* head = NULL,*tail = NULL;

void addEnd(int d)
{
	if(head==NULL)
	{
		head = (struct Node*)malloc(sizeof(struct Node));
		head->data = d;
		head->next = NULL;
		tail = head;
	}
	else
	{
		tail->next = (struct Node*)malloc(sizeof(struct Node));
		tail->next->data = d;
		tail->next->next = NULL;
		tail = tail->next;
	}
}

struct Lock
{
	pthread_mutex_t pmut;
	pthread_cond_t canRead,canWrite;
	int noOfPendingReaders,noOfPendingWriters;
	int noActive;
}lock;


void sharedLock(struct Lock* l)
{
	pthread_mutex_lock(&(l->pmut));
	l->noOfPendingReaders++;
	if(l->noOfPendingWriters>0)
		pthread_cond_wait(&l->canRead,&l->pmut);
	while(l->noActive<0)
		pthread_cond_wait(&(l->canRead),&(l->pmut));
	l->noActive++;
	l->noOfPendingReaders--;
	pthread_mutex_unlock(&(l->pmut));
}

void sharedUnlock(struct Lock* l)
{
	pthread_mutex_lock(&(l->pmut));
	l->noActive--;
	if(l->noActive==0)
		pthread_cond_signal(&(l->canWrite));
	pthread_mutex_unlock(&(l->pmut));
}

void exlusiveLock(struct Lock* l)
{
	pthread_mutex_lock(&(l->pmut));
	l->noOfPendingWriters++;
	while(l->noActive!=0)
		pthread_cond_wait(&(l->canWrite),&(l->pmut));
	l->noActive = -1;
	l->noOfPendingWriters--;
	pthread_mutex_unlock(&(l->pmut));
};

void exclusiveUnlock(struct Lock* l)
{
	pthread_mutex_lock(&(l->pmut));
	l->noActive = 0;
	if(l->noOfPendingReaders>0)
		pthread_cond_broadcast(&(l->canRead));
	else
		pthread_cond_signal(&(l->canWrite));
	pthread_mutex_unlock(&(l->pmut));
};

void* readFunc(void* k)
{
	int i = *(int*)k;
	struct Node* q;
	q = head;
	sharedLock(&lock);
	while(q!=NULL)
	{
		printf("Thread-%d is reading %d\n",i,q->data);
		q = q->next;
		// sleep(1);
	}
	sharedUnlock(&lock);
	printf("Thread-%d terminated\n",i);
}

void* writeFunc(void* k)
{
	int i = *(int*)k,j,c1,c2;
	exlusiveLock(&lock);
	c1 = 1+rand()%5;
	printf("Thread-%d will write %d values\n",i,c1);
	for(j=0;j<c1;j++)
	{
		c2 = 1+rand()%20;
		printf("Thread-%d is writing %d\n",i,c2);
		addEnd(c2);
		// sleep(1);
	}
	exclusiveUnlock(&lock);
	printf("Thread-%d terminated\n",i);
}

int main()
{
	srand(time(NULL));
	pthread_t p[5];
	int pi[5],type,i;
	lock.noActive = 0;
	lock.noOfPendingWriters = 0;
	lock.noOfPendingReaders = 0;
	pthread_mutex_init(&(lock.pmut),NULL);
	pthread_cond_init(&(lock.canRead),NULL);
	pthread_cond_init(&(lock.canWrite),NULL);
	for(i=0;i<5;i++)
	{
		pi[i] = i;
		type = 1+rand()%2;
		if(type==1)
			{
				printf("Thread-%d is reader\n",i);
				pthread_create(&p[i],NULL,readFunc,(void*)&pi[i]);
			}
		else
			{
				printf("Thread-%d is writer\n",i);
				pthread_create(&p[i],NULL,writeFunc,(void*)&pi[i]);
			}
	}
	for(i=0;i<5;i++)
		pthread_join(p[i],NULL);
	return 0;
}