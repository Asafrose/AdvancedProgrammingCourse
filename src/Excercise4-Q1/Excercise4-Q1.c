#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode
{
	unsigned int Data;
	struct treeNode* Left;
	struct treeNode* Right;
} TreeNode;

typedef struct tree
{
	TreeNode* Root;
} Tree;

TreeNode* CreateNode(int data)
{
	TreeNode* newNode = malloc(sizeof(TreeNode));
	newNode->Data = data;
	newNode->Left = NULL;
	newNode->Right = NULL;
	return newNode;
}

TreeNode* BuildNodeFromArrayRecursive(int* arr, int size)
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

	TreeNode* newNode = CreateNode(newNodeData);
	newNode->Left = BuildNodeFromArrayRecursive(arr, halfSize);
	newNode->Right = BuildNodeFromArrayRecursive(arr + (halfSize + 1), halfSize);

	return newNode;
}

Tree BuildTreeFromArray(int* arr, int size)
{
	Tree result;
	result.Root = BuildNodeFromArrayRecursive(arr, size);
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

void FreeNodeRecursive(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	FreeNodeRecursive(node->Left);
	FreeNodeRecursive(node->Right);
	free(node);
}

void FreeTree(Tree tree)
{
	FreeNodeRecursive(tree.Root);
}

void main()
{
	int size;
	int arr[100];

	printf("Please enter the number of items: ");
	scanf("%d", &size);
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}

	Tree tree = BuildTreeFromArray(arr, size);
	printf("The tree in inorder (LDR) format:\n");
	PrintTreeInOrder(tree); //Print the tree in-order (LDR)
	FreeTree(tree);
}
