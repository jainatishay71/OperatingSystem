#include<stdio.h>
#include<sys/sem.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include <sys/types.h>

#define MAXCHAIRS 4

int	nextCustomerNo = 1;
int	first = 0, last = 0;
int	waitingCustomerCount = 0;
pthread_mutex_t	lck;
pthread_cond_t custCond[MAXCHAIRS];
int	custNos[MAXCHAIRS];
pthread_cond_t brbrCond;

void WakeUpBarber()
{
	pthread_cond_signal(&brbrCond);
}

void CustomerWait(int chair)
{
	pthread_cond_wait(&custCond[chair], &lck);	
}

int CheckVacancyAndWait(void)
{
	int chair;
	int custNo;
	pthread_mutex_lock(&lck);
	if (waitingCustomerCount == MAXCHAIRS)
	{
		pthread_mutex_unlock(&lck);
		return 0;
	}
	else
	{
		chair = last;
		custNo = custNos[chair] = nextCustomerNo++;
		last = (chair + 1) % MAXCHAIRS;
		waitingCustomerCount++;

		if (waitingCustomerCount == 1)
			WakeUpBarber();
	
		CustomerWait(chair);
		pthread_mutex_unlock(&lck);
		return custNo;
	}
}

void CheckCustomerAndSleep(void)
{
	pthread_mutex_lock(&lck);
	if (waitingCustomerCount == 0)
		pthread_cond_wait(&brbrCond, &lck);
}

void ServiceCustomer()
{
	int custNo;
	int chair;

	chair = first;
	first = (first + 1) % MAXCHAIRS;
	custNo = custNos[chair];
	waitingCustomerCount--;

	pthread_cond_signal(&custCond[chair]);
	pthread_mutex_unlock(&lck);

	printf("Barber servicing %d customer\n",custNo);
	sleep(3);
}

void * Barber(void *x)
{
	while (1)
	{
		CheckCustomerAndSleep();
		ServiceCustomer();
	}
}

void * Customer(void *x)
{
	int custno;
	while (1)
	{
		custno = CheckVacancyAndWait();

		if (custno != 0)
		{
			printf("Customer %d getting serviced ...\n",custno);
			sleep(3);
		}
		else
		{
			printf("No chair is vacant and customer leaving ...\n");
			sleep((time(NULL) % 5) + 1);
		}
	}
}

int main()
{
	int i;
	pthread_mutex_init(&lck,NULL);
	for(i=0;i<MAXCHAIRS;i++)
	{
		pthread_cond_init(&custCond[i],NULL);
	}
	pthread_t brbr, cust[MAXCHAIRS+1];

	pthread_create(&brbr, NULL, Barber, 0);
	

	for (i=0;  i<MAXCHAIRS+1; i++)
		pthread_create(&cust[i], NULL, Customer, NULL);
	
	for ( ; ; )
		;
	return 0;
}
