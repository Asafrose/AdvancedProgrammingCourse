#include <stdio.h>

int GetNumberOfDigits(int number)
{
	int numberOfDigits = 0;
	do
	{
		numberOfDigits++;
		number = number / 10;
	}
	while (number > 0);

	return numberOfDigits;
}

int GetNumberInput()
{
	int result;
	scanf("%d", &result);
	return result;
}

void PrintTable(const int tableSize)
{
	for (int i = 1; i <= tableSize; ++i)
	{
		for (int j = 1; j <= tableSize; ++j)
		{
			printf(
				"%*d",
				j == 1
					? GetNumberOfDigits(j * tableSize)
					: GetNumberOfDigits(j * tableSize) + 1,
				i * j);
		}

		printf("\n");
	}
}

void Q1()
{
	PrintTable(10);
}

void Q2()
{
	PrintTable(GetNumberInput());
}

int FindChar(char* string, char character)
{
	int index = 0;
	while (*string != '\0')
	{
		if (*string == character)
		{
			return index;
		}

		index++;
		string++;
	}

	return -1;
}

int main()
{
	Q2();
	return 0;
}
