#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Input.h"
#include "Commander.h"
#define TESTEXTERNAL 0
int main(int argc, char **argv)
{
	
	FILE *currentTestFile = fopen("currentTest.in","r");
	char *originalfile = malloc(200 * sizeof(char));
	char *file = malloc(200 * sizeof(char));
	fscanf(currentTestFile,"%s", originalfile);
	printf("%s", originalfile);
	//char *aux = malloc(200);
#if TESTEXTERNAL==1
	strcpy(file, "Input\\");
	strcat(file, originalfile);
	strcat(file, ".in");
	init(file);
	strcpy(file, "Results\\");
	strcat(file, originalfile);
	strcat(file, ".res");
#endif // TESTEXTERNAL=1
#if TESTEXTERNAL==0
	//strcpy(file, "Input\\");
	strcpy(file, originalfile);
	strcat(file, ".in");
	init(file);
	//strcpy(file, "Results\\");
	strcpy(file, originalfile);
	strcat(file, ".out");
#endif

	
	outputFIle = fopen(file, "w");
	command* com = getNextCommand();
	while (com!=NULL)
	{
		giveCommand(com);
		com = getNextCommand();
	}
}