#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef enum Bool
{
	False = 0,
	True = 1
} Bool;

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

Bool BinSearch(void* arr, int size, size_t elemSize, void* item, int (* compare)(void*, void*))
{
	int left = 0;
	int right = size - 1;

	while ((left <= right))
	{
		int place = (left + right) / 2;
		int comperationResult = compare(arr + (place * elemSize), item);

		if (comperationResult == 0)
		{
			return True;
		}
		else if (comperationResult == -1)
		{
			left = place + 1;
		}
		else
		{
			right = place - 1;
		}
	}

	return False;
}

int IntCompare(void* item1, void* item2)
{
	int num1 = *((int*)item1);
	int num2 = *((int*)item2);

	if (num1 == num2)
	{
		return 0;
	}

	if (num1 > num2)
	{
		return 1;
	}

	return -1;
}

Bool IntBinSearch(int* arr, int size, int item)
{
	return BinSearch(arr, size, sizeof(int), &item, IntCompare);
}

int StringCompare(void* item1, void* item2)
{
	return strcmp(*((char**)item1), *((char**)item2));
}

Bool StringBinSearch(char** arr, int size, char* item)
{
	return BinSearch(arr, size, sizeof(char*), &item, StringCompare);
}

void FreeMemory(int* intArr, int intSize, char** stringArr, int stringSize)
{
	free(intArr);
	for (int i = 0; i < stringSize; ++i)
	{
		free(stringArr[i]);
	}
	free(stringArr);
}

void main()
{
	int* intArr;
	int intSize, intToFind;
	char** stringArr, stringToFind[SIZE];
	int stringSize;
	int res;

	// The user will enter the number of integers followed by the integers.
	intArr = GetIntArr(&intSize);

	// The user will enter the integer to find
	scanf("%d", &intToFind);

	//The function searches the array using BinSearch()
	res = IntBinSearch(intArr, intSize, intToFind);

	if (res == 1)
		printf("The number %d was found\n", intToFind);
	else
		printf("The number %d was not found\n", intToFind);

	// The user will enter the number of strings (lines) followed by the strings.
	// You may assume that each line contains up to 99 characters.
	stringArr = GetStringArr(&stringSize);

	// The user will enter the string to find
	getchar();
	scanf("%[^\n]s", stringToFind);

	//The function searches the array using BinSearch()
	res = StringBinSearch(stringArr, stringSize, stringToFind);

	if (res == 1)
		printf("The string %s was found\n", stringToFind);
	else
		printf("The string %s was not found\n", stringToFind);
	FreeMemory(intArr, intSize, stringArr, stringSize);
}
