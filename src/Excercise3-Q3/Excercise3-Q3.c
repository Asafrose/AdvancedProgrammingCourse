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
		for (YListNode* currentYNode = currentXNode->YList.Head; currentYNode != NULL; currentYNode = currentYNode->Next)
		{
			if (currentYNode->Data == y)
			{
				result++;
			}
		}
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

XListNode* GetOrAddXListNode(List* list, int x)
{
	if (IsXCordinateExist(*list, x))
	{
		XListNode* currentNode = list->Head;
		while (currentNode->Data != x)
		{
			currentNode = currentNode->Next;
		}
		return currentNode;
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

int InsertCoordinateInternal(List* list, int x, int y, int isMultipleAdds)
{
	if (!isMultipleAdds && IsCordinateExist(*list, x, y))
	{
		return 1;
	}

	AddYListNode(&GetOrAddXListNode(list, x)->YList, y);
	return 0;
}

int InsertCoordinate(List* list, int x, int y)
{
	return InsertCoordinateInternal(list, x, y, 0);
}

List CreateEmptyList()
{
	List result;
	result.Head = NULL;
	result.Tail = NULL;
	return result;
}

List getCoordList()
{
	List result = CreateEmptyList();
	printf("Enter number of points:\n");
	int numberOfPoints;
	scanf("%d", &numberOfPoints);

	for (int i = 0; i < numberOfPoints; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		InsertCoordinateInternal(&result, x, y, 1);
	}
	return result;
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
	List coordList = getCoordList();

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

	coordList = getCoordList();

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

	coordList = getCoordList();

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

	coordList = getCoordList();

	// get the (x,y) to insert
	scanf("%d%d", &x, &y);

	res = InsertCoordinate(&coordList, x, y);

	if (res == 0)
		printf("The point (%d,%d) didn't appear\n", x, y);
	else
		printf("The point (%d,%d) already appeared\n", x, y);

	FreeList(coordList);
}

void main()
{
	Q4();
}
