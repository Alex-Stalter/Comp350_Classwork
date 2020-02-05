#include <stdio.h>
#include <stdlib.h>

int isprime(int n)
{
	for(int i= 2;i<n;i++){
		if(n%i==0)
		return 0;

	}
	return 1;
}
int main(int argc, char* argv[])
{
//	printf("%s",argv[1]);
//	printf("%s",argv[2]);

	int start=atoi (argv[1]);

	int end=atoi (argv[2]);

	int i;
	int count=0;

	for(i = start; i<=end;i++)
	{
		if(isprime(i))
			count++;
	}
	printf("Between %d and %d there are %d primes.\n",start,end,count);
	return count;
}

