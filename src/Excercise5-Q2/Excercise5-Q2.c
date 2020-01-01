#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef int Bool;

typedef struct employee
{
	int NameLength;
	char* Name;
	float Salary;
} Employee;

Bool IsEndOfFile(FILE* file)
{
	int c = fgetc(file);
	ungetc(c, file);

	return c == EOF;
}

Employee* ReadEmployeeFromFile(FILE* file)
{
	Employee* result = malloc(sizeof(Employee));

	fread(&result->NameLength, sizeof(int), 1, file);

	result->Name = malloc(sizeof(char) * (result->NameLength + 1));
	fread(result->Name, sizeof(char), result->NameLength, file);
	result->Name[result->NameLength] = '\0';

	fread(&result->Salary, sizeof(float), 1, file);

	return result;
}

Employee** ParseEmployeesFile(const char* filePath, int* employeesCount)
{
	*employeesCount = 0;
	Employee** result = NULL;
	FILE* employeesFile = fopen(filePath, "rb");

	while (!IsEndOfFile(employeesFile))
	{
		result = *employeesCount == 0
			         ? malloc(sizeof(Employee*))
			         : realloc(result, sizeof(Employee*) * (*employeesCount + 1));

		result[*employeesCount] = ReadEmployeeFromFile(employeesFile);
		(*employeesCount)++;
	}

	fclose(employeesFile);
	return result;
}

float* GetRaises(const char* raisesFilePath, int employeesCount)
{
	float* result = malloc(sizeof(float) * employeesCount);

	FILE* file = fopen(raisesFilePath, "rb");
	fread(result, sizeof(float), employeesCount, file);
	fclose(file);

	return result;
}

void PromoteEmployee(Employee* employee, float raise)
{
	employee->Salary += raise;
}

void SortEmployees(Employee** employees, int employeesCount)
{
	for (int i = 0; i < employeesCount - 1; i++)
	{
		for (int j = 0; j < employeesCount - i - 1; j++)
		{
			if (employees[j]->Salary < employees[j + 1]->Salary)
			{
				Employee* temp = employees[j];
				employees[j] = employees[j + 1];
				employees[j + 1] = temp;
			}
		}
	}
}

void WriteEmployee(Employee* employee, FILE* file)
{
	fwrite(&employee->NameLength, sizeof(int), 1, file);
	fwrite(employee->Name, sizeof(char), employee->NameLength, file);
	fwrite(&employee->Salary, sizeof(float), 1, file);
}

void ReWriteEmployees(const char* filePath, Employee** employees, int employeesCount)
{
	FILE* file = fopen(filePath, "wb");
	for (int i = 0; i < employeesCount; ++i)
	{
		WriteEmployee(employees[i], file);
	}
	fclose(file);
}

void FreeEmployee(Employee* employee)
{
	free(employee->Name);
	free(employee);
}

void FreeEmployees(Employee** employees, int employeesCount)
{
	for (int i = 0; i < employeesCount; ++i)
	{
		FreeEmployee(employees[i]);
	}
}

void Exe5Q2(const char* fname1, const char* fname2)
{
	int employeesCount;

	Employee** employees = ParseEmployeesFile(fname1, &employeesCount);
	float* raises = GetRaises(fname2, employeesCount);

	for (int i = 0; i < employeesCount; ++i)
	{
		PromoteEmployee(employees[i], raises[i]);
	}

	SortEmployees(employees, employeesCount);

	ReWriteEmployees(fname1, employees, employeesCount);

	free(raises);
	FreeEmployees(employees, employeesCount);
}