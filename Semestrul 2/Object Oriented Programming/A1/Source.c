#include <stdio.h>

//Verifies if parameter number is a prime number.
int isPrime(int number)
{
	for (int Index = 2; Index < number; Index++)
		if (number % Index == 0)
			return 0;
	return 1;
}
// Prints all the prime numbers until number.

void allPrimeUntilNumber(int number)
{
	for (int Index = 2; Index < number; Index++)
		if (isPrime(Index) == 1)
			printf("%d ", Index);
}



int main()
{
	//printf("Hello, World!");
	int number, numberVector, vector[50], choice;
	int MaxConsecutiveElements = 0, consecutiveElements = 0, MaxForIndex = 0;
	while (1)
	{
		printf("1. Execute first functionality.\n");
		printf("2. Insert a vector to be used for functionality 2.\n");
		printf("3. Execute second functionality.\n");
		printf("4. Exit.\n");
		printf("Your choice:");
		scanf_s("%d", &choice);
		printf("\n");
		if (choice == 1)
		{
			printf("Number=");
			scanf_s("%d", &number);
			allPrimeUntilNumber(number);
			printf("\n\n");
		}
		else if (choice == 2)
		{
			printf("Number of elements in the vector:");
			scanf_s("%d", &numberVector);
			for (int Index = 0; Index < numberVector; Index++)
			{
				printf("vector[%d]=", Index);
				scanf_s("%d", &vector[Index]);
			}
			printf("\n");
		}
		else if (choice == 3) {
			for (int Index = 0; Index < numberVector - 1; Index++)
			{
				consecutiveElements = 1;
				for (int Index2 = Index; Index2 < numberVector - 1; Index2++)
				{
					if (isPrime(vector[Index2] + vector[Index2 + 1]) == 1)
						consecutiveElements++;
					else Index2 = numberVector;

					if (consecutiveElements > MaxConsecutiveElements)
					{
						MaxConsecutiveElements = consecutiveElements;
						MaxForIndex = Index;
					}

				}
			}
			for (int Index = MaxForIndex; Index < MaxForIndex + MaxConsecutiveElements; Index++)
			{
				printf("%d", vector[Index]);
				printf(" ");
			}
			printf("\n\n");
		}
		else if (choice == 4) {
			exit(0);
		}
		else printf("Wrong input\n");

	}
	return 0;



}