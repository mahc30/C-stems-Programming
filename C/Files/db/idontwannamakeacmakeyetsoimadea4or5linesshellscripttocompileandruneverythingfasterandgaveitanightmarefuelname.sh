#!/bin/bash
rm ./*.o

#Compile individual files
gcc -c stack.c -o stack.o
gcc -c student.c -o student.o
gcc -c file_db.c -o file_db.o
gcc -c constants.c -o constants.o
gcc -c main.c -o main.o

#Linking and stuff
gcc constants.o stack.o student.o file_db.o main.o -o test

#CMAKE? more like CBAD 