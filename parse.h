/* Header file for parse.c */
typedef int BOOLEAN;

char backup[100];

void initBuffer(char *inputLine);
/* This function initializes the private parse.c buffer
   with the string passed in the parameter inputLine.
*/

BOOLEAN hasNextToken();
/* This function returns a 1 if there are still more tokens 
   in the string, otherwise it returns 0.
   Tokens are space separated words.
*/

char *nextToken();
/* This function removes the first token from the buffer. 
   The removed token is returned to the caller.
   If the buffer is empty then this function returns NULL.
*/

void myRewind();
/* This function reinitializes the private buffer with the 
   string originally provided by the initBuffer() function 
   call. This will effectively restart the token extraction 
   process from the beginning.
*/
