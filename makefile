all: bin/main

bin/main: src/*.c include/*.h
	gcc -g -Wall -o bin/main -I include src/*.c
