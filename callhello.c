//callhello will run another program called hello

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	printf("callhello is about to call program ./hello\n");

	char* arguments[2];
	arguments[0]="./hello"; //convention is make the fule name the first argument last argument is null
	arguments[1]=NULL;

	//exevp will run another program
	int proccessid = fork();
	printf("my proccess id is %d\n",getpid());
	printf("fork returned the number %d \n",proccessid);
	if(proccessid==0)
	{
	execvp("./hello", arguments);
	}
	else
	{
	int status;
	waitpid(proccessid,&status ,0);
	status = WEXITSTATUS(status);
	printf("status is %d \n",status);
//	printf("the option vars hold: WCLONE is %x, WALL is %x, WNOTHREAD is %x\n",__WCLONE,__WALL,__WNOTHREAD);
	printf("callhello: hello is done\n");
//	printf("Some pointer stuff to follow: \n\n");

//	int value = 17;
//	int* pointertovalue = &value; //address of

//	int something = *pointertovalue; //get value at this address
//	printf("value: %d, pointertovalue %x, something %d \n", value,pointertovalue,something);
}
	return 0;
}
