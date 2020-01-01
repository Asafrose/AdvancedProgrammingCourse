#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef int Bool;

Bool IsUpper(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

void TrimUpperCaseLetters(char** stringPointer)
{
	for (int i = strlen(*stringPointer) - 1; i >= 0; --i)
	{
		if (IsUpper((*stringPointer)[i]))
		{
			for (int j = i; j < strlen(*stringPointer); ++j)
			{
				(*stringPointer)[j] = (*stringPointer)[j + 1];
			}
		}
	}

	*stringPointer = realloc(*stringPointer, sizeof(char) * (strlen(*stringPointer) + 1));
}

char* ReadStringFromFile(int stringSize, FILE* file)
{
	char* result = malloc(sizeof(char) * (stringSize + 1));

	for (int i = 0; i < stringSize; ++i)
	{
		result[i] = (char)fgetc(file);
	}
	result[stringSize] = '\0';

	return result;
}

char** GetTrimStringArray(char* fname, unsigned int x)
{
	FILE* file = fopen(fname, "rb");
	char** trimmedStringArray = malloc(sizeof(char*) * x);
	for (int i = 0; i < x; ++i)
	{
		int stringSize;
		fread(&stringSize, sizeof(int), 1, file);
		char* currentString = ReadStringFromFile(stringSize, file);
		TrimUpperCaseLetters(&currentString);
		trimmedStringArray[i] = currentString;
	}
	fclose(file);
	return trimmedStringArray;
}

size_t GetBiggerStringLength(char* str1, char* str2)
{
	int str1Size = strlen(str1);
	int str2Size = strlen(str2);
	if (str1Size > str2Size)
	{
		return sizeof(char) * (str1Size + 1);
	}

	return sizeof(char) * (str2Size + 1);
}

void OrderStringArray(char** stringArray, int stringArraySize)
{
	for (int i = 0; i < stringArraySize; ++i)
	{
		for (int j = i + 1; j < stringArraySize; ++j)
		{
			if (strcmp(stringArray[i], stringArray[j]) > 0)
			{
				char* temp = stringArray[i];
				stringArray[i] = stringArray[j];
				stringArray[j] = temp;
			}
		}
	}
}

void WriteStringArrayToNewFile(char** stringArray, int stringArraySize, char* filePath)
{
	FILE* file = fopen(filePath, "w");
	for (int i = 0; i < stringArraySize; ++i)
	{
		fputs(stringArray[i], file);
		fputc('\n', file);
	}
	fclose(file);
}

void FreeStringArray(char** stringArray, int stringArraySize)
{
	for (int i = 0; i < stringArraySize; ++i)
	{
		free(stringArray[i]);
	}
	free(stringArray);
}

char* GetOutputFileName(char* inputFileName)
{
	char* result = malloc(sizeof(char) * (strlen(inputFileName) + 5));
	strcpy(result, inputFileName);
	strcat(result, ".txt");
	return result;
}

void Exe5Q1(char* fname, unsigned int x)
{
	char** stringArray = GetTrimStringArray(fname, x);
	OrderStringArray(stringArray, x);
	char* outputFilePath = GetOutputFileName(fname);
	WriteStringArrayToNewFile(stringArray, x, outputFilePath);
	free(outputFilePath);
	FreeStringArray(stringArray, x);
}

//int main()
//{
//	Exe5Q1("C:\\Dev\\AdvancedProgrammingCourse\\src\\x64\\Debug\\test_file.bin", 5);
//	return 0;
//}
