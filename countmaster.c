#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{

	int divisions = atoi(argv[3]);
	int upperbound = atoi(argv[2]);
	int lowerbound = atoi(argv[1]);
	int total = 0;

	char* arguments[4];

	int range = upperbound - lowerbound;
	printf("Range: %d\n",range);
	int interval = range/divisions;
	printf("Interval: %d\n",interval);

	arguments[0]="./countprimes";
	arguments[1]=argv[1];
	arguments[2]=argv[2];
	arguments[3]=NULL;

	int childids[divisions];
	for(int i = 0;i<divisions;i++){
		char start[50];
		char end[50];

		int startNumber = lowerbound + (interval*i);
		int endNumber;
		if(i+1==divisions){
		endNumber = upperbound;
		}else{
		endNumber = lowerbound + (interval*(i+1))-1;
		}

		sprintf(start,"%d",startNumber);
		arguments[1]=start;
		sprintf(end," %d",endNumber);
		arguments[2]=end;
	        arguments[3]=NULL;

		int processid = fork();
		if(processid ==0){
		execvp("./countprimes",arguments);
		}else{
		childids[i]=processid;
		}
	}
	for(int j = 0;j<divisions;j++){
	int status;
	waitpid(childids[j],&status,0);
	status = WEXITSTATUS(status);
	total = total+status;
}
	printf("Total: %d\n",total);
	return 0;
}
