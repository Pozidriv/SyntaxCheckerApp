SyntaxCheckerApp : main.o parse.o syntax.o
	gcc -o SyntaxCheckerApp main.o parse.o syntax.o

debug : main.o parse.o syntax.o
	gcc -g -Wall -o debug main.c parse.o syntax.o

main.o : main.c parse.h syntax.h
	gcc -c main.c

parse.o : parse.c parse.h
	gcc -c parse.c

syntax.o : syntax.c syntax.h
	gcc -c syntax.c

clean :
	rm -f SyntaxCheckerApp main.o parse.o syntax.o
