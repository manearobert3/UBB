#include <stdio.h>
void sort(int arr[], int size)
{
	int i,j,k;
	for(i=0;i<size;i++)
		for(j=i;j>0;j--)
		if(arr[j]<arr[j-1])
			{
				k=arr[j];
					arr[j]=arr[j-1];
				arr[j-1]=k;
			}
}
int main()
{
	int i;
	int arr[10]={1,5,4,8,7,2,4,5,9,0};
	printf("Initial array: ");
	for(i=0;i<10;i++)
		printf("%d ", arr[i]);
	printf("\n Sorted array: ");
	sort(arr,10);
	for(i=0;i<10;i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}
