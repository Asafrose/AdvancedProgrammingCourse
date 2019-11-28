#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode
{
	char* DataPtr;
	struct listNode* Next;
}ListNode;

typedef struct list
{
	ListNode* Head;
	ListNode* Tail;
}List;

typedef struct  student
{
	List First;
	int Grade;
} Student;

int IsNumber(char ch)
{
	return ch >= '0' && ch <= '9';
}

void freeNode(ListNode* node)
{
	free(node->DataPtr);
	free(node);
}

int CharToInt(char ch)
{
	return (int)(ch - '0');
}

int GetGrade(List list)
{
	int grade = 0;
	ListNode* currentNode = list.Head;
	while (currentNode != NULL)
	{
		if (IsNumber(*currentNode->DataPtr))
		{
			grade = 10 * grade + CharToInt(*currentNode->DataPtr);
		}
		currentNode = currentNode->Next;
	}

	return grade;
}

void TrimGrade(List* list)
{
	ListNode* currentNode = list->Head;
	while (currentNode != NULL && IsNumber(*currentNode->DataPtr))
	{
		ListNode* nextNode = currentNode->Next;
		freeNode(currentNode);
		currentNode = nextNode;
	}

	list->Head = currentNode;
	ListNode* latestCharacterNode = currentNode;
	while (currentNode != NULL)
	{
		ListNode* nextNode = currentNode->Next;
		if (IsNumber(*currentNode->DataPtr))
		{
			freeNode(currentNode);
			latestCharacterNode->Next = nextNode;
		}
		else
		{
			latestCharacterNode = currentNode;
		}
		currentNode = nextNode;
	}
}

Student unScramble(List list)
{
	int grade = GetGrade(list);
	TrimGrade(&list);

	Student result;
	result.Grade = grade;
	result.First = list;
	return result;
}

void makeEmptyList(List* listPointer)
{
	List list;
	list.Head = NULL;
	list.Tail = NULL;

	*listPointer = list;
}

void insertDataToEndList(List* listPointer, char data)
{
	char* dataPointer = malloc(sizeof(char));
	*dataPointer = data;
	ListNode* newNodePointer = malloc(sizeof(ListNode));
	newNodePointer->DataPtr = dataPointer;
	newNodePointer->Next = NULL;

	if (listPointer->Head == NULL)
	{
		listPointer->Head = newNodePointer;
		listPointer->Tail = newNodePointer;
	}
	else
	{
		listPointer->Tail->Next = newNodePointer;
		listPointer->Tail = newNodePointer;
	}
}

void printList(List list)
{
	ListNode* currentNodePointer = list.Head;
	while (currentNodePointer != NULL)
	{
		printf("%c", *currentNodePointer->DataPtr);
		currentNodePointer = currentNodePointer->Next;
	}
}

void printStudent(Student* studentPointer)
{
	printf("First name: ");
	printList(studentPointer->First);
	printf("\n");

	printf("Grade: %d\n", studentPointer->Grade);
}

void freeList(List* listPointer)
{
	ListNode* currentNodePointer = listPointer->Head;
	while (currentNodePointer != NULL)
	{
		ListNode* nextNodePointer = currentNodePointer->Next;
		free(currentNodePointer->DataPtr);
		free(currentNodePointer);
		currentNodePointer = nextNodePointer;
	}
}

void main()
{
	List lst;
	Student student;

	makeEmptyList(&lst);

	printf("Please enter the scrambled student:\n");

	char ch = (char)getchar();
	while (ch != '\n')
	{
		insertDataToEndList(&lst, ch);
		ch = (char)getchar();
	}

	student = unScramble(lst);

	printStudent(&student);

	freeList(&student.First);
}
