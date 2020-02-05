#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 5

int queue[SIZE];
int first = 0;
int last = 0;
int stuffInQueue = 0;

pthread_mutex_t queueLock;
//pthread_mutex_t queueIsFull;

sem_t emptySpacesInQueue;
sem_t availableItemsInQueue;

void putIntoQueue(int item)
{
	pthread_mutex_lock(&queueLock);
	if(stuffInQueue==SIZE)
	{

	printf("---ERROR QUEUE IS FULL---\n");

	}else
	{
	queue[first]=item;
	first = (first+1)%SIZE;
	stuffInQueue++;
	}
        pthread_mutex_unlock(&queueLock);

}
int takeOutOfQueue()
{
	int item = 0;
	pthread_mutex_lock(&queueLock);
	if(stuffInQueue==0)
	{

	printf("---ERROR QUEUE IS EMPTY---\n");


	}else{
	item = queue[last];
	last=(last+1)%SIZE;
	stuffInQueue--;
	}
	pthread_mutex_unlock(&queueLock);
	return item;

}

void* producer()
{
	int i;
	for (i=1; ;i++)
	{
	printf("Producing value %d\n",i);
//either producer gets to put in queue or it goes to sleep
	sem_wait(&emptySpacesInQueue);

	putIntoQueue(i);
	sem_post(&availableItemsInQueue);
	usleep(rand()%2000000);

	}
}

void* consumer()
{
	for(;;)
	{
	sem_wait(&availableItemsInQueue);
	int item = takeOutOfQueue();
	printf("Consumed value %d\n",item);
	sem_post(&emptySpacesInQueue);
	usleep(rand()%2000000);
	}



}

int main()
{
	srand(time(0));
//set semephore to keep track of spaces inital value is SIZE
	sem_init(&emptySpacesInQueue,0,SIZE);
	sem_init(&availableItemsInQueue,0,0);

	pthread_t prod,cons,cons2;

	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&cons,NULL,consumer,NULL);
	pthread_create(&cons2,NULL,consumer,NULL);
	pthread_join(prod,NULL);
	pthread_join(cons,NULL);

/*	putIntoQueue(10);
	putIntoQueue(11);
	putIntoQueue(12);
	putIntoQueue(13);
	putIntoQueue(14);
	putIntoQueue(15);

	printf("%d\n",takeOutOfQueue());
	putIntoQueue(16);
        printf("%d\n",takeOutOfQueue());
	putIntoQueue(17);
        printf("%d\n",takeOutOfQueue());
*/

	return 0;

}
