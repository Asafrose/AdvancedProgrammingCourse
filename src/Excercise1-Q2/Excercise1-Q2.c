#include <stdio.h>
#include <stdlib.h>

int CharToInt(char ch)
{
	return ch - 48;
}

int StringToInt(char* string)
{
	int result = 0;
	while (*string != '\0')
	{
		result = result * 10 + CharToInt(*string);
		string++;
	}
	return result;
}

void CopyString(char* sourceString, char* resultString)
{
	int index = 0;
	while (*sourceString != '\0')
	{
		resultString[index] = *sourceString;
		index++;
		sourceString++;
	}

	resultString[index] = '\0';
}

int TrimNumber(char* string)
{
	char word[100];
	int index = 0;
	while (*string == ' ')
	{
		string++;
	}
	while (*string != ' ' && *string != '\0' && *string != '\n')
	{
		word[index] = *string;
		index++;
		*string = ' ';
		string++;
	}
	word[index] = '\0';
	return StringToInt(word);
}

void PrintAsBase(int number, int base)
{
	const char IntToCharMapping[16] =
	{
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F'
	};

	if (number == 0)
	{
		printf("%c", '0');
		return;
	}

	char reversedResult[100];
	int index = 0;
	while (number != 0)
	{
		reversedResult[index] = IntToCharMapping[number % base];
		index++;
		number = number / base;
	}

	for (int i = index - 1; i >= 0; --i)
	{
		printf("%c", reversedResult[i]);
	}
}

void PrintAsRoman(int number)
{
	int values[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
	char* symbols[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

	for (int i = 12; i >= 0 && number > 0; --i)
	{
		for (int j = 0; j < number / values[i]; ++j)
		{
			printf("%s", symbols[i]);
		}
		number = number % values[i];
	}
}

void printFormattedIntegers(char* format, char* numbers)
{
	char numbersCopy[100];
	char* numbersCopyPointer = &numbersCopy[0];
	CopyString(numbers, numbersCopyPointer);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case '\0':
				return;
			case 'd':
				printf("%d", TrimNumber(numbersCopyPointer));
				break;
			case 'x':
				PrintAsBase(TrimNumber(numbersCopyPointer), 16);
				break;
			case 'o':
				PrintAsBase(TrimNumber(numbersCopyPointer), 8);
				break;
			case 'b':
				PrintAsBase(TrimNumber(numbersCopyPointer), 2);
				break;
			case 'r':
				PrintAsRoman(TrimNumber(numbersCopyPointer));
				break;
			default:
				printf("%%%c", *numbersCopyPointer);
				break;
			}
		}
		else
		{
			printf("%c", *format);
		}
		format++;
	}
}


int main()
{
	char format[100];
	char numbers[100];

	fgets(format, 100, stdin);
	fgets(numbers, 100, stdin);

	printFormattedIntegers(format, numbers);

	return 0;
}