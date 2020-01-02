#define _CRT_SECURE_NO_WARNINGS
#define FALSE 0
#define TRUE 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef int Bool;

typedef struct student
{
	char* Name;
	int Average;
} Student;

typedef struct binarySearchTreeNode
{
	Student* Student;
	long Offset;
	struct binarySearchTreeNode* Left;
	struct binarySearchTreeNode* Right;
} BinarySearchTreeNode;

typedef struct binarySearchTree
{
	BinarySearchTreeNode* Root;
} BinarySearchTree;

BinarySearchTreeNode* CreateTreeNode(Student* student, long offset)
{
	BinarySearchTreeNode* result = malloc(sizeof(BinarySearchTreeNode));
	result->Student = student;
	result->Offset = offset;
	result->Left = NULL;
	result->Right = NULL;

	return result;
}

void AddTreeNodeRecursive(BinarySearchTreeNode* potentialParent, BinarySearchTreeNode* newNode)
{
	if (potentialParent->Student->Average > newNode->Student->Average)
	{
		if (potentialParent->Left == NULL)
		{
			potentialParent->Left = newNode;
			return;
		}
		AddTreeNodeRecursive(potentialParent->Left, newNode);
	}
	else
	{
		if (potentialParent->Right == NULL)
		{
			potentialParent->Right = newNode;
			return;
		}
		AddTreeNodeRecursive(potentialParent->Right, newNode);
	}
}

void AddStudentToTree(BinarySearchTree* tree, Student* student, long offset)
{
	BinarySearchTreeNode* newNode = CreateTreeNode(student, offset);

	if (tree->Root == NULL)
	{
		tree->Root = newNode;
	}
	else
	{
		AddTreeNodeRecursive(tree->Root, newNode);
	}
}

Student* ReadStudentFromFile(FILE* file)
{
	short int nameSize;
	fread(&nameSize, sizeof(short int), 1, file);

	Student* result = malloc(sizeof(Student));
	result->Name = malloc(sizeof(char) * (nameSize + 1));
	fread(result->Name, sizeof(char), nameSize, file);
	fread(&result->Average, sizeof(int), 1, file);

	return result;
}

BinarySearchTree ParseDatabaseFile(const char* filePath)
{
	BinarySearchTree result;
	result.Root = NULL;

	FILE* file = fopen(filePath, "rb");

	short int entityCount;
	fread(&entityCount, sizeof(short int), 1, file);
	for (int i = 0; i < entityCount; ++i)
	{
		long offset = ftell(file);
		AddStudentToTree(&result, ReadStudentFromFile(file), offset);
	}

	fclose(file);
	return result;
}

void FreeTreeNodeRecurcive(BinarySearchTreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	FreeTreeNodeRecurcive(node->Left);
	FreeTreeNodeRecurcive(node->Right);
	free(node);
}

void WriteStudentOffsetInOrderRecursive(BinarySearchTreeNode* node, FILE* file)
{
	if (node == NULL)
	{
		return;
	}

	WriteStudentOffsetInOrderRecursive(node->Left, file);
	fwrite(&node->Offset, sizeof(long), 1, file);
	WriteStudentOffsetInOrderRecursive(node->Right, file);
}

char* GetOutputFilePath(const char* inputFilePath)
{
	char* result = malloc(sizeof(char) * (strlen(inputFilePath) + 5));
	strcpy(result, inputFilePath);
	strcat(result, ".ind");
	return result;
}

void WriteStudentsOffsetted(BinarySearchTree sortedStudents, const char* outputFilePath)
{
	FILE* file = fopen(outputFilePath, "wb");
	WriteStudentOffsetInOrderRecursive(sortedStudents.Root, file);
	fclose(file);
}

void Exe5Q3(const char* fname)
{
	BinarySearchTree sortedStudents = ParseDatabaseFile(fname);
	char* outputFilePath = GetOutputFilePath(fname);
	WriteStudentsOffsetted(sortedStudents, outputFilePath);
	free(outputFilePath);
	FreeTreeNodeRecurcive(sortedStudents.Root);
}

char** Union(char** arr1, int arr1Size, char** arr2, int arr2Size)
{
	if (arr1 == NULL && arr2 == NULL)
	{
		return NULL;
	}

	char** result = malloc(sizeof(char*) * (arr1Size + arr2Size));
	for (int i = 0; i < arr1Size + arr2Size; ++i)
	{
		if (i < arr1Size)
		{
			result[i] = arr1[i];
		}
		else
		{
			result[i] = arr2[i - arr1Size];
		}
	}

	if (arr1 != NULL)
	{
		free(arr1);
	}

	if (arr2 != NULL)
	{
		free(arr2);
	}

	return result;
}

char** FindAverageGradeRecursive(BinarySearchTreeNode* node, int avgGrade, int* resSize)
{
	if (node == NULL)
	{
		*resSize = 0;
		return NULL;
	}

	int leftSize;
	char** leftResult = FindAverageGradeRecursive(node->Left, avgGrade, &leftSize);
	int rightSize;
	char** rightResult = FindAverageGradeRecursive(node->Right, avgGrade, &rightSize);

	*resSize = leftSize + rightSize;
	char** combinedResult = Union(leftResult, leftSize, rightResult, rightSize);

	if (node->Student->Average == avgGrade)
	{
		(*resSize)++;
		combinedResult = realloc(combinedResult, sizeof(char*) * *resSize);
		combinedResult[*resSize - 1] = node->Student->Name;
	}

	return combinedResult;
}

char** FindAverageGrade(char* database, int avgGrade, int* resSize)
{
	BinarySearchTree sortedStudents = ParseDatabaseFile(database);
	return FindAverageGradeRecursive(sortedStudents.Root, avgGrade, resSize);
}
