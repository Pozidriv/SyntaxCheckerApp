#include<stdio.h>
#include "syntax.h"
#define MAX_LINE 100

/* This is the file that will be executed.
   The procedure is the following: 
	Take the input files as parameters of main()
	For each line do 
		if syntaxIsValid continue
		else displayError
		continue
	exit
 
   The input is a text file, ie a single line of text
   containing \n characters.
*/

//Finished, not tested
int main(int argc, char *argv[])
{
	char line[MAX_LINE+1];
	FILE *ptr;

	//Checking validity of input
	if (argc !=2) {
		printf("The arguments you have passed are invalid.\n");
		printf("Please use this program with the following syntax:\n");
		printf("./a.out FILE_NAME\n");
		return 1;
	}

	ptr = fopen(argv[1], "rt");

	lineCount=1;
	while (!feof(ptr)) {
		fgets(line, MAX_LINE, ptr); //fgets stores a single line into line.
		
		if (line != NULL && !isValidExpression(line) && !isValidCommand(line)) {
		//IMPORTANT: isValidExpression MUST be checked BEFORE isValidCommand in order to have a correct error message
		}

		lineCount++;
	}
	fclose(ptr); //would ptr = NULL work the same?
	
	return 0;
}
