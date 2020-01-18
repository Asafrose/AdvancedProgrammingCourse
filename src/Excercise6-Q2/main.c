#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Byte;

int CountOneBits(Byte* byteArray, int byteArraySize)
{
	int count = 0;
	for (int i = 0; i < byteArraySize; ++i)
	{
		for (Byte currentByte = byteArray[i]; currentByte != 0; currentByte >>= 1)
		{
			count += (currentByte & 1);
		}
	}

	return count;
}

int* filter(
	int* numbers,
	int size,
	Byte* predicate,
	int* newSize)
{
	int predicateSize = size / 8;
	*newSize = CountOneBits(predicate, predicateSize);
	int* result = malloc(sizeof(int) * *newSize);

	int currentIndex = 0;
	for (int i = 0; i < predicateSize; ++i)
	{
		Byte currentByte = predicate[i];
		for (int j = 0; j < 8; ++j)
		{
			if (currentByte & (1 << j))
			{
				result[currentIndex] = numbers[(8 * i) + j];
				currentIndex++;
			}
		}
	}

	return result;
}

Byte* XorBytes(Byte* byteArr1, Byte* byteArr2, int size)
{
	Byte* result = malloc(sizeof(Byte) * size);
	for (int i = 0; i < size; ++i)
	{
		result[i] = byteArr1[i] ^ byteArr2[i];
	}

	return result;
}

int* XorFilter(int* numbers, int size, Byte* pred1, Byte* pred2, int* newSize)
{
	Byte* combinedPred = XorBytes(pred1, pred2, size / 8);
	int* result = filter(numbers, size, combinedPred, newSize);
	free(combinedPred);
	return result;
}

void main()
{
	int i, pr, new_size, size;
	int* numbers;
	Byte* pred1, * pred2;

	int* some_numbers1;
	int* some_numbers2;

	printf("Please enter the number of numbers:\n");
	scanf("%d", &size);

	numbers = (int*)malloc(size * sizeof(int));
	pred1 = (char*)malloc(size / 8 * sizeof(char));
	pred2 = (char*)malloc(size / 8 * sizeof(char));

	printf("Please enter the numbers:\n");

	for (i = 0; i < size; i++)
		scanf("%d", &numbers[i]);

	printf("Please enter the first filter bits in hexa:\n");

	for (i = 0; i < size / 8; i++)
	{
		scanf("%x", &pr);
		pred1[i] = (char)pr;
	}

	some_numbers1 = filter(numbers, size, pred1, &new_size);

	printf("The numbers selected are:\n");

	for (i = 0; i < new_size; i++)
		printf("%d ", some_numbers1[i]);

	printf("Please enter the second filter bits in hexa:\n");

	for (i = 0; i < size / 8; i++)
	{
		scanf("%x", &pr);
		pred2[i] = (char)pr;
	}

	some_numbers2 = XorFilter(numbers, size, pred1, pred2, &new_size);

	printf("The numbers selected are:\n");

	for (i = 0; i < new_size; i++)
		printf("%d ", some_numbers2[i]);

	free(numbers);
	free(some_numbers1);
	free(pred1);
	free(some_numbers2);
	free(pred2);
}

