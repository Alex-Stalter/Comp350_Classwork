#include <stdlib.h>
#include <stdio.h>

//prototype
void doPrint(char*);

int main(int argc,char* argv[])
{
	doPrint("Hi from target program\n");

	return 3;
}

void doPrint(char* astring)
{
	printf("%s",astring);
}
