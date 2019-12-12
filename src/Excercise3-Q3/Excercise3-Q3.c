#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct yListNode
{
	int Data;
	struct yListNode* Next;
} YListNode;

typedef struct yList
{
	YListNode* Head;
	YListNode* Tail;
} YList;

typedef struct xListNode
{
	struct xListNode* Before;
	int Data;
	YList YList;
	struct xListNode* Next;
} XListNode;

typedef struct list
{
	XListNode* Head;
	XListNode* Tail;
} List;

unsigned int GetYOccurrencesInternal(YList yList, int y)
{
	unsigned int result = 0;
	YListNode* currentNode = yList.Head;
	while (currentNode != NULL)
	{
		if (currentNode->Data == y)
		{
			result++;
		}
		currentNode = currentNode->Next;
	}

	return result;
}

unsigned int GetPairOccurrences(List list, int x, int y)
{
	XListNode* currentNode = list.Head;
	while (currentNode != NULL)
	{
		if (currentNode->Data == x)
		{
			return GetYOccurrencesInternal(currentNode->YList, y);
		}
		currentNode = currentNode->Next;
	}

	return 0;
}

unsigned int CountNodes(YList list)
{
	unsigned int result = 0;
	YListNode* currentNode = list.Head;
	while (currentNode != NULL)
	{
		result++;
		currentNode = currentNode->Next;
	}

	return result;
}

unsigned int GetXOccurrences(List list, int x)
{
	XListNode* currentNode = list.Head;
	while (currentNode != NULL)
	{
		if (currentNode->Data == x)
		{
			return CountNodes(currentNode->YList);
		}
		currentNode = currentNode->Next;
	}

	return 0;
}

unsigned int GetYOccurrences(List list, int y)
{
	unsigned int result = 0;
	for (XListNode* currentXNode = list.Head; currentXNode != NULL; currentXNode = currentXNode->Next)
	{
		result += GetYOccurrencesInternal(currentXNode->YList, y);
	}
	return result;
}

int IsXCordinateExist(List list, int x)
{
	return GetXOccurrences(list, x) != 0;
}

int IsCordinateExist(List list, int x, int y)
{
	return GetPairOccurrences(list, x, y) != 0;
}

YList CreateEmptyYList()
{
	YList result;
	result.Head = NULL;
	result.Tail = NULL;
	return result;
}

XListNode* CreateNewXNode(int value)
{
	XListNode* newNode = malloc(sizeof(XListNode));
	newNode->Data = value;
	newNode->YList = CreateEmptyYList();
	newNode->Next = NULL;
	newNode->Before = NULL;

	return newNode;
}

void InsertXNode(XListNode* node, XListNode* nodeToInsert)
{
	if (node->Next != NULL)
	{
		node->Next->Before = nodeToInsert;
	}
	nodeToInsert->Next = node->Next;
	node->Next = nodeToInsert;
	nodeToInsert->Before = node;
}

void InsertXNodeToHead(List* list, XListNode* node)
{
	list->Head->Before = node;
	node->Next = list->Head;
	list->Head = node;
}

void InsertXNoteToTail(List* list, XListNode* node)
{
	list->Tail->Next = node;
	node->Before = list->Tail;
	list->Tail = node;
}

XListNode* AddXListNode(List* list, int x)
{
	XListNode* newNode = CreateNewXNode(x);


	if (list->Head == NULL)
	{
		list->Head = newNode;
		list->Tail = newNode;
		return newNode;
	}
	if (x < list->Head->Data)
	{
		InsertXNodeToHead(list, newNode);
		return newNode;
	}
	if (x > list->Tail->Data)
	{
		InsertXNoteToTail(list, newNode);
		return newNode;
	}

	XListNode* currentNode = list->Head;
	while (x > currentNode->Next->Data)
	{
		currentNode = currentNode->Next;
	}
	InsertXNode(currentNode, newNode);

	return newNode;
}

XListNode* GetXListNode(List* list, int x)
{
	XListNode* currentNode = list->Head;
	while (currentNode != NULL && currentNode->Data != x)
	{
		currentNode = currentNode->Next;
	}
	return currentNode;
}

XListNode* GetOrAddXListNode(List* list, int x)
{
	if (IsXCordinateExist(*list, x))
	{
		return GetXListNode(list, x);
	}

	return AddXListNode(list, x);
}

YListNode* CreateNewYListNode(int value)
{
	YListNode* newNode = malloc(sizeof(YListNode));
	newNode->Data = value;
	newNode->Next = NULL;

	return newNode;
}

void InsertYNode(YListNode* node, YListNode* nodeToInsert)
{
	nodeToInsert->Next = node->Next;
	node->Next = nodeToInsert;
}

void InsertYNodeToHead(YList* list, YListNode* node)
{
	node->Next = list->Head;
	list->Head = node;
}

void InsertYNodeToTail(YList* list, YListNode* node)
{
	list->Tail->Next = node;
	list->Tail = node;
}

void AddYListNode(YList* list, int y)
{
	YListNode* newNode = CreateNewYListNode(y);

	if (list->Head == NULL)
	{
		list->Head = newNode;
		list->Tail = newNode;
		return;
	}
	if (y < list->Head->Data)
	{
		InsertYNodeToHead(list, newNode);
		return;
	}
	if (y >= list->Tail->Data)
	{
		InsertYNodeToTail(list, newNode);
		return;
	}

	YListNode* currentNode = list->Head;
	while (y > currentNode->Next->Data)
	{
		currentNode = currentNode->Next;
	}
	InsertYNode(currentNode, newNode);
}

int InsertCoordinate(List* list, int x, int y)
{
	AddYListNode(&GetOrAddXListNode(list, x)->YList, y);
	return GetPairOccurrences(*list, x, y) == 1
		? 0
		: 1;
}

YListNode* GetYNode(YList list, int y)
{
	for (YListNode* currentNode = list.Head; currentNode != NULL; currentNode = currentNode->Next)
	{
		if (currentNode->Data == y)
		{
			return currentNode;
		}
	}
	return NULL;
}

YListNode* GetNodeBefore(YList list, YListNode* node)
{
	if (list.Head == node)
	{
		return NULL;
	}

	for (YListNode* currentNode = list.Head; currentNode != NULL; currentNode = currentNode->Next)
	{
		if (currentNode->Next == node)
		{
			return currentNode;
		}
	}

	return NULL;
}

void RemoveYNodeInternal(YList* list, YListNode* node)
{
	YListNode* beforeNode = GetNodeBefore(*list, node);

	if (list->Head == node)
	{
		list->Head = node->Next;
	}
	if (list->Tail == node)
	{
		list->Tail = beforeNode;
	}
	if (beforeNode != NULL)
	{
		beforeNode->Next = node->Next;
	}
	
	free(node);
}

int RemoveYNode(YList* list, int y)
{
	if (GetYOccurrencesInternal(*list, y) == 0)
	{
		return 1;
	}

	RemoveYNodeInternal(list, GetYNode(*list, y));

	return GetYOccurrencesInternal(*list, y) == 0
		       ? 0
		       : 2;
}

void FreeYList(YList list)
{
	YListNode* currentNode = list.Head;
	while (currentNode != NULL)
	{
		YListNode* nextNode = currentNode->Next;
		free(currentNode);
		currentNode = nextNode;
	}
}

void FreeXNode(XListNode* node)
{
	FreeYList(node->YList);
	free(node);
}

void RemoveXNode(List* list, XListNode* node)
{
	if (list->Head == node)
	{
		list->Head = node->Next;
	}
	if (list->Tail == node)
	{
		list->Tail = node->Before;
	}

	if (node->Next != NULL)
	{
		node->Next->Before = node->Before;
	}
	if (node->Before != NULL)
	{
		node->Before->Next = node->Next;
	}

	FreeXNode(node);
}

int RemoveCoordinate(List* list, int x, int y)
{
	XListNode* xNode = GetXListNode(list, x);

	int result = RemoveYNode(&xNode->YList, y);

	if (CountNodes(xNode->YList) == 0)
	{
		RemoveXNode(list, xNode);
		return 3;
	}

	return result;
}

List CreateEmptyList()
{
	List result;
	result.Head = NULL;
	result.Tail = NULL;
	return result;
}

List GetCoordList()
{
	List result = CreateEmptyList();
	printf("Enter number of points:\n");
	int numberOfPoints;
	scanf("%d", &numberOfPoints);

	for (int i = 0; i < numberOfPoints; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		InsertCoordinate(&result, x, y);
	}
	return result;
}


void FreeList(List list)
{
	XListNode* currentNode = list.Head;
	while (currentNode != NULL)
	{
		XListNode* nextNode = currentNode->Next;
		FreeXNode(currentNode);
		currentNode = nextNode;
	}
}

void Q1()
{
	int x, y;

	// The user will enter the number of points followed by the points.
	// The pointes will be entered in a sorted fashion.
	// i.e. first by the x value and then by y.
	// for example (5 points): 5 1 2 1 5 2 7 3 3 3 8
	// are: (1,2),(1,5),(2,7),(3,3),(3,8)
	List coordList = GetCoordList();

	// get the (x,y) to look for
	scanf("%d%d", &x, &y);

	unsigned int res = GetPairOccurrences(coordList, x, y);

	printf("The point (%d,%d) appears %u times\n", x, y, res);

	FreeList(coordList);
}

void Q2()
{
	List coordList;
	int y;
	unsigned int res;

	coordList = GetCoordList();

	// get the (*,y) to look for
	scanf("%d", &y);

	res = GetYOccurrences(coordList, y);

	printf("The point (*,%d) appears %u times\n", y, res);

	FreeList(coordList);
}

void Q3()
{
	List coordList;
	int x;
	unsigned int res;

	coordList = GetCoordList();

	// get the (x,*) to look for
	scanf("%d", &x);

	res = GetXOccurrences(coordList, x);

	printf("The point (%d,*) appears %u times\n", x, res);

	FreeList(coordList);
}

void Q4()
{
	List coordList;

	int x, y;
	int res;

	coordList = GetCoordList();

	// get the (x,y) to insert
	scanf("%d%d", &x, &y);

	res = InsertCoordinate(&coordList, x, y);

	if (res == 0)
		printf("The point (%d,%d) didn't appear\n", x, y);
	else
		printf("The point (%d,%d) already appeared\n", x, y);

	FreeList(coordList);
}

void Q5()
{
	List coordList;

	int x, y;
	int res;

	coordList = GetCoordList();

	// get the (x,y) to remove
	scanf("%d%d", &x, &y);

	res = RemoveCoordinate(&coordList, x, y);

	if (res == 1)
		printf("The point (%d,%d) didn't appear\n", x, y);
	else if (res == 2)
		printf("The point (%d,%d) has another occurrence\n", x, y);
	else if (res == 3)
		printf("The point (%d,%d) was the only point with this x\n", x, y);
	else
		printf("Other\n");

	FreeList(coordList);
}

void main()
{
	Q5();
}
