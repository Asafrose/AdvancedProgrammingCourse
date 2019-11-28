#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


void CopyArray(int** source, int startingIndex, int size, int** destination)
{
	for (int i = 0; i < size; i++)
	{
		destination[i] = source[startingIndex + i];
	}
}

void PointerMerge(int** arr, int left, int middle, int right, int isAscending)
{
	int const leftBlockSize = middle - left + 1;
	int const rightBlockSize = right - middle;

	int** leftArray = (int**)malloc(sizeof(int*) * leftBlockSize);
	int** rightArray = (int**)malloc(sizeof(int*) * rightBlockSize);

	CopyArray(arr, left, leftBlockSize, leftArray);
	CopyArray(arr, middle + 1, rightBlockSize, rightArray);

	int rightIndex = 0;
	int leftIndex = 0;
	int arrayIndex = left;
	while (rightIndex < rightBlockSize && leftIndex < leftBlockSize)
	{
		if (isAscending)
		{
			if (*leftArray[leftIndex] <= *rightArray[rightIndex])
			{
				arr[arrayIndex] = leftArray[leftIndex];
				leftIndex++;
			}
			else
			{
				arr[arrayIndex] = rightArray[rightIndex];
				rightIndex++;
			}
		}
		else
		{
			if (*leftArray[leftIndex] >= *rightArray[rightIndex])
			{
				arr[arrayIndex] = leftArray[leftIndex];
				leftIndex++;
			}
			else
			{
				arr[arrayIndex] = rightArray[rightIndex];
				rightIndex++;
			}
		}
		arrayIndex++;

		
	}

	for (int i = rightIndex; i < rightBlockSize; i++)
	{
		arr[arrayIndex] = rightArray[i];
		arrayIndex++;
	}
	for (int i = leftIndex; i < leftBlockSize; i++)
	{
		arr[arrayIndex] = leftArray[i];
		arrayIndex++;
	}

	free(leftArray);
	free(rightArray);
}

void PointerMergeSort(int** arr, int left, int right, int isAscending)
{
	if (left >= right)
	{
		return;
	}

	int middle = (left + right) / 2;
	PointerMergeSort(arr, left, middle, isAscending);
	PointerMergeSort(arr, middle + 1, right, isAscending);
	PointerMerge(arr, left, middle, right, isAscending);
}

void PointerSort(int* arr, unsigned int size, int isAscending, int*** destination)
{
	int** tempDestination = malloc(size * sizeof(int*));

	for (unsigned int i = 0; i < size; i++)
	{
		tempDestination[i] = arr + i;
	}

	PointerMergeSort(tempDestination, 0, size - 1, isAscending);

	*destination = tempDestination;
}

int** PointerSort(int* arr, unsigned int size, int isAscending)
{
	int** destination;

	PointerSort(arr, size, isAscending, &destination);

	return destination;
}

void printPointers(int** pointers, int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", *pointers[i]);
	}
}

int main()
{
	unsigned int size;
	int arr[100];
	int** pointers;
	int ascendFlag;

	printf("Please enter the number of items:\n");
	scanf("%u", &size);

	for (unsigned int i = 0; i < size; i++)
		scanf("%d", &arr[i]);

	scanf("%d", &ascendFlag);
	PointerSort(arr, size, ascendFlag, &pointers);
	printf("The sorted array:\n"); //Print the sorted array
	printPointers(pointers, size);
	free(pointers);

	return 0;
}
