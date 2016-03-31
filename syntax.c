#include<stdio.h>
#include<string.h>
#include "parse.h"
#define MAX_LINE 500
#define NUM_COMMANDS 8
#define NUM_EXPRESSIONS 3

//Corrected, not tested
int isValidCommand(char *token);

//Finished, not tested; need helper functions
int isValidExpression(char *expression);

//Finished, not tested
int isValidRepeatExp(char *expression);

//Finished, not tested
int isValidWhileExp(char *expression);

//Finished, not tested
int isValidSayExp(char *expression);

//Finished, not tested
int isValidCommaCom(char *expression);

//Finished, not tested
void lower(char *string);

/************ global variables **************/

int lineCount;
int isExp;

//commands and expressions are kept in arrays to prevent overuse of if statements
char *commands[] = {
"takeastep",
"left",
"right",
"pickup",
"drop",
"detectmarker",
"turnon",
"turnoff"
}; 

//Note that only the first word is used since we will need to compare it with a single token
char *expressions[] = {
"repeat",
"while",
"say"
};

/**********************************************/

int isValidCommand(char *token)
{
	int i;
	if (isExp) return 0;
	lower(token); //we want our string to be all in lowercase

	for (i=0; i<NUM_COMMANDS; i++) {
		if (strcmp(token, commands[i]) == 0) return 1; //note that strcmp return 0 for equality
	//printf("Command %d: %s\n", i, commands[i]);
	//printf("Token : %s\n", token);
	}

//Where is my mistake??

	printf("Error at line %d:\n", lineCount);
	printf("\tUnrecognized command\n");
	return 0;
}

/**
 * Edit: we need to FIRST check the first element
 * to then decide in which kind of construct we are in
 * and then procede accordingly.
 * So we use strtok to get our blocks;
 * then call each specialized method for each case.
 */
int isValidExpression(char *expression)
{
	char token[MAX_LINE];
	lower(expression); //assuming expressions are not case sensitive either
	initBuffer(expression);

	strcpy(token, nextToken());
	isExp = 1;
	
	if (strcmp(token, expressions[0]) == 0) return isValidRepeatExp(expression);
	if (strcmp(token, expressions[1]) == 0) return isValidWhileExp(expression);
	if (strcmp(token, expressions[2]) == 0) return isValidSayExp(expression);

	isExp = 0;

	return 0;
}

int isValidRepeatExp(char *expression)
{
	char token[MAX_LINE];
	char *ptr;
	ptr = &token[0];
	

	strcpy(token, nextToken());
	while (*ptr != 0) {
		//checking if second token is a valid number
		if (!isdigit(*ptr)) {
			printf("Error at line %d:\n", lineCount);
			printf("\t%s\n", backup);
			printf("\tExpected an integer number\n");
			return 0;
		}
		ptr++;
	}
	//if there is nothing
	if (ptr == &token[0]) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tExpected an integer number\n");
		return 0; 
	}
	
	strcpy(token, nextToken());
	//checking for keyword TIMES
	if (strcmp(token, "times") == 0) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tExpected token \"TIMES\"\n");
		return 0; 
	}

	//checking the comma sep commands 
	//as well as the END keyword
	strcpy(token, nextToken());
	if (!isValidCommaCom(token)) return 0; 

	return !hasNextToken(); //expression should end after END keyword
}

int isValidWhileExp(char *expression)
{
	char token[MAX_LINE];
	
	strcpy(token, nextToken());
	if (strcmp(token, "not") == 0) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tExpected token \"NOT\"\n");
		return 0;
	}

	strcpy(token, nextToken());
	if (strcmp(token, "detectmarker") == 0) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tExpected command \"DETECTMARKER\"\n");
		return 0;
	}

	strcpy(token, nextToken());
	if (strcmp(token, "do") == 0) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tExpected token \"TIMES\"\n");
		return 0;
	}

	strcpy(token, nextToken());
	if (!isValidCommaCom(token)) return 0;

	return !hasNextToken();

}

/**
 * The idea is the following: starting from the first ",
 * parse the string until you find another " or reach the end.
 * If we reached the end of the string, there is an error. Else
 * Have a pointer point at the next character after this "
 * If strtok(*ptr, " ") != NULL, thene there are some non space
 * characters after the second quote --> error.
 */
int isValidSayExp(char *expression)
{
	char *ptr;
	ptr = nextToken(); //copy the start point of the first token

	myRewind(); 

	if (*ptr != '\"') {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tExpected opening \"\n");
		return 0;
	}
	ptr++;

	while (*ptr != '\"' && ptr != 0) {
		ptr++;
	}

	if (*ptr == 0) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tExpected closing \"\n");
		return 0;
	}

	if (strtok(ptr, " ") != NULL) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tUnexpected tokens after closing \"\n");
		return 0;
	}

	return 1;

}

int isValidCommaCom(char *token) 
{
	char strg[MAX_LINE]; //char array where the command will be stored
	char *ptr, *start; 
	int i = 0; //i is used as a counter of the # of letters before the first comma

	while (token != NULL && (strcmp(token, "end") != 0)) { //recall strcmp return 0 if "true"
		i=0;
		start = &token[0];
		ptr = &token[0];
		while (*ptr != '0') {
			if (!(*ptr == ',' || *ptr == 0)) { //not comma or NULL -> continue parsing
				i++;
				ptr++;
			}	
			else { 
				//char is a comma or end of string: check if word is a valid command
				//                                  reinitialize i
				//                                  break or continue parsing
				memcpy(strg, start, i);
				if (!isValidCommand(strg)) return 0;
				if (*ptr == 0) break; //breaking from comma sep words loop
	//What if "LEFT RIGHT," ? *******************************
				memset(strg, 0, MAX_LINE);
				ptr++;
				start = ptr;
				i=0;
			}
		}//End of comma separated words loop

		strcpy(token, nextToken());

	} //End of token loop

	if (strcmp(token, "end") == 0) {
		printf("Error at line %d:\n", lineCount);
		printf("\t%s\n", backup);
		printf("\tUnexpected tokens after \"END\"");
		return 0;
	}

	return 1;
}

//Helper function that changes to lowercase
void lower(char *string) 
{
	char *ptr;
	ptr = string;

	while (*ptr != 0) {
		*ptr = tolower(*ptr);
		ptr++; //DO NOT FORGET THIS LINE FFS
	}
}
