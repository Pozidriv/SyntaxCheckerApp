# SyntaxCheckerApp
This is a small program that I have developped for a class.
It takes as input a file written in a language called "robot language", 
and checks whether the syntax of the given file is correct.

The language consists of commands and expressions.
There can be only one command or expression per line.
The commands are not case sensitive.
List of legal commands is: 
  TAKEASTEP
  LEFT
  RIGHT
  PICKUP
  DROP
  DETECTMARKER
  TURNON
  TURNOFF
The legal expressions are:
  REPEAT n TIMES comma-separated-list-of-commands END
  WHILE NOT c DO comma-separated-list-of-commands END
    note: c is any legal condition. The only legal condition is DETECTMARKER
  SAY "message"
  
In addition, we had a few functions to build no matter what. 
The instructions can be found here: http://pozidrivtotheskies.site90.net/Courses&stuff/COMP206/a3.pdf (question 1)
