//Alex Stalter

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t Alock;
pthread_mutex_t Block;
pthread_mutex_t Clock;


void* doAB()
{

	while(1)
	{
	//grab a lock on A
	printf("AB: trying to get A lock\n");
	pthread_mutex_lock(&Alock);
	//grab a lock on B
	printf("AB: trying to get B lock\n");
	pthread_mutex_lock(&Block);
	//do stuff
	printf("AB: got them. now doing stuff\n");
	usleep(10000);
	printf("AB: Done now releasing them\n");
	//release lock on A
	pthread_mutex_unlock(&Alock);
	usleep(10000);
	//release lcok on B
	pthread_mutex_unlock(&Block);
	usleep(10000);

	}

}
void* doBC()
{ 

        while(1)
        { 
        //grab a lock on A
        printf("BC: trying to get B lock\n");
        pthread_mutex_lock(&Block);
        //grab a lock on B
        printf("BC: trying to get C lock\n");
	pthread_mutex_unlock(&Clock);
        //do stuff
        printf("BC: got them. now doing stuff\n");
        usleep(10000);
        printf("BC: Done now releasing them\n");
        //release lock on A
        pthread_mutex_unlock(&Block);
	usleep(10000);
        //release lcok on B
        pthread_mutex_unlock(&Clock);
        usleep(10000);

        }

}
void* doCA()
{ 

        while(1)
        { 
        //grab a lock on A
        printf("CA: trying to get C lock\n");
        pthread_mutex_lock(&Clock);
        //grab a lock on B
        printf("CA: trying to get A lock\n");
	pthread_mutex_lock(&Alock);
        //do stuff
        printf("CA: got them. now doing stuff\n");
        usleep(10000);
        printf("CA: Done now releasing them\n");
        //release lock on A
        pthread_mutex_unlock(&Clock);
	usleep(10000);
        //release lcok on B
        pthread_mutex_unlock(&Alock);
        usleep(10000);

        }

}


int main()
{

	pthread_t ABthread, BCthread, CAthread;
	pthread_create(&ABthread,NULL,doAB,NULL);
	pthread_create(&BCthread,NULL,doBC,NULL);
	pthread_create(&CAthread,NULL,doCA,NULL);

	pthread_join(ABthread,NULL);
	pthread_join(BCthread,NULL);
	pthread_join(CAthread,NULL);
	return 0;

}
