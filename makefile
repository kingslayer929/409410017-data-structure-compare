all: main.c ./lib/BST.h ./lib/hash.h ./lib/list.h
	gcc main.c -o main.exe