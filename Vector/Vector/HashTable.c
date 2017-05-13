#include "HashTable.h"
#include "Errors.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char ***hashTableInstances;
unsigned long(**hashTableFunctions)(unsigned char*);
int hashTableInstacesCount = 0;
LinkedItem ***hashTableValues;
int* hastTableValuesCount;
int* hastTableValuesType;
int *modulo;
int getHastTableIndexInstance(char* name)
{
	for (int i = 0; i < hashTableInstacesCount; i++)
	{
		if (strcmp(hashTableInstances[i], name) == 0)
		{
			return i;
		}
	}
	return -1;
}
unsigned long calculateHash(unsigned char *str) {
	unsigned long hash = 5381; int c;
	while (c = *str++)
	{
		hash = ((hash << 5) + hash);
		hash = hash ^ c;
	}
	return hash;
}
unsigned long hash(unsigned char *str,int index)
{
	unsigned long(*hashFunction)(unsigned char*);
	hashFunction = hashTableFunctions[index];
	return hashFunction(str);
}
unsigned long hashWithType(Item *str,dataType type,int instanceId)
{
	if(type==string)
		return hash(str,instanceId);
	return (int)str;
}
LinkedItem *getLastHashItem(LinkedItem *item)
{
	LinkedItem *last = item;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return last;
}
void createHashTable(char* name)
{
	if (hashTableInstacesCount == 0)
	{
		hashTableInstances = (char**)malloc(1 * sizeof(char*));
		modulo = malloc(5 * sizeof(int));
		hashTableValues = malloc(5 * sizeof(LinkedItem**));
		hastTableValuesCount = malloc(5 * sizeof(int));
		hastTableValuesType = malloc(5 * sizeof(int));
		hashTableFunctions = malloc(5 * sizeof(void*));
	}
	else
	{
		int instanceId = getHastTableIndexInstance(name);
		if (instanceId != -1)
		{
			errorDetected(NULL, StructureAlreadyExists);
			return;
		}
		hashTableInstances = (char**)realloc(hashTableInstances, (hashTableInstacesCount + 1) * sizeof(char*));
		hashTableValues = realloc(hashTableValues, (hashTableInstacesCount + 3) * sizeof(LinkedItem**));
		hastTableValuesCount = realloc(hastTableValuesCount, (hashTableInstacesCount + 3) * sizeof(int));
		hastTableValuesType = realloc(hastTableValuesType, (hashTableInstacesCount + 3) * sizeof(int));
		modulo = realloc(modulo, (hashTableInstacesCount + 3) * sizeof(int));
	}
	modulo[hashTableInstacesCount] = 100;
	hashTableFunctions[hashTableInstacesCount] = calculateHash;
	hastTableValuesCount[hashTableInstacesCount] = 0;
	hastTableValuesType[hashTableInstacesCount] =integer;
	hashTableValues[hashTableInstacesCount] = malloc((modulo[hashTableInstacesCount]+3) * sizeof(LinkedItem*));
	for (int i = 0; i < modulo[hashTableInstacesCount]; i++)
	{
		hashTableValues[hashTableInstacesCount][i] = malloc(sizeof(LinkedItem));
		hashTableValues[hashTableInstacesCount][i]->next = NULL;
	}
	hashTableInstances[hashTableInstacesCount] = malloc(20);
	strcpy(hashTableInstances[hashTableInstacesCount], name);
	hashTableInstacesCount++;
}
void createHashTableWithFunction(char* name, unsigned long(*hashFunction)(unsigned char*))
{
	createHashTable(name);
	int instanceId = getHastTableIndexInstance(name);
	if (instanceId != -1)
	{
		hashTableFunctions[instanceId] = hashFunction;
	}
}
void printHashTable(char* name)
{
	int instanceId = getHastTableIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (hastTableValuesCount[instanceId] == 0)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	for (int i = 0; i < modulo[instanceId]; i++)
	{
		LinkedItem *current = hashTableValues[instanceId][i];
		if (current->next == NULL)
			continue;
		WRITESTRINGSAMELINE("[");
		WRITEINT(i);
		WRITESTRINGSAMELINE("]={");
		while (current->next != NULL)
		{
			WRITEINT(current->data);
			current = current->next;
			if (current->next != NULL)
				WRITESTRINGSAMELINE(",");
		}
		WRITESTRINGSAMELINE("};");
	}
	WRITELINE();
	
}
void addHashTableItem(int instanceId, Item value, dataType type)
{
	unsigned long hashCode = hashWithType(value, type, instanceId);
	LinkedItem *last = getLastHashItem(hashTableValues[instanceId][hashCode%modulo[instanceId]]);
	last->data = value;
	last->next = malloc(sizeof(LinkedItem));
	last->next->next = NULL;
}
void recalculateHash(int instanceId,int oldCount)
{
	LinkedItem **before = hashTableValues[instanceId];
	hashTableValues[instanceId] = malloc((modulo[instanceId] + 3) * sizeof(LinkedItem*));
	for (int i = 0; i < modulo[instanceId]; i++)
	{
		hashTableValues[instanceId][i] = malloc(sizeof(LinkedItem));
		hashTableValues[instanceId][i]->next = NULL;
	}
	for (int i = 0; i < oldCount; i++)
	{
		LinkedItem *current = before[i];
		while (current->next != NULL)
		{
			addHashTableItem(instanceId, current->data, hastTableValuesType[instanceId]);
			current = current->next;
		}
	}
	free(before);
}
void reHashTable(char* name, unsigned long(*hashFunction)(unsigned char*))
{
	int instanceId = getHastTableIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	hashTableFunctions[instanceId] = hashFunction;
	recalculateHash(instanceId,modulo[instanceId]);
}
void addHashTableItems(command *com)
{
	int instanceId = getHastTableIndexInstance((char*)com->parameters.values[0]);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if ((int)com->parameters.values[1] > 0)
	{
		hastTableValuesType[instanceId] = com->struc.dataTypeOrder[2];
	}
	for (int i =0; i <((int)com->parameters.values[1]); i++)
	{
		addHashTableItem(instanceId, com->parameters.values[i + 2], com->struc.dataTypeOrder[i + 2]);
	}
	hastTableValuesCount[instanceId] += (int)com->parameters.values[1];
	if (hastTableValuesCount[instanceId] > modulo[instanceId] * 3 / 4)
	{
		modulo[instanceId] *= 2;
		recalculateHash(instanceId,modulo[instanceId]/2);
	}
}
void deleteHashTableItem(char* name, Item *value,dataType type)
{
	int instanceId = getHastTableIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	unsigned long hashCode = hashWithType(value, type,instanceId);
	LinkedItem *searched =hashTableValues[instanceId][hashCode%modulo[instanceId]];
	LinkedItem *last = NULL;
	while (searched->next != NULL)
	{
		if (searched->data == value)
		{
			if (last == NULL)
			{
				//free(hashTableValues[instanceId][hashCode%modulo]);
				hashTableValues[instanceId][hashCode%modulo[instanceId]] = searched->next;
				
			}
			else
			{
				last->next = searched->next;
				
			}
			free(searched);
			return;
		}
		last = searched;
		searched = searched->next;
	}
	//errorDetected(com,)
}
int searchHashTableItem(char* name, Item value,dataType type)
{
	int instanceId = getHastTableIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	unsigned long hashCode = hashWithType(value, type,instanceId);
	LinkedItem *searched = hashTableValues[instanceId][hashCode%modulo[instanceId]];
	LinkedItem *last = NULL;
	while (searched->next != NULL)
	{
		if (type == string)
		{
			if (strcmp((char*)searched->data, (char*)value) == 0)
				return 1;

		}
		if (searched->data == value)
		{
			return 1;
		}
		last = searched;
		searched = searched->next;
	}
	return 0;
}
void deleteHashTableSubItems(LinkedItem *item)
{
	if (item->next != NULL)
	{
		deleteHashTableSubItems(item->next);
	}
	free(item);
}
void deleteHashTable(char* name)
{
	int instanceId = getHastTableIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	for (int i = 0; i < modulo[instanceId]; i++)
	{
		deleteHashTableSubItems(hashTableValues[instanceId][i]);
	}
	free(hashTableValues[instanceId]);
	for (int i = instanceId; i < hashTableInstacesCount - 1; i++)
	{
		hashTableValues[i] = hashTableValues[i + 1];
		hashTableInstances[i] = hashTableInstances[i + 1];
	}
	hashTableInstacesCount--;
	hashTableValues = realloc(hashTableValues, (hashTableInstacesCount + 3) * sizeof(LinkedItem**));
}