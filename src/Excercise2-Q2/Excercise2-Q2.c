#define _CRT_SECURE_NO_WARNINGS

#include  <stdio.h>
#include <stdlib.h>

typedef struct monom
{
	int Coefficient;
	int Power;
} Monom;

void CopyPolynom(Monom* source, unsigned int size, Monom* destination)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		destination[i] = source[i];
	}
}


int GetPowerIndex(Monom* polynom, unsigned int polynomSize, int power)
{
	for (int i = 0; i < polynomSize; ++i)
	{
		if (polynom[i].Power == power)
		{
			return i;
		}
	}

	return -1;
}

int IsPowerExist(
	Monom* polynom,
	unsigned int polynomSize,
	int power)
{
	return GetPowerIndex(polynom, polynomSize, power) != -1;
}

void AddMonom(Monom** polynom, unsigned int* polynomSize, Monom monom)
{
	if (monom.Coefficient == 0)
	{
		return;
	}

	if (IsPowerExist(*polynom, *polynomSize, monom.Power))
	{
		(*polynom)[GetPowerIndex(*polynom, *polynomSize, monom.Power)].Coefficient += monom.Coefficient;
	}
	else
	{
		*polynom = (Monom*)realloc(*polynom, sizeof(Monom) * (*polynomSize + 1));
		*(*polynom + *polynomSize) = monom;
		*polynomSize = *polynomSize + 1;
	}
}

void SwapMonoms(Monom* monomA, Monom* monomB)
{
	const Monom temp = *monomA;
	*monomA = *monomB;
	*monomB = temp;
}

void SortPolynom(Monom* polynom, unsigned int size)
{
	for (unsigned int i = 0; i < size - 1; ++i)
	{
		for (unsigned int j = 0; j < size - i - 1; ++j)
		{
			if (polynom[j].Power < polynom[j + 1].Power)
			{
				SwapMonoms(&polynom[j], &polynom[j + 1]);
			}
		}
	}
}

Monom* GetPolynom(unsigned int* polynomSize)
{
	char stoppingIndicator;
	Monom currentMonom;

	Monom* polynom = malloc(sizeof(Monom));
	*polynomSize = 0;

	do
	{
		scanf("%d", &currentMonom.Coefficient);
		scanf("%d%c", &currentMonom.Power, &stoppingIndicator);

		AddMonom(&polynom, polynomSize, currentMonom);
	}
	while (stoppingIndicator != '\n');

	SortPolynom(polynom, *polynomSize);

	return polynom;
}

Monom* SumPolynoms(Monom* PolynomA, unsigned int sizeA, Monom* PolynomB, unsigned int sizeB, unsigned int* resultSize)
{
	Monom* result = malloc(sizeA * sizeof(Monom));
	*resultSize = sizeA;
	CopyPolynom(PolynomA, sizeA, result);

	for (unsigned int i = 0; i < sizeB; ++i)
	{
		AddMonom(&result, resultSize, PolynomB[i]);
	}

	SortPolynom(result, *resultSize);
	return result;
}

Monom* MultiplyPolynomByMonom(Monom* polynom, unsigned int size, Monom monom)
{
	Monom* result = malloc(size * sizeof(Monom));
	CopyPolynom(polynom, size, result);
	for (unsigned int i = 0; i < size; ++i)
	{
		result[i].Coefficient *= monom.Coefficient;
		result[i].Power += monom.Power;
	}

	return result;
}

Monom* MultiplyPolynoms(Monom* polynomA, unsigned int sizeA, Monom* polynomB, unsigned int sizeB,
                        unsigned int* resultSize)
{
	*resultSize = sizeB;
	Monom* result = MultiplyPolynomByMonom(polynomB, sizeB, polynomA[0]);

	for (unsigned int i = 1; i < sizeA; ++i)
	{
		Monom* currentMonomMultiplication = MultiplyPolynomByMonom(polynomB, sizeB, polynomA[i]);
		Monom* resultLastPointer = result;
		result = SumPolynoms(result, *resultSize, currentMonomMultiplication, sizeB, resultSize);
		free(currentMonomMultiplication);
		free(resultLastPointer);
	}

	return result;
}

void PrintMonom(Monom monom, int isFirstMonom)
{
	if (monom.Coefficient < 0)
	{
		printf(" - %d", -1 * monom.Coefficient);
	}
	else
	{
		if (!isFirstMonom)
		{
			printf(" + ");
		}
		if (monom.Coefficient != 1)
		{
			printf("%d", monom.Coefficient);
		}
	}

	if (monom.Power > 0)
	{
		printf("x");
	}
	if (monom.Power > 1)
	{
		printf("^%d", monom.Power);
	}
}

void PrintPolynom(Monom* polynom, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		PrintMonom(polynom[i], i == 0);
	}
}

void PrintPolySum(Monom* polynomA, unsigned int sizeA, Monom* polynomB, unsigned int sizeB)
{
	unsigned int resultSize;
	Monom* result = SumPolynoms(polynomA, sizeA, polynomB, sizeB, &resultSize);
	PrintPolynom(result, resultSize);
	free(result);
}

void PrintPolyMul(Monom* polynomA, unsigned int sizeA, Monom* polynomB, unsigned int sizeB)
{
	unsigned int resultSize;
	Monom* result = MultiplyPolynoms(polynomA, sizeA, polynomB, sizeB, &resultSize);
	PrintPolynom(result, resultSize);
	free(result);
}

int main()
{
	unsigned int polynom1Size, polynom2Size; // The size of each polynom

	printf(" Please enter the first polynom:\n");
	Monom* polynom1 = GetPolynom(&polynom1Size); // get polynom 1

	printf("Please enter the second polynom:\n");
	Monom* polynom2 = GetPolynom(&polynom2Size); // get polynom 2

	printf("The multiplication of the polynoms is:\n"); // print the multiplication
	PrintPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
	printf("\n");

	printf("The sum of the polynoms is:\n"); // print the sum
	PrintPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
	printf("\n");

	free(polynom1); // releasing all memory allocations
	free(polynom2);
}
