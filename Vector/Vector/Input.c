#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Input.h"
char** lines;
char* currentLine;
int countLines;
command *commands;
int countCommands;
int lastGavedCommand = 0;
char* processDataInput(char* data)
{
	int firstWordRemoved = 0;
	for (int i = 0; i < strlen(data); i++)
	{
		if ((data[i] == '\n' || data[i] == ' ') && firstWordRemoved==0)
		{
			firstWordRemoved = 1;
			data += i;
			i = -1;
		}
		else if (data[i] == '\n')
			data[i] = ' ';
	}
	return data;
}
void calculateStructure(command *com)
{
	int* valuesTypeOrder = (int*)malloc(4 * sizeof(int));
	int valuesTypeOrderCount = 0;
	int wordInt = 0;
	int wordChar = 0;
	int wordDouble = 0;
	int justNumbers = 1;
	int containsPoint = 0;
	int wordDetected = 0;
	for (int i = 0; i < strlen(com->parameters.data); i++)
	{
		if (com->parameters.data[i] == ' ' && wordDetected==1)
		{
			wordDetected = 0;
			if (justNumbers == 1)
			{
				if (containsPoint == 0)
				{
					wordDouble++;
					valuesTypeOrder[valuesTypeOrderCount++] = integer;
				}
				else
				{
					wordInt++;
					valuesTypeOrder[valuesTypeOrderCount++] = real;
				}
			}
			else
			{
				wordChar++;
				valuesTypeOrder[valuesTypeOrderCount++] = string;
			}
			valuesTypeOrder = (int*)realloc(valuesTypeOrder,(valuesTypeOrderCount+4) * sizeof(int));
			justNumbers = 1;
			containsPoint = 0;
		}
		if (com->parameters.data[i] == '.')
			containsPoint = 1;
		if ((!((com->parameters.data[i] >= '0' &&com->parameters.data[i] <= '9')|| com->parameters.data[i] == '-')) && com->parameters.data[i] != ' ')
		{
			justNumbers = 0;
		}
		if (com->parameters.data[i] != ' ')
			wordDetected = 1;
	}
	if (wordDetected == 1)
	{
		if (justNumbers == 1)
		{
			if (containsPoint == 1)
			{
				wordDouble++;
				valuesTypeOrder[valuesTypeOrderCount++] = real;
			}
			else
			{
				wordInt++;
				valuesTypeOrder[valuesTypeOrderCount++] = integer;
			}
		}
		else
		{
			wordChar++;
			valuesTypeOrder[valuesTypeOrderCount++] = string;
		}
		valuesTypeOrder = (int*)realloc(valuesTypeOrder,(valuesTypeOrderCount+3) * sizeof(int));
	}
	com->struc.stringCount = wordChar;
	com->struc.intCount = wordInt;
	com->struc.doubleCount = wordDouble;
	com->struc.dataTypeOrder = valuesTypeOrder;
	com->struc.dataTypeCount = valuesTypeOrderCount;
}
char* removeUntilFirstSpace(char* text)
{
	int last = -1;
	for (int i = 0; i < strlen(text) - 1; i++)
	{
		if (text[i] == ' ')
		{
			last = i;
		}
		if (text[i] != ' ' && last!=-1)
		{
			text = text + last + 1;
			last = -1;
			break;
		}
	}
	if (last != -1)
	{
		text = text + last + 1;
	}
	return text;
}
void extractValues(command *com)
{
	char* aux = malloc(500);
	strcpy(aux, com->parameters.data);
	aux=removeUntilFirstSpace(aux);
	for (int i = 0; i < com->struc.dataTypeCount; i++)
	{
		if (com->struc.dataTypeOrder[i] == integer)
		{
			com->parameters.values[com->parameters.valuesCount] = malloc(sizeof(int));
			sscanf(aux, "%d", &(com->parameters.values[com->parameters.valuesCount]));
			com->parameters.valuesCount++;
		}
		else if (com->struc.dataTypeOrder[i] == real)
		{
			com->parameters.values[com->parameters.valuesCount] = malloc(sizeof(double));
			sscanf(aux, "%f", &(com->parameters.values[com->parameters.valuesCount]));
			com->parameters.valuesCount++;
		}
		else if (com->struc.dataTypeOrder[i] == string)
		{
			com->parameters.values[com->parameters.valuesCount] = malloc(sizeof(char)*500);
			sscanf(aux, "%s", (com->parameters.values[com->parameters.valuesCount]));
			com->parameters.valuesCount++;
		}
		com->parameters.values = realloc(com->parameters.values, (com->parameters.valuesCount+2) * sizeof(Item));
		aux = removeUntilFirstSpace(aux);
	}
	//free(aux);
}
int getCommandIndex(char *text)
{
	char *firstWord=(char*)malloc(strlen(text)+20);
	sscanf(text, "%s", firstWord);
	if (strcmp(firstWord, "CreateVector") == 0)
	{
		free(firstWord);
		return 0;
	}
	else if (strcmp(firstWord, "PrintVector") == 0)
	{
		free(firstWord);
		return 1;
	}
	else if (strcmp(firstWord, "AddVectorItems") == 0)
	{
		free(firstWord);
		return 2;
	}
	else if (strcmp(firstWord, "PutVectorItem") == 0)
		return 3;
	else if (strcmp(firstWord, "GetVectorItem") == 0)
		return 4;
	else if (strcmp(firstWord, "DeleteVectorItem") == 0)
		return 5;
	else if (strcmp(firstWord, "SearchVectorItem") == 0)
		return 6;
	else if (strcmp(firstWord, "SortVector") == 0)
		return 7;
	else if (strcmp(firstWord, "MergeVectors") == 0)
		return 8;
	else if (strcmp(firstWord, "DeleteVector") == 0)
		return 9;
	else if (strcmp(firstWord, "CreateLinkedList") == 0)
	{
		free(firstWord);
		return 10;
	}
	else if (strcmp(firstWord, "PrintLinkedList") == 0)
	{
		free(firstWord);
		return 11;
	}
	else if (strcmp(firstWord, "AddLinkedListItems") == 0)
	{
		free(firstWord);
		return 12;
	}
	else if (strcmp(firstWord, "PutLinkedListItem") == 0)
		return 13;
	else if (strcmp(firstWord, "GetLinkedListItem") == 0)
		return 14;
	else if (strcmp(firstWord, "DeleteLinkedListItem") == 0)
		return 15;
	else if (strcmp(firstWord, "SearchLinkedListItem") == 0)
		return 16;
	else if (strcmp(firstWord, "SortLinkedList") == 0)
		return 17;
	else if (strcmp(firstWord, "MergeLinkedLists") == 0)
		return 18;
	else if (strcmp(firstWord, "DeleteLinkedList") == 0)
		return 19;
	else if (strcmp(firstWord, "CreateHashTable") == 0)
	{
		free(firstWord);
		return 20;
	}
	else if (strcmp(firstWord, "PrintHashTable") == 0)
	{
		free(firstWord);
		return 21;
	}
	else if (strcmp(firstWord, "AddHashTableItem") == 0)
	{
		free(firstWord);
		return 22;
	}
	else if (strcmp(firstWord, "DeleteHashTableItem") == 0)
		return 23;
	else if (strcmp(firstWord, "SearchHashTableItem") == 0)
		return 24;
	else if (strcmp(firstWord, "ReHashTable ") == 0)
		return 25;
	else if (strcmp(firstWord, "DeleteHashTable") == 0)
		return 26;
	else if (strcmp(firstWord, "CreateHeap") == 0)
	{
		free(firstWord);
		return 27;
	}
	else if (strcmp(firstWord, "PrintHeap") == 0)
	{
		free(firstWord);
		return 28;
	}
	else if (strcmp(firstWord, "AddHeapItem") == 0)
	{
		free(firstWord);
		return 29;
	}
	else if (strcmp(firstWord, "GetHeapMin") == 0)
		return 30;
	else if (strcmp(firstWord, "DeleteHeapMin") == 0)
		return 31;
	else if (strcmp(firstWord, "DeleteHeapItem") == 0)
		return 32;
	else if (strcmp(firstWord, "MergeMinHeaps") == 0)
		return 33;
	else if (strcmp(firstWord, "DeleteHeap") == 0)
		return 34;
	else if (strcmp(firstWord, "CreateBST") == 0)
	{
		free(firstWord);
		return 35;
	}
	else if (strcmp(firstWord, "PrintBST") == 0)
	{
		free(firstWord);
		return 36;
	}
	else if (strcmp(firstWord, "PreorderBST") == 0)
		return 37;
	else if (strcmp(firstWord, "InorderBST") == 0)
		return 38;
	else if (strcmp(firstWord, "PostorderBST") == 0)
		return 39;
	else if (strcmp(firstWord, "AddBSTItem") == 0)
	{
		free(firstWord);
		return 40;
	}
	else if (strcmp(firstWord, "SearchBSTItem") == 0)
		return 41;
	else if (strcmp(firstWord, "DeleteBSTItem") == 0)
		return 42;
	else if (strcmp(firstWord, "MergeBSTs") == 0)
		return 43;
	else if (strcmp(firstWord, "HightBST") == 0)
		return 44;
	else if (strcmp(firstWord, "DeleteBST") == 0)
		return 45;
	else if (strcmp(firstWord, "CreateBalancedBST") == 0)
	{
		free(firstWord);
		return 46;
	}
	else if (strcmp(firstWord, "PrintBalancedBST") == 0)
	{
		free(firstWord);
		return 47;
	}
	else if (strcmp(firstWord, "PreorderBalancedBST") == 0)
		return 48;
	else if (strcmp(firstWord, "InorderBalancedBST") == 0)
		return 49;
	else if (strcmp(firstWord, "PostorderBalancedBST") == 0)
		return 50;
	else if (strcmp(firstWord, "AddBalancedBSTItem") == 0)
	{
		free(firstWord);
		return 51;
	}
	else if (strcmp(firstWord, "SearchBalancedBSTItem") == 0)
		return 52;
	else if (strcmp(firstWord, "DeleteBalancedBSTItem") == 0)
		return 53;
	else if (strcmp(firstWord, "MergeBalancedBSTs") == 0)
		return 54;
	else if (strcmp(firstWord, "HightBalancedBST") == 0)
		return 55;
	else if (strcmp(firstWord, "DeleteBalancedBST") == 0)
		return 56;
	return -1;
}
void readLines(char *fileName)
{
	commands = (command*)malloc(2 * sizeof(command*));
	FILE *file;
	file = fopen(fileName, "r");
	countLines = 0;
	lines = (char**)malloc(sizeof(char*) * 100);
	lines[countLines] = (char*)malloc(200);
	while (fgets(lines[countLines++], 100, file))
	{
		lines[countLines] = (char*)malloc(200);
	}
	countLines--;
}
void processLines()
{
	for (int i = 0; i < countLines; i++)
	{

		int commandIndex = getCommandIndex(lines[i]);
		if (commandIndex != -1)
		{
			currentLine = (char*)malloc(5+strlen(lines[i]));
			strcpy(currentLine, lines[i]);
			for (int j = i + 1; j < countLines; j++)
			{
				if (getCommandIndex(lines[j]) == -1)
				{
					currentLine = realloc(currentLine, strlen(currentLine) + strlen(lines[j])+50);
					currentLine = strcat(currentLine, lines[j]);
					i = j;
				}
				else
				{
					break;
				}
			}
			commands = (command*)realloc(commands, (countCommands+5) * sizeof(command));
			commands[countCommands].type = (commandType)commandIndex;
			commands[countCommands].parameters.data = (char*)malloc(500);
			strcpy(commands[countCommands].parameters.data, currentLine);
			commands[countCommands].parameters.valuesCount = 0;
			commands[countCommands].parameters.values = (Item*)malloc(1 * sizeof(Item));
			commands[countCommands].parameters.data=processDataInput(commands[countCommands].parameters.data);
			calculateStructure(&commands[countCommands]);
			extractValues(&commands[countCommands]);
			countCommands++;
			free(currentLine);
		}
	}
}
int checkFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	if (file != NULL)
	{
		fclose(file);
		return 1;
	}
	return 0;
}
void init(char *fileName)
{
	if (checkFile(fileName) == 0)
	{
		printf("Invalid file!");
		return;
	}
	readLines(fileName);
	processLines();
	for (int i = 0; i < countCommands; i++)
	{
		printf("%d \n", commands[i].type);
		for (int j = 0; j < commands[i].parameters.valuesCount; j++)
		{
			if (commands[i].struc.dataTypeOrder[j] == integer)
				printf("%d ", (int)commands[i].parameters.values[j]);
			else
				if (commands[i].struc.dataTypeOrder[j] == string)
					printf("%s ", (char*)commands[i].parameters.values[j]);
		}
		printf("\n");
	}
}
command* getNextCommand()
{
	if (lastGavedCommand == countCommands)
		return NULL;
	return &commands[lastGavedCommand++];
}