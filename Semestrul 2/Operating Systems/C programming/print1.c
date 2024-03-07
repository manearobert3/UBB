#include <stdio.h>
int main()
{
	printf("%-5d\n",0);
	printf("%-5d\n",-1);
	printf("%-5d\n",12345);
	printf("%-5d\n",-12345);
	printf("%+5d\n",0);
	printf("%+5d\n",-1);
	printf("%+5d\n",12345);
	printf("%+5d\n",-12345);
	return 0;
}
