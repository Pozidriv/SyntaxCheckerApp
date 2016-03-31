#include<string.h>
#define MAX_LINE 100
typedef int BOOLEAN;

//Finished, tested
void initBuffer(char *inputLine);

//Finished
BOOLEAN hasNextToken();

//Finished, tested
char *nextToken();

//Finished, tested
void myRewind();

char buffer[MAX_LINE];//needs to be stored as an array since strtok modifies the input
char backup[MAX_LINE];
char *nextTok;//stores the next token in the string
char *currentTok;

void initBuffer(char *inputLine)
{
	strcpy(buffer, inputLine);
	strcpy(backup, inputLine);
	nextTok = strtok(buffer, " ");
}

BOOLEAN hasNextToken()
{
	if (nextTok) return 1;
	else return 0;
}

char *nextToken()
{
	char delim[] = " ";
	currentTok = nextTok;

	nextTok = strtok(NULL, delim);
	return currentTok;
}

void myRewind()
{
	strcpy(buffer, backup);
	nextTok = strtok(buffer, " ");
	return;
}
