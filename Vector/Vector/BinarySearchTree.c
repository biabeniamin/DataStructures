#include "BinarySearchTree.h"
#include "Errors.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char **binarySearchTreeInstances;
int binarySearchTreeInstacesCount = 0;
BinaryItem **binarySearchTreeValues;
int getBinarySearcheTreeInstance(char* name)
{
	for (int i = 0; i < binarySearchTreeInstacesCount; i++)
	{
		if (strcmp(binarySearchTreeInstances[i], name) == 0)
		{
			return i;
		}
	}
	return -1;
}
BinaryItem *alocateBinaryItem()
{
	BinaryItem *item = malloc(2 * sizeof(BinaryItem));
	item->left = NULL;
	item->right=NULL;
}
void createBinarySearchTree(char* name)
{
	if (binarySearchTreeInstacesCount == 0)
	{
		binarySearchTreeInstances = (char**)malloc(1 * sizeof(char*));
		binarySearchTreeValues = malloc(5 * sizeof(BinaryItem*));
	}
	else
	{
		int instanceId = getBinarySearcheTreeInstance(name);
		if (instanceId != -1)
		{
			errorDetected(NULL, StructureAlreadyExists);
			return;
		}
		binarySearchTreeInstances = (char**)realloc(binarySearchTreeInstances, (binarySearchTreeInstacesCount + 1) * sizeof(char*));
		binarySearchTreeValues = realloc(binarySearchTreeValues, (binarySearchTreeInstacesCount + 3) * sizeof(BinaryItem*));
	}
	binarySearchTreeValues[binarySearchTreeInstacesCount] = alocateBinaryItem();
	/*binarySearchTreeValues[binarySearchTreeInstacesCount]->left = NULL;
	binarySearchTreeValues[binarySearchTreeInstacesCount]->right = NULL;*/
	binarySearchTreeInstances[binarySearchTreeInstacesCount] = malloc(20);
	strcpy(binarySearchTreeInstances[binarySearchTreeInstacesCount], name);
	binarySearchTreeInstacesCount++;
}

void printBinarySearchTree(char* name)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (binarySearchTreeValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	BinaryItem *current = binarySearchTreeValues[instanceId];
	int lastRow = 1;
	BinaryItem **itemsPerRow = malloc((lastRow + 5) * sizeof(BinaryItem*));
	BinaryItem **nextLine = malloc((2 * lastRow + 5) * sizeof(BinaryItem*));
	itemsPerRow[0] = binarySearchTreeValues[instanceId];
	BinaryItem *nullItem = alocateBalancedBI();
	int depth = getDepthOfNode(current);
	while (lastRow>0)
	{
		int countNextLine = 0;
		int addedValues = 0;
		int whiteSpaces = calculatePow(2, depth) - calculatePow(2, depth - 1);
		for (int i = 0; i < lastRow; i++)
		{
			if (itemsPerRow[i]->left != NULL)
			{
				if (i == 0)
				{
					//WRITESPACES(whiteSpaces);
				}
				else
				{
					//WRITESPACES(whiteSpaces - 1);
				}
				WRITEINT(itemsPerRow[i]->data);
				nextLine[countNextLine++] = itemsPerRow[i]->left;
				nextLine[countNextLine++] = itemsPerRow[i]->right;
				if (itemsPerRow[i]->left->left != NULL)
					addedValues++;
				if (itemsPerRow[i]->right->left != NULL)
					addedValues++;
			}
			else
			{
				//WRITESTRINGSAMELINE("-");
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
			nextLine = malloc((2 * lastRow + 25) * sizeof(BinaryItem*));
		}
		else
			lastRow = 0;
	}
	//WRITELINE();
}
void addBinaryItem(BinaryItem *position, Item *item)
{
	if (position->left == NULL)
	{
		position->left = alocateBinaryItem();
		position->right = alocateBinaryItem();
		position->data = item;
		return;
	}
	if ((int)position->data > (int)item)
	{
		return addBinaryItem(position->left, item);
	}
	else
	{
		return addBinaryItem(position->right, item);
	}
}
BinaryItem *getLastBinaryItem(int instanceId)
{
	BinaryItem *last = binarySearchTreeValues[instanceId];
	while (last->left != NULL)
	{
		last = last->left;
	}
	return last;
}
void addBinarySearchTreeItems(command *com)
{
	int instanceId = getBinarySearcheTreeInstance((char*)com->parameters.values[0]);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	for (int i = 0; i < ((int)com->parameters.values[1]); i++)
	{
		addBinaryItem(binarySearchTreeValues[instanceId], com->parameters.values[i + 2]);
	}
}
void printPreorderSubItems(BinaryItem *item)
{
	if (item->left == NULL)
		return;
	WRITEINT(item->data);
	printPreorderSubItems(item->left);
	printPreorderSubItems(item->right);
}
void preorderBinarySearchTree(char* name)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (binarySearchTreeValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	printPreorderSubItems(binarySearchTreeValues[instanceId]);
	WRITELINE();
}
void printInorderSubItems(BinaryItem *item)
{
	if (item->left == NULL)
		return;
	printInorderSubItems(item->left);
	WRITEINT(item->data);
	printInorderSubItems(item->right);
}
void inorderBinarySearchTree(char* name)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (binarySearchTreeValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	printInorderSubItems(binarySearchTreeValues[instanceId]);
	WRITELINE();
}
void printPostorderSubItems(BinaryItem *item)
{
	if (item->left == NULL)
		return;
	printPostorderSubItems(item->left);
	printPostorderSubItems(item->right);
	WRITEINT(item->data);
}
void postorderBinarySearchTree(char* name)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (binarySearchTreeValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	printPostorderSubItems(binarySearchTreeValues[instanceId]);
	WRITELINE();
}
Item *findValue(BinaryItem *start,Item *value)
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
		return findValue(start->left, value);
	}
	else
	{
		return findValue(start->right, value);
	}
}
Item *searchBinarySearchTreeItem(char* name, Item *item)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	Item *value = findValue(binarySearchTreeValues[instanceId], item);
	if (value == NULL)
	{
		errorDetected(NULL, IndexOutOfBounds);
		return -1;
	}
	return value;
}
BinaryItem *getValuePosition(BinaryItem *start, Item *value)
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
		return getValuePosition(start->left, value);
	}
	else
	{
		return getValuePosition(start->right, value);
	}
}
void deleteItem(BinaryItem *item)
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
Item *deleteBinarySearchTreeItem(char* name, Item *value)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	BinaryItem *position = getValuePosition(binarySearchTreeValues[instanceId], value);
	if (position == NULL)
	{
		errorDetected(NULL, ItemNotFound);
		return NULL;
	}
	else
	{
		deleteItem(position);
	}
}
void mergeBinaryItems(BinaryItem *destination, BinaryItem *source)
{
	if (source->left == NULL)
		return;
	addBinaryItem(destination, source->data);
	mergeBinaryItems(destination, source->left);
	mergeBinaryItems(destination, source->right);
}
void mergeBinarySearchTrees(char *inst1, char *inst2)
{
	int instanceId1 = getBinarySearcheTreeInstance(inst1);
	if (instanceId1 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int instanceId2 = getBinarySearcheTreeInstance(inst2);
	if (instanceId2 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	mergeBinaryItems(binarySearchTreeValues[instanceId1], binarySearchTreeValues[instanceId2]);
	
}
int hightBinarySearchTree(char *name, int node)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (binarySearchTreeValues[instanceId]->left == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return -1;
	}
	BinaryItem *current = binarySearchTreeValues[instanceId];
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
void deleteBinarySearchTreeSubItems(BinaryItem *item)
{
	if (item->left != NULL)
	{
		deleteBinarySearchTreeSubItems(item->left);
		deleteBinarySearchTreeSubItems(item->right);
	}
	free(item);
}
void deleteBinarySearchTree(char* name)
{
	int instanceId = getBinarySearcheTreeInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	deleteBinarySearchTreeSubItems(binarySearchTreeValues[instanceId]);
	for (int i = instanceId; i < binarySearchTreeInstacesCount - 1; i++)
	{
		binarySearchTreeValues[i] = binarySearchTreeValues[i + 1];
		binarySearchTreeInstances[i] = binarySearchTreeInstances[i + 1];
	}
	binarySearchTreeInstacesCount--;
	binarySearchTreeValues = realloc(binarySearchTreeValues, (binarySearchTreeInstacesCount + 3) * sizeof(BinaryItem*));
}