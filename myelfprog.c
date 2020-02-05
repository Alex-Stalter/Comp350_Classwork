#include <stdio.h>

int b=7;
int c;

int main()
{


	int a=2;
	a=a+b;
	printf("doesthisprint? %d\n",a);

	__asm__
	(
	"mov $60, %rax \n"
	"syscall\n"

	);

	return 0;
}
