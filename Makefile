a.out:main.o pfunction.o
	gcc -g main.c pfunction.c
main.o:main.c header.h
	gcc -c -g main.c
old_function.o:pfunction.c
	gcc -c -g pfunction.c
