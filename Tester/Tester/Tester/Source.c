#include<stdio.h>
#include <sys/types.h>
#include <tchar.h> 
#include<string.h>
#include <windows.h>
#include<stdlib.h>
#include <time.h>
void waitFor(unsigned int miliSecs)
{
	clock_t start = clock();
	while (clock() - start < miliSecs);
	/*unsigned int retTime = time(0) + secs;
	while (time(0) < retTime);*/
}
int doesFileExists(char *name)
{
	FILE *file = fopen(name, "r");
	if (file!=NULL)
	{
		fclose(file);
		return 1;
	}
	return 0;
}
int readFile(char *filename,char ** lines)
{
	FILE *file;
	file = fopen(filename, "r");
	int countLines = 0;
	//lines = (char**)malloc(sizeof(char*) * 100);
	lines[countLines] = (char*)malloc(200);
	while (fgets(lines[countLines++], 100, file))
	{
		lines[countLines] = (char*)malloc(200);
	}
	fclose(file);
	return countLines;
}
int checkResult(char *originalFile)
{
	char **resultLines= (char**)malloc(sizeof(char*) * 100);
	char **outputLines= (char**)malloc(sizeof(char*) * 100);
	for (int i = 0; i < 100; i++)
	{
		resultLines[i] = (char*)malloc(200);
		outputLines[i] = (char*)malloc(200);
		strcpy(resultLines[i], "");
		strcpy(outputLines[i], "");
	}
	char *file = malloc(200);
	strcpy(file, "Results\\");
	strcat(file, originalFile);
	strcat(file, ".res");
	int countResultLines = readFile(file, resultLines);
	strcpy(file, "Output\\");
	strcat(file, originalFile);
	strcat(file, ".out");
	if (doesFileExists(file)==0)
	{
		printf("Nu exista fisier de iesire pentru testul curent\n");
		return 2;
	}
	int countOutputLines = readFile(file, outputLines);
	if (countOutputLines != countResultLines)
		return 0;
	for (int i = 0; i < countOutputLines; i++)
	{
		if (strcmp(resultLines[i], outputLines[i]) != 0)
			return 0;
	}
	return 1;
}
void runSingle(char* file)
{
	char *aux = malloc(200);
	strcpy(aux, "Input\\");
	strcat(aux, file);
	strcat(aux, ".in");
	if (doesFileExists(aux) == 0)
	{
		printf("%s does not exists\n",file);
		return;
	}
	FILE *currentTest = fopen("currentTest.in", "w");
	fprintf(currentTest, "%s", file);
	fclose(currentTest);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	int start = clock();
	double duration;
	if (!CreateProcess
	(
		TEXT("Vector.exe"),
		NULL, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE,
		NULL, NULL,
		&si,
		&pi
	))
	{
		printf("error");
	}
	else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		duration = (clock() - start);
		printf("rulat cu %s  RESULT=", file);
		//waitFor(3000);
		int res = checkResult(file);
		if (res == 1)
		{
			printf("OK\n");
		}
		else if(res==0)
		{
			printf("NOT OK\n");
		}
	}
	duration /= CLOCKS_PER_SEC;
	printf("Runtime %.3fs\n", duration);
}
void runAll()
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;
	char path[] = "Inputs";
	//szDir = "Inputs\\*";
	szDir[0] = 'I';
	szDir[1] = 'n';
	szDir[2] = 'p';
	szDir[3] = 'u';
	szDir[4] = 't';
	szDir[5] = '\\';
	szDir[6] = '*';
	szDir[7] = '\0';
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		//return 0;
	}
	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//printf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			char *c = malloc(200);
			strcpy(c, ffd.cFileName);
			int count = 0;
			while (ffd.cFileName[count] != '\0' || count==100)
			{
				c[count] = ffd.cFileName[count];
				count++;
			}
			c[count] = '\0';
			//
			int posBeforeDot = strlen(c) - 3;
			if (c[posBeforeDot] == '.' && c[posBeforeDot + 1] == 'i' && c[posBeforeDot + 2] == 'n')
			{
				c[posBeforeDot] = '\0';
				runSingle(c);
			}
			else
			{
				printf("%s is not compatible\n", c);
			}
			free(c);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

}
void runInterval(char *from, char *to)
{
	if (from[strlen(from) - 1] > to[strlen(to) - 1])
	{
		printf("Interval gresit!Primul mai mare ca al doilea\n");
		return;
	}
	while (from[strlen(from) - 1] <=to[strlen(to) - 1])
	{
		runSingle(from);
		from[strlen(from) - 1]++;
	}
}
int main(int argc, char **argv)
{
	//doesFileExists("Vector.exe2");
	//runAll();
	//checkResult("data1");
	//runSingle("data1");
	//char from[] = "data1";
	//runInterval(from, "data2");
	if (argc == 2)
	{
		if (strcmp(argv[1], "runall")==0)
		{
			printf("ruleaza toate teste\n");
			runAll();
		}
		else
		{
			runSingle(argv[1]);
		}
	}
	else if(argc>=3)
	{
		printf("ruleaza in interval\n");
		runInterval(argv[1], argv[2]);
	}
}