#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TrimStringFirstLetter(char* string)
{
	while (*string != '\0')
	{
		*string = *(string + 1);
		string++;
	}
}

void RemoveFromIndex(char*** stringArrayPointer, unsigned int* stringArraySize, unsigned int index)
{
	for (unsigned int i = index; i < *stringArraySize; ++i)
	{
		(*stringArrayPointer)[i] = (*stringArrayPointer)[i + 1];
	}

	*stringArrayPointer = realloc(*stringArrayPointer, sizeof(char*) * (*stringArraySize - 1));
	(*stringArraySize)--;
}

unsigned int FreeStringArrayUnusedSpace(char*** stringArray, unsigned int* stringArraySize)
{
	unsigned int removedIndexes = 0;
	for (int i = *stringArraySize - 1; i >= 0; --i)
	{
		unsigned int const stringSize = strlen((*stringArray)[i]);

		if (stringSize == 0)
		{
			free((*stringArray)[i]);
			RemoveFromIndex(stringArray, stringArraySize, i);
			removedIndexes++;
		}
		else
		{
			(*stringArray)[i] = realloc((*stringArray)[i], sizeof(char) * (stringSize + 1));
		}
	}

	return removedIndexes;
}

void SwapPointers(char** pointer1, char** pointer2)
{
	char* temp = *pointer1;
	*pointer1 = *pointer2;
	*pointer2 = temp;
}

unsigned int GetPtrToCharsArraySize(char** ptrToCharsArray)
{
	unsigned int size = 0;
	while (*ptrToCharsArray != NULL)
	{
		size++;
		ptrToCharsArray++;
	}

	return  size;
}

void SortPointers(char** pointers)
{
	const unsigned int size = GetPtrToCharsArraySize(pointers);

	for (unsigned int i = 0; i < size - 1; ++i)
	{
		for (unsigned int j = 0; j < size - i - 1; ++j)
		{
			if (pointers[j] < pointers[j + 1])
			{
				SwapPointers(pointers + j, pointers + j + 1);
			}
		}
	}
}

unsigned int RemoveFromStrArray(char*** strArray, unsigned int strArraySize, char** ptrToCharsArray)
{
	SortPointers(ptrToCharsArray);
	while (*ptrToCharsArray != NULL)
	{
		TrimStringFirstLetter(*ptrToCharsArray);
		ptrToCharsArray++;
	}
	
	return FreeStringArrayUnusedSpace(strArray , &strArraySize);
}


char** SetPtrToCharsArray(char** strArray)
{
	int size;
	int strArrayRow, strArrayCol;

	scanf("%d", &size); // Get number of ptrs
	char** res = (char**)malloc(sizeof(char*) * (size + 1)); // Add 1 for NULL at the end

	for (int i = 0; i < size; i++)
	{
		scanf("%d", &strArrayRow);
		scanf("%d", &strArrayCol);
		res[i] = strArray[strArrayRow] + strArrayCol;
	}

	res[size] = NULL; // Set the last one to NULL

	return res;
}

char** getStrArrayInput(int* size)
{
	scanf("%d", size);

	getchar(); // ignore \n after number of lines

	char** stringArray = malloc(sizeof(char*) * *size);

	for (int i = 0; i < *size; ++i)
	{
		int stringSize = 0;
		char* currentString = 0;

		char currentChar = (char)getchar();
		while (currentChar != '\n')
		{
			currentString =
				stringSize == 0
					? malloc(sizeof(char))
					: realloc(currentString, sizeof(char) * (stringSize + 1));

			currentString[stringSize] = currentChar;
			stringSize++;
			currentChar = (char)getchar();
		}

		currentString =
			stringSize == 0
				? malloc(sizeof(char))
				: realloc(currentString, sizeof(char) * (stringSize + 1));
		currentString[stringSize] = '\0';
		stringArray[i] = currentString;
	}

	return stringArray;
}

void printArray(char** strArray, unsigned int strSize)
{
	for (unsigned int i = 0; i < strSize; ++i)
	{
		printf("%s\n", strArray[i]);
	}
}

void freeArray(char** strArray, unsigned int strSize)
{
	for (unsigned int i = 0; i < strSize; ++i)
	{
		free(strArray[i]);
	}

	free(strArray);
}

int main()
{
	char** strArray;
	unsigned int strArraySize;

	strArray = getStrArrayInput(&strArraySize);
	// Get the size and strings from user (can't assume max size for each string)
	char** ptrToCharsArray = SetPtrToCharsArray(strArray);
	const unsigned int res = RemoveFromStrArray(&strArray, strArraySize, ptrToCharsArray);
	printArray(strArray, strArraySize - res);

	// Free memory
	freeArray(strArray, strArraySize - res);
	free(ptrToCharsArray);
}
