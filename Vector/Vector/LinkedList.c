#include "LinkedList.h"
#include "Errors.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char **linkedListInstances;
int linkedListInstacesCount = 0;
LinkedItem **linkedListValues;
int getLinekdListIndexInstance(char* name)
{
	for (int i = 0; i < linkedListInstacesCount; i++)
	{
		if (strcmp(linkedListInstances[i], name) == 0)
		{
			return i;
		}
	}
	return -1;
}
void createLinkedList(char* name)
{
	if (linkedListInstacesCount == 0)
	{
		linkedListInstances = (char**)malloc(1 * sizeof(char*));
		linkedListValues = malloc(5 * sizeof(LinkedItem*));
	}
	else
	{
		int instanceId = getLinekdListIndexInstance(name);
		if (instanceId != -1)
		{
			errorDetected(NULL, StructureAlreadyExists);
			return;
		}
		linkedListInstances = (char**)realloc(linkedListInstances, (linkedListInstacesCount + 3) * sizeof(char*));
		linkedListValues = realloc(linkedListValues, (linkedListInstacesCount + 3) * sizeof(LinkedItem*));
	}
	linkedListValues[linkedListInstacesCount] = malloc(5 * sizeof(LinkedItem*));
	linkedListValues[linkedListInstacesCount]->next = NULL;
	linkedListInstances[linkedListInstacesCount] = malloc(20);
	strcpy(linkedListInstances[linkedListInstacesCount], name);
	linkedListInstacesCount++;
}

void printLinkedList(char* name)
{
	int instanceId = getLinekdListIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (linkedListValues[instanceId]->next == NULL)
	{
		errorDetected(NULL, StructureEmpty);
		return;
	}
	LinkedItem *current = linkedListValues[instanceId];
	while (current->next!=NULL)
	{
		WRITEINT(current->data);
		current = current->next;
	}
	WRITELINE();
}
LinkedItem *getLastLinkedItem(int instanceId)
{
	LinkedItem *last=linkedListValues[instanceId];
	while(last->next!=NULL)
	{
		last= last->next;
	}
	return last;
}
void addLinkedListItems(command *com)
{
	int instanceId = getLinekdListIndexInstance((char*)com->parameters.values[0]);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	LinkedItem *last = getLastLinkedItem(instanceId);
	for (int i =0; i <((int)com->parameters.values[1]); i++)
	{
		last->data = com->parameters.values[i + 2];
		last->next = malloc(sizeof(LinkedItem));
		last->next->next = NULL;
		last = last->next;
	}
}
LinkedItem *getLinkedListItemByIndex(int instanceId,int index)
{
	LinkedItem *current = linkedListValues[instanceId];
	int count = 0;
	while (current->next != NULL)
	{
		if (count == index)
			break;
		count++;
		current = current->next;
	}
	return current;
}
void putLinkedListItems(char* name, int index, Item value)
{
	int instanceId = getLinekdListIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	LinkedItem *item = getLinkedListItemByIndex(instanceId, index);
	if (item->next==NULL)
	{
		errorDetected(NULL, IndexOutOfBounds);
		return;
	}
	item->data = value;
}
Item getLinkedListItem(char* name, int index)
{
	int instanceId = getLinekdListIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	LinkedItem *item = getLinkedListItemByIndex(instanceId, index);
	if (item->next == NULL)
	{
		errorDetected(NULL, IndexOutOfBounds);
		return;
	}
	return item->data;
}
void deleteLinkedListItem(char* name, int index)
{
	int instanceId = getLinekdListIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	if (index == 0)
	{
		if (linkedListValues[instanceId]->next == NULL)
		{
			errorDetected(NULL, IndexOutOfBounds);
			return;
		}
		else
		{
			linkedListValues[instanceId] = linkedListValues[instanceId]->next;
		}
	}
	else
	{
		LinkedItem *item = getLinkedListItemByIndex(instanceId, index-1);
		if (getLinkedListItemByIndex(instanceId, index) == NULL)
		{
			errorDetected(NULL, IndexOutOfBounds);
			return;
		}
		item->next = item->next->next;
	}
}
int searchLinkedListItem(char* name, Item value)
{
	int instanceId = getLinekdListIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	LinkedItem *current = linkedListValues[instanceId];
	int count = 0;
	int founded = 0;
	while (current->next != NULL)
	{
		if (current->data == value)
		{
			founded = 1;
			break;
		}
		count++;
		current = current->next;
	}
	if (founded == 0)
		return -1;
	return count;
}
void sortLinkedList(char* name)
{
	int instanceId = getLinekdListIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	LinkedItem *current = linkedListValues[instanceId];
	while (current->next != NULL)
	{
		LinkedItem *subItem = current->next;
		while (subItem->next != NULL)
		{
			if ((int)current->data > (int)subItem->data)
			{
				Item aux = current->data;
				current->data = subItem->data;
				subItem->data = aux;
			}
			subItem = subItem->next;
		}
		current = current->next;
	}
}
void mergeLinkedLists(char *inst1, char *inst2)
{
	int instanceId1 = getLinekdListIndexInstance(inst1);
	if (instanceId1 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	int instanceId2 = getLinekdListIndexInstance(inst2);
	if (instanceId2 == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	LinkedItem *last = getLastLinkedItem(instanceId1);
	LinkedItem *current = linkedListValues[instanceId2];
	while (current->next != NULL)
	{
		last->data = current->data;
		last->next = malloc(sizeof(LinkedItem));
		last->next->next = NULL;
		current = current->next;
		last= last->next;

	}
}
void deleteLinkedListSubItems(LinkedItem *item)
{
	if (item->next != NULL)
	{
		deleteLinkedListSubItems(item->next);
	}
	free(item);
}
void deleteLinkedList(char* name)
{
	int instanceId = getLinekdListIndexInstance(name);
	if (instanceId == -1)
	{
		errorDetected(NULL, InexistantStructure);
		return;
	}
	deleteLinkedListSubItems(linkedListValues[instanceId]);
	for (int i = instanceId; i < linkedListInstacesCount - 1; i++)
	{
		linkedListValues[i] = linkedListValues[i + 1];
		linkedListInstances[i] = linkedListInstances[i + 1];
	}
	linkedListInstacesCount--;
	linkedListValues = realloc(linkedListValues, (linkedListInstacesCount + 3) * sizeof(LinkedItem*));
}