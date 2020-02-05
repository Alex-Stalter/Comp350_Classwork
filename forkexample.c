#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	printf("before the fork\n");
	fork();
	fork();
	fork();
	printf("after the fork\n");
	return 0;
}
