// Create and read functions in framework.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "removeNewLine.c"
#define MENU_FILE "menu1.cfg"
#define FIELDNAMES_FILE "fieldNames.cfg"
#define FIELDVALUES_FILE "field.dat"
#define LINE_LENGTH 70
char **fieldNames;
int linesCounter, linesCount;
char fieldValues[LINE_LENGTH];
char **loadAndCountLines(char *fileName)
{
	linesCounter = 0;
	char **lines;
	char line[LINE_LENGTH];
	FILE *fpLines;
	fpLines = fopen(fileName, "r");
	while (fgets(line, LINE_LENGTH, fpLines) != NULL)
	{
		linesCounter++;
	}
	linesCount = linesCounter;
	lines = malloc((linesCount + 1) * sizeof(char *));
	lines[0] = malloc(LINE_LENGTH);
	sprintf(lines[0], "%d", linesCount);
	rewind(fpLines);
	for(linesCounter = 1; linesCounter <= linesCount; linesCounter++)
	{
		lines[linesCounter] = malloc(LINE_LENGTH);
		fgets(lines[linesCounter], LINE_LENGTH, fpLines);
		removeNewLine(lines[linesCounter]);
	} 
	fclose(fpLines);
	return(lines);
}
int main()
{
	fieldNames = loadAndCountLines(FIELDNAMES_FILE);
	showMenu();
}
int showMenu()
{
	char **menuLines;
	menuLines = loadAndCountLines(MENU_FILE);
	printf("%d\n", linesCount);
	int option;
	do
	{
		linesCount = atoi(menuLines[0]);
		printf("%d\n", linesCount);
		for(linesCounter = 1; linesCounter <= linesCount; linesCounter++)
		{
			printf("%s", menuLines[linesCounter]);
			if(linesCounter != linesCount)
		  	{
		  		printf("\n");
			}
		}
		scanf("%d", &option);
		switch (option)
		{
			case 1: Create();
					break;
			case 2: Display();
					break;
			default: printf("Exit.");
					 exit(0);
		}
	} while (option != 3);
}
int Create()
{
	FILE *fpFieldValues;
	fpFieldValues = fopen(FIELDVALUES_FILE, "a");
	fflush(stdin);
	linesCount = atoi(fieldNames[0]);
	for(linesCounter = 1; linesCounter <= linesCount; linesCounter++)
	{
		printf("Enter the %s: ", fieldNames[linesCounter]);
		fgets(fieldValues, sizeof(fieldValues), stdin);
		fwrite(fieldValues, sizeof(fieldValues), 1, fpFieldValues);
		// fprintf(fpFieldValues, "%s", fieldValues);
	}
	fclose(fpFieldValues);
}
int Display()
{
	int dataFound = 0;
	FILE *fpFieldValues;
	fpFieldValues = fopen(FIELDVALUES_FILE, "r");
	fflush(stdin);
	linesCount = atoi(fieldNames[0]);
	for(linesCounter = 1; linesCounter <= linesCount; linesCounter++)
	{
		if( fread(fieldValues, sizeof(fieldValues), 1, fpFieldValues) == 1)
		{
			dataFound = 1;
			printf("%s: %s", fieldNames[linesCounter], fieldValues);
		}
		else
		{
			break;
		}
		if(linesCounter == linesCount)
		{
			linesCounter = 0;
		}
	}
	if ( dataFound != 1)
	{
		printf("No data found!\n");
	}
	fclose(fpFieldValues);
}
