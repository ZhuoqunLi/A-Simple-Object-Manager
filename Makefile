all: main.c	regions.c
	clang -Wall -o main main.c regions.c
 