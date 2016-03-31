/* Header file for syntax.c */
extern int lineCount;

int isValidCommand(char *token);

/* This function returns 1 if the token is one of the 
   valid robot commands, otherwise it returns 0.
*/

int isValidExpression(char *expression);
/* This function returns 1 if the expression agrees 
   with one of the legal robot expressions, otherwise
   it returns 0.
*/
