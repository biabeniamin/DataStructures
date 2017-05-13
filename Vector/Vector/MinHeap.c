#include "MinHeap.h"
#include "Errors.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char **heapInstances;
int heapInstacesCount = 0;
int* heapValuesCount;
Item **heapValues;
int getHeapIndexInstance(char* name)
{
	for (int i = 0; i < heapInstacesCount; i++)
	{
		if (strcmp(heapInstances[i], name) == 0)
		{
			return i;
		}
	}
	return -1;
}
void createHeap(char* name)
{
	if (heapInstacesCount == 0)
	{
		heapInstances = (char**)malloc(1 * sizeof(char*));
		heapValues = malloc(5 * sizeof(LinkedItem*));
		heapValuesCount= malloc(5 * sizeof(int));
	}
	else
	{
		int instanceId = getHeapIndexInstance(name);
		if (instanceId != -1)
		{
			errorDetected(NULL, StructureAlreadyExists);
			return;
		}
		heapInstances = (char**)realloc(heapInstances, (heapInstacesCount + 1) * sizeof(char*));
		heapValues = realloc(heapValues, (heapInstacesCount + 3) * sizeof(Item*));
	}
	heapValues[heapInstacesCount] = malloc(5 * sizeof(Item));
	heapInstances[heapInstacesCount] = malloc(20);
	heapValuesCount = realloc(heapValuesCount, (heapInstacesCount + 3) * sizeof(int));
	heapValuesCount[heapInstacesCount] = 0;
	strcpy(heapInstances[heapInstacesCount], name);
	heapInstacesCount++;
}
int getLeftChildIndex(int index)
{
	return index * 2 + 1;
}
int getRightChildIndex(int index)
{
	return index * 2 + 2;
}
void printHeapChilds(int instanceId, int index)
{
	//printHeapChilds(instanceId, getRightChildIndex)
}
int pow(int number, int power)
{
	if (power == 0)
		return 1;
	return number*pow(number, power - 1);
}
void printHeap(char* name)
{
	int instanceId = getHeapIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (heapValuesCount[instanceId] == 0)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	int nextLine = 0;
	int elementsPerLine = 1;
	int endedInNewLine = 0;
	for (int i = 0; i < heapValuesCount[instanceId]; i++)
	{
		endedInNewLine = 0;
		WRITEINT(heapValues[instanceId][i]);
		if (nextLine == i)
		{
			WRITELINE();
			endedInNewLine = 1;
			elementsPerLine *= 2;
			nextLine =nextLine+ elementsPerLine;
		}
	}
	if (endedInNewLine == 0)
		WRITELINE();
	//WRITESTRING("--------------------------");
}
int calculateParentIndex(int position)
{
	int parentPosition = (position - 2) / 2;
	if (position % 2 != 0)
		parentPosition = (position - 1) / 2;
	return parentPosition;
}
void addHeapValue(int instanceId, Item value)
{
	int position = heapValuesCount[instanceId]++;
	heapValues[instanceId][position] = value;
	int parentPosition = calculateParentIndex(position);
	while (parentPosition>=0)
	{
		if (heapValues[instanceId][parentPosition] > heapValues[instanceId][position])
		{
			Item aux = heapValues[instanceId][parentPosition];
			heapValues[instanceId][parentPosition] = heapValues[instanceId][position];
			heapValues[instanceId][position] = aux;
		}
		else
		{
			break;
		}
		position = parentPosition;
		parentPosition = calculateParentIndex(position);
	}
}
void addHeapItems(command *com)
{
	int instanceId = getHeapIndexInstance((char*)com->parameters.values[0]);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	heapValues[instanceId] = realloc(heapValues[instanceId],(heapValuesCount[instanceId]+ (int)com->parameters.values[1]+5) * sizeof(Item));
	for (int i = 0; i <((int)com->parameters.values[1]); i++)
	{
		Item value= com->parameters.values[i + 2];
		addHeapValue(instanceId, value);

	}
}
Item getHeapMin(char* name)
{
	int instanceId = getHeapIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (heapValuesCount[instanceId] == 0)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	return heapValues[instanceId][0];
}
void deleteHeapItemAtIndex(int instanceId, int position)
{
	int rightChild = getRightChildIndex(position);
	int leftChild = getLeftChildIndex(position);
	if ((rightChild) > heapValuesCount[instanceId])
	{
		if ((leftChild)< heapValuesCount[instanceId])
		{
			heapValues[instanceId][rightChild] = heapValues[instanceId][heapValuesCount[instanceId]-1];
			heapValuesCount[instanceId]--;
			return;
		}
		else
		{
			for (int i = position; i < heapValuesCount[instanceId]-1; i++)
			{
				heapValues[instanceId][i] = heapValues[instanceId][i + 1];
			}
			heapValuesCount[instanceId]--;
			return;
		}
	}
	if (heapValues[instanceId][rightChild] < heapValues[instanceId][leftChild])
	{
		heapValues[instanceId][position] = heapValues[instanceId][rightChild];
		deleteHeapItemAtIndex(instanceId, rightChild);
	}
	if (heapValues[instanceId][rightChild] > heapValues[instanceId][leftChild])
	{
		heapValues[instanceId][position] = heapValues[instanceId][leftChild];
		deleteHeapItemAtIndex(instanceId, leftChild);
	}
}
void deleteHeapMin(char* name)
{
	int instanceId = getHeapIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (heapValuesCount[instanceId] == 0)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	deleteHeapItemAtIndex(instanceId, 0);
}
int getItemIndex(int instanceId, Item *value,int startPos)
{
	if (startPos >= heapValuesCount[instanceId])
		return -1;
	if (heapValues[instanceId][startPos] == *value)
		return startPos;
	if (heapValues[instanceId][startPos] > *value)
		return -1;
	int index = getItemIndex(instanceId, value, getLeftChildIndex(startPos));
	if(index==-1)
		index = getItemIndex(instanceId, value, getRightChildIndex(startPos));
	return index;
}
void deleteHeapItem(char* name, Item *value)
{
	int instanceId = getHeapIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int position = getItemIndex(instanceId, value, 0);
	if (position == -1)
	{
		errorDetected(NULL, IndexOutOfBounds);
		return;
	}
	deleteHeapItemAtIndex(instanceId, position);
}
void mergeHeaps(char *inst1, char *inst2)
{
	int instanceId1 = getHeapIndexInstance(inst1);
	if (instanceId1 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int instanceId2 = getHeapIndexInstance(inst2);
	if (instanceId2 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	for (int i = 0; i < heapValuesCount[instanceId2]; i++)
	{
		addHeapValue(instanceId1, heapValues[instanceId2][i]);
	}
}
void deleteHeap(char* name)
{
	int instanceId = getHeapIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	free(heapValues[instanceId]);
	free(heapInstances[instanceId]);
	for (int i = instanceId; i < heapInstacesCount-1; i++)
	{
		heapInstances[i] = heapInstances[i + 1];
		heapValues[i] = heapValues[i + 1];
		heapValuesCount[i] = heapValuesCount[i + 1];
	}
	heapValues = realloc(heapValues, (heapInstacesCount + 3) * sizeof(Item*));
	heapInstacesCount--;
}
