#define _CRT_SECURE_NO_WARNINGS

#define FALSE 0
#define TRUE 1
#define SIZE 100
#define LEFT  0
#define RIGHT 1

#include <stdio.h>
#include <stdlib.h>

typedef int Bool;

typedef struct listNode
{
	int Data;
	struct listNode* Next;
} ListNode;

typedef struct list
{
	ListNode* Head;
	ListNode* Tail;
} List;

typedef struct treeNode
{
	int Data;
	struct treeNode* Parent;
	struct treeNode* Left;
	struct treeNode* Right;
} TreeNode;

typedef struct tree
{
	TreeNode* Root;
	List LeafList;
} Tree;

TreeNode* CreateNode(int data, TreeNode* parent)
{
	TreeNode* newNode = malloc(sizeof(TreeNode));
	newNode->Data = data;
	newNode->Parent = parent;
	newNode->Left = NULL;
	newNode->Right = NULL;
	return newNode;
}

TreeNode* BuildNodeFromArrayRecursive(int* arr, int size, TreeNode* parent)
{
	if (size == 0)
	{
		return NULL;
	}

	int halfSize = size / 2;
	int newNodeData = arr[halfSize];

	if (newNodeData == -1 || size == 0)
	{
		return NULL;
	}

	TreeNode* newNode = CreateNode(newNodeData, parent);
	newNode->Left = BuildNodeFromArrayRecursive(arr, halfSize, newNode);
	newNode->Right = BuildNodeFromArrayRecursive(arr + (halfSize + 1), halfSize, newNode);

	return newNode;
}

Bool IsEmptyList(List list)
{
	return list.Head == NULL && list.Tail == NULL;
}

List JoinLists(List list1, List list2)
{
	if (IsEmptyList(list1))
	{
		return list2;
	}
	if (IsEmptyList(list2))
	{
		return list1;
	}

	list1.Tail->Next = list2.Head;
	list1.Tail = list2.Tail;
	return list1;
}

Bool IsLeaf(TreeNode* node)
{
	return node != NULL && node->Left == NULL && node->Right == NULL;
}

List GetEmptyList()
{
	List result;
	result.Head = NULL;
	result.Tail = NULL;
	return result;
}

ListNode* CreateListNode(int data)
{
	ListNode* result = malloc(sizeof(ListNode));
	result->Next = NULL;
	result->Data = data;
	return result;
}

List GetSingleNodeList(int data)
{
	List result = GetEmptyList();
	ListNode* node = CreateListNode(data);
	result.Head = node;
	result.Tail = node;
	return result;
}

List GetLeafListFromNodeRecursive(TreeNode* node)
{
	if (node == NULL)
	{
		return GetEmptyList();
	}
	if (IsLeaf(node))
	{
		return GetSingleNodeList(node->Data);
	}
	return JoinLists(GetLeafListFromNodeRecursive(node->Left), GetLeafListFromNodeRecursive(node->Right));
}

Tree BuildTreeFromArrayWithLeafList(int* arr, int size)
{
	Tree result;
	result.Root = BuildNodeFromArrayRecursive(arr, size, NULL);
	result.LeafList = GetLeafListFromNodeRecursive(result.Root);
	return result;
}

void PrintNodeInOrderRecursive(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	PrintNodeInOrderRecursive(node->Left);
	printf("%d ", node->Data);
	PrintNodeInOrderRecursive(node->Right);
}

void PrintTreeInOrder(Tree tree)
{
	PrintNodeInOrderRecursive(tree.Root);
}

TreeNode* GetChild(TreeNode* node, int branchSelect)
{
	return node == NULL
		       ? NULL
		       : branchSelect == LEFT
		       ? node->Left
		       : node->Right;
}

TreeNode* FindParentNodeRecursive(TreeNode* node, int parentData, int branchSelect)
{
	if (node == NULL)
	{
		return NULL;
	}

	TreeNode* leftResult = FindParentNodeRecursive(node->Left, parentData, branchSelect);
	if (leftResult != NULL)
	{
		return leftResult;
	}
	if (node->Data == parentData && GetChild(node, branchSelect) == NULL)
	{
		return node;
	}
	return FindParentNodeRecursive(node->Right, parentData, branchSelect);
}

TreeNode* FindParent(Tree tr, int parentData, int branchSelect)
{
	return FindParentNodeRecursive(tr.Root, parentData, branchSelect);
}

void AddChild(TreeNode* node, TreeNode* child, int branchSelect)
{
	if (node == NULL)
	{
		return;
	}
	child->Parent = node;
	if (branchSelect == LEFT)
	{
		node->Left = child;
	}
	else
	{
		node->Right = child;
	}
}

TreeNode* CreateTreeNode(int data)
{
	TreeNode* result = malloc(sizeof(TreeNode));
	result->Data = data;
	result->Left = NULL;
	result->Parent = NULL;
	result->Right = NULL;
	return result;
}

void FreeList(List list)
{
	ListNode* currentNode = list.Head;
	while (currentNode != NULL)
	{
		ListNode* nextNode = currentNode->Next;
		free(currentNode);
		currentNode = nextNode;
	}
}

Tree AddLeaf(Tree tr, TreeNode* treeNode, int branchSelect, int data)
{
	AddChild(treeNode, CreateTreeNode(data), branchSelect);
	FreeList(tr.LeafList);
	tr.LeafList = GetLeafListFromNodeRecursive(tr.Root);
	return tr;
}

void PrintLeafList(Tree tr)
{
	for (ListNode* node = tr.LeafList.Head; node != NULL; node = node->Next)
	{
		printf("%d ", node->Data);
	}
}

void FreeTreeNodeRecursive(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	FreeTreeNodeRecursive(node->Left);
	FreeTreeNodeRecursive(node->Right);
	free(node);
}

void FreeTree(Tree tree)
{
	FreeTreeNodeRecursive(tree.Root);
	FreeList(tree.LeafList);
}

void main()
{
	int size, i;
	int arr[SIZE];

	Tree tr;
	TreeNode* p;

	int parentData, data, branchSelect;
	printf("Please enter the number of items: ");
	scanf("%d", &size);


	for (i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}

	scanf("%d%d%d", &parentData, &data, &branchSelect);
	tr = BuildTreeFromArrayWithLeafList(arr, size); //the array is given as described in question 1

	//scan the tree inorder (LDR) and find the first parent (a node with parentData as data) that has no child in branchSelect
	p = FindParent(tr, parentData, branchSelect);
	tr = AddLeaf(tr, p, branchSelect, data);
	PrintTreeInOrder(tr); //Print the tree in-order (LDR)
	PrintLeafList(tr); //Print the leaves from left to right
	FreeTree(tr);
}
