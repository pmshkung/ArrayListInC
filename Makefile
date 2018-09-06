.PHONY: all main clean
main: main.o arraylist.o
	gcc main.o arraylist.o -o main
main.o: main.c utils/ArrayList.h
	gcc -c main.c -o main.o
arraylist.o: utils/ArrayList.c utils/ArrayList.h
	gcc -c utils/ArrayList.c -o arraylist.o
clean:
	rm -rf *.o *.exe
