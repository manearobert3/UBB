#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	int a[10], n, i;
	//input size
	printf("Input array size:");
	scanf("%d", &n);

	//verifying if n is a negative number or a string
	if(n<=0 || isalpha(n)!=0)
	{
		printf("Invalid size.");
		return 1;
	}

	//input elements in an array
	printf("Input array elements:\n");
	for (i=0;i<n;i++)
	{	printf("a[%d]=",i);
		scanf("%d", &a[i]);
		if(isalpha(a[i])!=0)
		{	printf("Invalid data");
			return 2;
		}
	}

	//maximum & minimum
	int maximum = a[0], minimum = a[0];
	for (i=1;i<n;i++)
	{
		if(a[i]>maximum)
			maximum = a[i];
		if(a[i]<minimum)
			minimum=a[i];
	}

	//print results
	printf("The maximum value of the array is %d.\n", maximum);
	printf("The minimum value of the array is %d.\n", minimum);
	return 0;
}
