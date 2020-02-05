//Alex Stalter

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//int lock;

pthread_mutex_t lock;

void slowprint(char*);

void delay(){

	usleep(rand()%1000000);

}

//this will run as a seperate thread
//defining targetfun as a pointer to a function
void* targetfunc(void* message){
	int i;
	char* msg=(char*)message;
	for(i=0;i<1000;i++){

//	printf("%s %d\n",msg,i);
	slowprint(msg);
	delay();
	}
}
//slower print function to show issues with thread proccesses
//this is a critical section of code
//if two threads run this at the same time, we get garbage on the screen
void slowprint(char* message){

//check if the door is locked before continuing
/*	while(lock==1){
	//sit here and wait
	//spin lock
}*/
//PROBLEM:Thread switch occurs here
//befroe printing lock
//	lock=1;

 //ask os to lock door and put us to sleep

	pthread_mutex_lock(&lock);


	int i=0;
	for(i=0;message[i]!='\0';i++){

	putchar(message[i]);
	usleep(rand()%100000);

}
//after printing unlock door
//	lock=0;

	pthread_mutex_unlock(&lock);

}

int main(){
	//seed the random number generator with time of day
	srand(time(0));

	//a structure to hold info about a thread
	pthread_t pthread1;
	pthread_t pthread2;
	//args1: thread object args2: attribute (NULL)
	//args3:pointer to function to call args4: arguments to call(NULL for now)
	pthread_create(&pthread1,NULL,targetfunc,(void*)"thread1 msg\n");
	pthread_create(&pthread1,NULL,targetfunc,(void*)"THREAD2 MSG\n");


	//while(1); stops main ending before thread runs
	pthread_join(pthread1,NULL);
	pthread_join(pthread2,NULL);
	return 0;

}
