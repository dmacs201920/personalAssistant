#
#     By :AVA
#     On :14 03 2020
#
a.out:Personal_Assistant.o functions.o
	gcc Personal_Assistant.o functions.o -lncurses
Personal_Assistant.o:Personal_Assistant.c header.h
	gcc -c Personal_Assistant.c
functions.o:functions.c header.h
	gcc -c functions.c

