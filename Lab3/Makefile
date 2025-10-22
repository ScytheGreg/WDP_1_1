ocen.e: zbior_ary.o ocen.o
	gcc zbior_ary.o ocen.o -o ocen.e

ocen.o: ocen.c zbior_ary.h
	gcc -c @opcje ocen.c -o ocen.o

zbior_ary.o: zbior_ary.c zbior_ary.h
	gcc -c @opcje zbior_ary.c -o zbior_ary.o 
