#include "BalancedBST.h"
#include "Errors.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char **balancedBSTInstances;
int balancedBSTInstacesCount = 0;
BinaryItem **balancedBSTValues;
int getBalancedBSTInstance(char* name)
{
	for (int i = 0; i < balancedBSTInstacesCount; i++)
	{
		if (strcmp(balancedBSTInstances[i], name) == 0)
		{
			return i;
		}
	}
	return -1;
}
BinaryItem *alocateBalancedBI()
{
	BinaryItem *item = malloc(2 * sizeof(BinaryItem));
	item->left = NULL;
	item->right = NULL;
}
void createBalancedBST(char* name)
{
	if (balancedBSTInstacesCount == 0)
	{
		balancedBSTInstances = (char**)malloc(1 * sizeof(char*));
		balancedBSTValues = malloc(5 * sizeof(BinaryItem*));
	}
	else
	{
		int instanceId = getBalancedBSTInstance(name);
		if (instanceId != -1)
		{
			errorDetected(NULL, StructureAlreadyExists);
			return;
		}
		balancedBSTInstances = (char**)realloc(balancedBSTInstances, (balancedBSTInstacesCount + 1) * sizeof(char*));
		balancedBSTValues = realloc(balancedBSTValues, (balancedBSTInstacesCount + 3) * sizeof(BinaryItem*));
	}
	balancedBSTValues[balancedBSTInstacesCount] = alocateBalancedBI();
	/*balancedBSTValues[balancedBSTInstacesCount]->left = NULL;
	balancedBSTValues[balancedBSTInstacesCount]->right = NULL;*/
	balancedBSTInstances[balancedBSTInstacesCount] = malloc(20);
	strcpy(balancedBSTInstances[balancedBSTInstacesCount], name);
	balancedBSTInstacesCount++;
}
int calculatePow(int number, int power)
{
	if (power == 0)
		return 1;
	return number*calculatePow(number, power - 1);
}
void printBalancedBST(char* name)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (balancedBSTValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	BinaryItem *current = balancedBSTValues[instanceId];
	int lastRow = 1;
	BinaryItem **itemsPerRow = malloc((lastRow + 5) * sizeof(BinaryItem*));
	BinaryItem **nextLine = malloc((2 * lastRow + 5) * sizeof(BinaryItem*));
	itemsPerRow[0] = balancedBSTValues[instanceId];
	BinaryItem *nullItem = alocateBalancedBI();
	int depth = getDepthOfNode(current);
	while (lastRow>0)
	{
		int countNextLine = 0;
		int addedValues= 0;
		int whiteSpaces = calculatePow(2, depth)- calculatePow(2, depth-1);
		for (int i = 0; i < lastRow; i++)
		{
			if (itemsPerRow[i]->left != NULL)
			{
				if (i ==0)
				{
					WRITESPACES(whiteSpaces);
				}
				else
				{
					WRITESPACES(whiteSpaces -1);
				}
				WRITEINT(itemsPerRow[i]->data);
				nextLine[countNextLine++] = itemsPerRow[i]->left;
				nextLine[countNextLine++] = itemsPerRow[i]->right;
				if (itemsPerRow[i]->left ->left!= NULL)
					addedValues++;
				if (itemsPerRow[i]->right->left!= NULL)
					addedValues++;
			}
			else
			{
				WRITESTRINGSAMELINE(" ");
				nextLine[countNextLine++] = nullItem;
				nextLine[countNextLine++] = nullItem;
			}
		}
		free(itemsPerRow);
		depth--;
		itemsPerRow = nextLine;
		WRITELINE();
		if (addedValues>0)
		{
			lastRow = countNextLine;
			nextLine = malloc((2*lastRow + 25) * sizeof(BinaryItem*));
		}
		else
			lastRow = 0;
	}
	//WRITELINE();
}
void addBBI(BinaryItem *position, Item *item)
{
	BinaryItem *asd = balancedBSTValues[0];
	if (position->left == NULL)
	{
		position->left = alocateBalancedBI();
		position->right = alocateBalancedBI();
		position->data = item;
		return;
	}
	if ((int)position->data > (int)item)
	{
		return addBBI(position->left, item);
	}
	else
	{
		return addBBI(position->right, item);
	}
}
void mergeBBI(BinaryItem *destination, BinaryItem *source)
{
	if (source->left == NULL)
		return;
	addBBI(destination, source->data);
	mergeBBI(destination, source->left);
	mergeBBI(destination, source->right);
}
void deleteBalancedBSTSubItems(BinaryItem *item)
{
	if (item->left != NULL)
	{
		deleteBalancedBSTSubItems(item->left);
		deleteBalancedBSTSubItems(item->right);
	}
	free(item);
}
int getDepthOfNode(BinaryItem *item)
{
	if (item == NULL)
		return 0;
	if (item->left == NULL)
		return 0;
	int leftDepth = getDepthOfNode(item->left) + 1;
	int rightDepth = getDepthOfNode(item->right) + 1;
	if (leftDepth > rightDepth)
		return leftDepth;
	return rightDepth;
}
/*void balancedNode(BinaryItem *last, BinaryItem *current)
{
	if (last == NULL || current == NULL)
		return;
	if (current->left == NULL)
		return;
	BinaryItem *nextRight = current->right;
	BinaryItem *nextLeft= current->left;
	if (nextLeft->left != NULL)
	{
		if (last->right->left == NULL && current->right->left == NULL && nextRight->right->left == NULL)
		{
			BinaryItem *leftItem = alocateBalancedBI();
			leftItem->data = last->data;
			leftItem->left = alocateBalancedBI();
			leftItem->right = last->left;
			last->data = current->data;
			last->right = current->right;
			last->left = current->left;
			mergeBBI(last, leftItem);
			deleteBalancedBSTSubItems(leftItem);


		}
	}
	if (nextRight->left != NULL)
	{
		if (last->left->left == NULL && current->left->left == NULL && nextRight->left->left == NULL)
		{
			BinaryItem *rightItem = alocateBalancedBI();
			rightItem->data = last->data;
			rightItem->left = last->left;
			rightItem->right = alocateBalancedBI();
			last->data = current->data;
			last->left = current->left;
			last->right= current->right;
			mergeBBI(last, rightItem);
			deleteBalancedBSTSubItems(rightItem);


		}
	}
	balancedNode(current, current->left);
	balancedNode(current, current->right);
	//while(())
}*/
void balancedNode(BinaryItem *node)
{
	if (node == NULL)
		return;
	if (node->left == NULL)
		return;
	int depthLeft = getDepthOfNode(node->left);
	int depthRight = getDepthOfNode(node->right);
	while (depthLeft < depthRight - 1)
	{
		BinaryItem *leftValues = node->left;
		Item topValue = node->data;
		node->data = node->right->data;
		node->left = node->right->left;
		node->right = node->right->right;
		mergeBBI(node, leftValues);
		addBBI(node, topValue);
		depthLeft = getDepthOfNode(node->left);
		depthRight = getDepthOfNode(node->right);
	}
	while (depthLeft-1 > depthRight)
	{
		BinaryItem *asd = balancedBSTValues[0];
		BinaryItem *rightValues = node->right;
		Item topValue = node->data;
		node->data = node->left->data;
		node->right = node->left->right;
		node->left = node->left->left;
		mergeBBI(node, rightValues);
		addBBI(node, topValue);
		depthLeft = getDepthOfNode(node->left);
		depthRight = getDepthOfNode(node->right);
	}
	balancedNode(node->left);
	balancedNode(node->right);
}
void balanceBST(int instanceId)
{
	balancedNode(balancedBSTValues[instanceId]);
}
BinaryItem *getLastBBI(int instanceId)
{
	BinaryItem *last = balancedBSTValues[instanceId];
	while (last->left != NULL)
	{
		last = last->left;
	}
	return last;
}
void addBalancedBSTItems(command *com)
{
	int instanceId = getBalancedBSTInstance((char*)com->parameters.values[0]);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	for (int i = 0; i < ((int)com->parameters.values[1]); i++)
	{
		addBBI(balancedBSTValues[instanceId], com->parameters.values[i + 2]);
	}
	balanceBST(instanceId);
}
void printPreorderSubBItems(BinaryItem *item)
{
	if (item->left == NULL)
		return;
	WRITEINT(item->data);
	printPreorderSubBItems(item->left);
	printPreorderSubBItems(item->right);
}
void preorderBalancedBST(char* name)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (balancedBSTValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	printPreorderSubBItems(balancedBSTValues[instanceId]);
	WRITELINE();
}
void printInorderSubBItems(BinaryItem *item)
{
	if (item->left == NULL)
		return;
	printInorderSubBItems(item->left);
	WRITEINT(item->data);
	printInorderSubBItems(item->right);
}
void inorderBalancedBST(char* name)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (balancedBSTValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	printInorderSubBItems(balancedBSTValues[instanceId]);
	WRITELINE();
}
void printPostorderSubBItems(BinaryItem *item)
{
	if (item->left == NULL)
		return;
	printPostorderSubBItems(item->left);
	printPostorderSubBItems(item->right);
	WRITEINT(item->data);
}
void postorderBalancedBST(char* name)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (balancedBSTValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	printPostorderSubBItems(balancedBSTValues[instanceId]);
	WRITELINE();
}
Item *findBValue(BinaryItem *start, Item *value)
{
	if (start->left == NULL)
	{
		return NULL;
	}
	if ((int)start->data == (int)value)
	{
		return value;
	}
	if ((int)start->data > (int)value)
	{
		return findBValue(start->left, value);
	}
	else
	{
		return findBValue(start->right, value);
	}
}
Item *searchBalancedBSTItem(char* name, Item *item)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	Item *value = findBValue(balancedBSTValues[instanceId], item);
	if (value == NULL)
	{
		errorDetected(NULL, IndexOutOfBounds);
		return -1;
	}
	return value;
}
BinaryItem *getBValuePosition(BinaryItem *start, Item *value)
{
	if (start->left == NULL)
	{
		return NULL;
	}
	if ((int)start->data == (int)value)
	{
		return start;
	}
	if ((int)start->data > (int)value)
	{
		return getBValuePosition(start->left, value);
	}
	else
	{
		return getBValuePosition(start->right, value);
	}
}
Item getMinItem(BinaryItem *item)
{
	if (item->left->left == NULL)
		return item;
	return getMinItem(item->left);
}
Item getMaxItem(BinaryItem *item)
{
	if (item->right->left == NULL)
		return item;
	return getMaxItem(item->right);
}
void deleteBItem(BinaryItem *item)
{

	if (item->right->left != NULL)
	{
		//item->data = item->right->data;
		BinaryItem *min = getMinItem(item->right);
		item->data = min->data;
		return deleteBItem(min);
	}
	else if (item->left->left != NULL)
	{
		BinaryItem *max = getMinItem(item->left);
		item->data = max->data;
		return deleteBItem(max);
	}
	else
	{
		free(item->left);
		free(item->right);
		item->left = NULL;

	}
}
Item *deleteBalancedBSTItem(char* name, Item *value)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	BinaryItem *position = getBValuePosition(balancedBSTValues[instanceId], value);
	if (position == NULL)
	{
		errorDetected(NULL, ItemNotFound);
		return NULL;
	}
	else
	{
		deleteBItem(position);
	}
	balanceBST(instanceId);
}
void mergeBalancedBSTs(char *inst1, char *inst2)
{
	int instanceId1 = getBalancedBSTInstance(inst1);
	if (instanceId1 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int instanceId2 = getBalancedBSTInstance(inst2);
	if (instanceId2 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	mergeBBI(balancedBSTValues[instanceId1], balancedBSTValues[instanceId2]);

}
int hightBalancedBST(char *name, int node)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (balancedBSTValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return -1;
	}
	BinaryItem *current = balancedBSTValues[instanceId];
	int lastRow = 1;
	BinaryItem **itemsPerRow = malloc((lastRow + 5) * sizeof(BinaryItem*));
	BinaryItem **nextLine = malloc((2 * lastRow + 5) * sizeof(BinaryItem*));
	itemsPerRow[0] = current;
	int count = 0;
	int depth = 0;
	if (node <= count)
	{
		return depth;
	}
	depth++;
	while (lastRow>0)
	{
		int countNextLine = 0;
		for (int i = 0; i < lastRow; i++)
		{
			if (itemsPerRow[i]->left != NULL)
			{
				nextLine[countNextLine++] = itemsPerRow[i]->left;
				count++;
			}
			if (itemsPerRow[i]->right != NULL)
			{
				nextLine[countNextLine++] = itemsPerRow[i]->right;
				count++;
			}
			if (node <= count)
			{
				return depth;
			}
		}
		depth++;
		free(itemsPerRow);
		itemsPerRow = nextLine;
		lastRow = countNextLine;
		nextLine = malloc((countNextLine + 5) * sizeof(BinaryItem*));
	}
	return -1;
}
void deleteBalancedBST(char* name)
{
	int instanceId = getBalancedBSTInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	deleteBalancedBSTSubItems(balancedBSTValues[instanceId]);
	for (int i = instanceId; i < balancedBSTInstacesCount - 1; i++)
	{
		balancedBSTValues[i] = balancedBSTValues[i + 1];
		balancedBSTInstances[i] = balancedBSTInstances[i + 1];
	}
	balancedBSTInstacesCount--;
	balancedBSTValues = realloc(balancedBSTValues, (balancedBSTInstacesCount + 3) * sizeof(BinaryItem*));
}