#define _CRT_SECURE_NO_WARNINGS

#define FALSE 0
#define TRUE 1
#define SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Bool;

typedef struct treeNode
{
	char Data;
	struct treeNode* Left;
	struct treeNode* Right;
} TreeNode;

typedef struct tree
{
	TreeNode* Root;
} Tree;

Bool IsOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

Bool IsNumber(char ch)
{
	return ch <= '9' && ch >= '0';
}

Bool IsExpressionValid(char* expression)
{
	int openingBracketsCount = 0;
	int closingBracketsCount = 0;
	for (int i = 0; i < (int)strlen(expression); ++i)
	{
		if (expression[i] == '(')
		{
			openingBracketsCount++;
		}
		else if (expression[i] == ')')
		{
			closingBracketsCount++;
		}
		else if (IsOperator(expression[i]))
		{
			if (i == 0)
			{
				return FALSE;
			}
			if (expression[i + 1] == '\0' ||
				IsOperator(expression[i + 1]) ||
				IsOperator(expression[i - 1]) ||
				expression[i + 1] == ')' ||
				expression[i - 1] == '(')
			{
				return FALSE;
			}
		}
		else if (IsNumber(expression[i]))
		{
			if (IsNumber(expression[i + 1]))
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	return openingBracketsCount == closingBracketsCount;
}

char* TrimSubExpression(char** expression)
{
	char* result = *expression;
	int bracketsBalance = 0;
	do
	{
		if (**expression == '(')
		{
			bracketsBalance++;
		}
		if (**expression == ')')
		{
			bracketsBalance--;
		}
		(*expression)++;
	} while (bracketsBalance != 0);
	return result;
}

char TrimChar(char** expression)
{
	char result = **expression;
	(*expression)++;
	return result;
}

TreeNode* CreateEmptyNode()
{
	TreeNode* result = malloc(sizeof(TreeNode));
	result->Left = NULL;
	result->Right = NULL;
	result->Data = '\0';
	return result;
}

TreeNode* CreateNumberNode(char number)
{
	TreeNode* result = CreateEmptyNode();
	result->Data = number;
	return result;
}

TreeNode* ParseExpressionRecursive(char* expression)
{
	expression++;
	TreeNode* newNode = CreateEmptyNode();
	newNode->Left = IsNumber(*expression)
		                ? CreateNumberNode(TrimChar(&expression))
		                : ParseExpressionRecursive(TrimSubExpression(&expression));
	newNode->Data = TrimChar(&expression);
	newNode->Right = IsNumber(*expression)
		                 ? CreateNumberNode(TrimChar(&expression))
		                 : ParseExpressionRecursive(TrimSubExpression(&expression));
	return newNode;
}

Bool BuildExpressionTree(char* expression, Tree* tr)
{
	if (!IsExpressionValid(expression))
	{
		tr->Root = NULL;
		return FALSE;
	}

	tr->Root = ParseExpressionRecursive(expression);

	return TRUE;
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


double Calculate(double left, char operator, double right)
{
	if (operator == '+')
	{
		return left + right;
	}
	if (operator == '-')
	{
		return left - right;
	}
	if (operator == '*')
	{
		return left * right;
	}
	return left / right;
}

double CharToDouble(char ch)
{
	return (double)(ch - '0');
}

double CalcExpressionRecursive(TreeNode* node)
{
	return Calculate(IsNumber(node->Left->Data)
		                 ? CharToDouble(node->Left->Data)
		                 : CalcExpressionRecursive(node->Left),
	                 node->Data,
	                 IsNumber(node->Right->Data)
		                 ? CharToDouble(node->Right->Data)
		                 : CalcExpressionRecursive(node->Right));
}

double CalcExpression(Tree tr)
{
	return CalcExpressionRecursive(tr.Root);
}

void main()

{
	char str[SIZE];
	Tree tr;

	printf("Please enter the expression: ");
	scanf("%s", str);

	Bool expressionOK = BuildExpressionTree(str, &tr);

	if (expressionOK == TRUE)
	{
		double res = CalcExpression(tr);
		printf("%s = %.2f", str, res);
	}
	else
		printf("The input expression is not valid\n");

	FreeTree(tr);
}
