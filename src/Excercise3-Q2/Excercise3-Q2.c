#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
	int* DataPtr;
	struct listNode* Next;
} ListNode;

typedef struct list
{
	ListNode* Head;
	ListNode* Tail;
} List;

void GetEmptyList(List* list)
{
	List newList;
	newList.Head = NULL;
	newList.Tail = NULL;
	*list = newList;
}

void InsertDataToEndList(List* listPointer, int data)
{
	int* dataPointer = malloc(sizeof(int));
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

void PrintList(List list)
{
	ListNode* currentNodePointer = list.Head;
	while (currentNodePointer != NULL)
	{
		printf("%d ", *currentNodePointer->DataPtr);
		currentNodePointer = currentNodePointer->Next;
	}
}

List GetList()
{
	List res;
	int size, num, i;

	GetEmptyList(&res);

	printf("Please enter the number of items to be entered:\n");
	scanf("%d", &size);

	printf("Please enter the numbers:\n");
	for (i = 0; i < size; i++)
	{
		scanf("%d", &num);
		InsertDataToEndList(&res, num);
	}

	return res;
}

void FreeList(List* listPointer)
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

int GetValueAndAdvanceNode(ListNode** node)
{
	int result = *((*node)->DataPtr);
	*node = (*node)->Next;
	return result;
}

int GetLowerValueAndAdvanceLowerNode(ListNode** node1, ListNode** node2)
{
	if (*node2 == NULL || (*node1 != NULL && *((*node1)->DataPtr) < *((*node2)->DataPtr)))
	{
		return GetValueAndAdvanceNode(node1);
	}
	return GetValueAndAdvanceNode(node2);
}

List MergeQ1(List list1, List list2)
{
	List result;
	GetEmptyList(&result);

	ListNode** node1 = &list1.Head;
	ListNode** node2 = &list2.Head;

	while (*node1 != NULL || *node2 != NULL)
	{
		InsertDataToEndList(&result, GetLowerValueAndAdvanceLowerNode(node1, node2));
	}

	return result;
}

void Q1()
{
	List lst1, lst2, mergedList;

	lst1 = GetList();
	lst2 = GetList();

	mergedList = MergeQ1(lst1, lst2);

	printf("Merged list:\n");
	PrintList(mergedList);

	FreeList(&lst1);
	FreeList(&lst2);
	FreeList(&mergedList);
}

void main()
{
	Q1();
}
