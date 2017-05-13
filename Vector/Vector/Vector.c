#include "Vector.h"
#include "Errors.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char **vectorInstances;
int vectorInstacesCount = 0;
Item **vectorValues;
int getVectorIndexInstance(char* name)
{
	for (int i = 0; i < vectorInstacesCount; i++)
	{
		if (strcmp(vectorInstances[i], name) == 0)
		{
			return i;
		}
	}
	return -1;
}
void createVector(char* name)
{
	if (vectorInstacesCount == 0)
	{
		vectorInstances = (char**)malloc(1 * sizeof(char*));
		vectorValues = malloc(1 * sizeof(Item*));
	}
	else
	{
		int instanceId = getVectorIndexInstance(name);
		if (instanceId != -1)
		{
			errorDetected(NULL, StructureAlreadyExists);
			return;
		}
		vectorInstances = (char**)realloc(vectorInstances, (vectorInstacesCount + 1) * sizeof(char*));
		vectorValues = realloc(vectorValues,(vectorInstacesCount+1) * sizeof(Item*));
	}
	vectorValues[vectorInstacesCount] = malloc(1 * sizeof(Item));
	vectorValues[vectorInstacesCount][0] = 0;
	vectorInstances[vectorInstacesCount] = malloc(20);
	strcpy(vectorInstances[vectorInstacesCount], name);
	vectorInstacesCount++;
}
void printVector(char* name)
{
	int instanceId = getVectorIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if ((int)vectorValues[instanceId][0] == 0)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	for (int i = 0; i < (int)vectorValues[instanceId][0]; i++)
	{
		WRITEINT(vectorValues[instanceId][i + 1]);
	}
	WRITELINE();
}
void addVectorItems(command *com)
{
	int instanceId = getVectorIndexInstance((char*)com->parameters.values[0]);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int newSize = (((int)vectorValues[instanceId][0]) + ((int)com->parameters.values[1]) + 2) * sizeof(Item);
	vectorValues[instanceId] = (Item*)realloc(vectorValues[instanceId], newSize);
	for (int i = (int)vectorValues[instanceId][0]+1; i <((int)com->parameters.values[1]) +(int)vectorValues[instanceId][0]+1; i++)
	{
		vectorValues[instanceId][i] = com->parameters.values[i - (int)vectorValues[instanceId][0] + 1];
	}
	vectorValues[instanceId][0] = (int)com->parameters.values[1]+ (int)vectorValues[instanceId][0];
}
void putVectorItems(char* name, int index, Item value)
{
	int instanceId = getVectorIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (index < 0 || index >= vectorValues[instanceId][0])
	{
		errorDetected(NULL, IndexOutOfBounds);
		return;
	}
	vectorValues[instanceId][index + 1] = value;
}
Item getVectorItem(char* name, int index)
{
	int instanceId = getVectorIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (index < 0 || index >= vectorValues[instanceId][0])
	{
		errorDetected(NULL, IndexOutOfBounds);
		return;
	}
	return vectorValues[instanceId][index + 1];
}
void deleteVectorItem(char* name, int index)
{
	int instanceId = getVectorIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (index < 0 || index >= vectorValues[instanceId][0])
	{
		errorDetected(NULL, IndexOutOfBounds);
		return;
	}
	for (int i = index + 1; i <(int)vectorValues[instanceId][0]; i++)
	{
		vectorValues[instanceId][i] = vectorValues[instanceId][i + 1];
	}
	vectorValues[instanceId][0] = (int)vectorValues[instanceId][0] - 1;
}
int searchVectorItem(char* name, Item value)
{
	int instanceId = getVectorIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	for (int i =1; i <(int)vectorValues[instanceId][0]+1; i++)
	{
		if (value == vectorValues[instanceId][i])
		{
			return i - 1;
		}
	}
	return -1;
}
void sortVector(char* name)
{
	int instanceId = getVectorIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	for (int i =  1; i <(int)vectorValues[instanceId][0]+1; i++)
	{
		for (int j = i + 1; j < (int)vectorValues[instanceId][0] + 1; j++)
		{
			if ((int)vectorValues[instanceId][i] > (int)vectorValues[instanceId][j])
			{
				int aux = (int)vectorValues[instanceId][i];
				vectorValues[instanceId][i] = (int)vectorValues[instanceId][j];
				vectorValues[instanceId][j] = aux;
			}
		}
	}
	//vectorValues[instanceId][0] = (int)vectorValues[instanceId][0] - 1;
}
void mergeVectors(char *inst1, char *inst2)
{
	int instanceId1 = getVectorIndexInstance(inst1);
	if (instanceId1 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int instanceId2 = getVectorIndexInstance(inst2);
	if (instanceId2 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int initialSize = (int)vectorValues[instanceId1][0];
	vectorValues[instanceId1][0] = (int)vectorValues[instanceId1][0] + (int)vectorValues[instanceId2][0];
	int newSize = ((int)vectorValues[instanceId1][0] + 5) * sizeof(Item);
	vectorValues[instanceId1] = (Item*)realloc(vectorValues[instanceId1], newSize);
	for (int i = 0; i < (int)vectorValues[instanceId2][0]; i++)
	{
		vectorValues[instanceId1][i+ initialSize + 1] = (int)vectorValues[instanceId2][i + 1];
	}
}
void deleteVector(char* name)
{
	int instanceId = getVectorIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	free(vectorValues[instanceId]);
	for (int i = instanceId; i < vectorInstacesCount-1; i++)
	{
		vectorValues[i] = vectorValues[i + 1];
		vectorInstances[i] = vectorInstances[i + 1];
	}
	vectorInstacesCount--;
	vectorValues = realloc(vectorValues, (vectorInstacesCount + 1) * sizeof(Item*));
}