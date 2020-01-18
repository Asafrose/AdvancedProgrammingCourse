#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

int* GetIntArr(int* arrSize)
{
	scanf("%d", arrSize);
	int* result = malloc(*arrSize * sizeof(int));

	for (int i = 0; i < *arrSize; ++i)
	{
		scanf("%d", result + i);
	}
	return result;
}

void Copy(char* sourceStartingPointer, char* destinationStartingPointer, size_t elementSize)
{
	for (int i = 0; i < elementSize; ++i)
	{
		*(destinationStartingPointer + i) = *(sourceStartingPointer + i);
	}
}

void* Scramble(void* arr, size_t elemSize, int n, int* indArr)
{
	void* result = malloc(n * elemSize);
	for (int i = 0; i < n; ++i)
	{
		Copy(arr + (indArr[i] * elemSize), result + (i * elemSize), elemSize);
	}
	return result;
}


int* ScrambleInt(int* intArr, int arrSize, int* indArr)
{
	return Scramble(intArr, sizeof(int), arrSize, indArr);
}

char** ScrambleString(char** stringArr, int size, int* indArr)
{
	return Scramble(stringArr, sizeof(char*), size, indArr);
}

void PrintIntArr(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

char** GetStringArr(int* arrSize)
{
	scanf("%d", arrSize);
	char** result = malloc(*arrSize * sizeof(char*));

	for (int i = 0; i < *arrSize; ++i)
	{
		getchar();
		result[i] = malloc(sizeof(char) * 100);
		scanf("%[^\n]s", result[i]);
	}
	return result;
}

void PrintStringArr(char** stringArr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%s\n", stringArr[i]);
	}
}

void FreeStringArr(char** arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		free(arr[i]);
	}
	free(arr);
}

void FreeMemory(
	int* intArr,
	int* scrambleIntArr,
	int intSize,
	char** stringArr,
	char** scrambleStringArr,
	int stringSize)
{
	free(intArr);
	free(scrambleIntArr);
	free(scrambleStringArr);
	FreeStringArr(stringArr, stringSize);
}

void main()
{
	int* intArr, * scrambleIntArr;
	int intSize;
	char** stringArr, ** scrambleStringArr;
	int stringSize, i;
	int indArr[SIZE];

	// The user will enter the number of integers followed by the integers.
	intArr = GetIntArr(&intSize);

	// The user will enter the indices
	for (i = 0; i < intSize; i++)
		scanf("%d", &indArr[i]);

	//The function scrambles the array using Scramble()
	scrambleIntArr = ScrambleInt(intArr, intSize, indArr);

	PrintIntArr(scrambleIntArr, intSize);

	// The user will enter the number of strings (lines) followed by the strings.
	// You may assume that each line contains up to 99 characters.
	stringArr = GetStringArr(&stringSize);

	// The user will enter the indices
	for (i = 0; i < stringSize; i++)
		scanf("%d", &indArr[i]);

	//The function scrambles the array using Scramble()
	scrambleStringArr = ScrambleString(stringArr, stringSize, indArr);

	PrintStringArr(scrambleStringArr, stringSize);
	FreeMemory(intArr, scrambleIntArr, intSize, stringArr, scrambleStringArr, stringSize);
}