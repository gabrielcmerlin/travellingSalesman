all: pcv.o backtracking.o main.o
	gcc pcv.o backtracking.o main.o -o forca_bruta -std=c99 -Wall

backtracking.o: pcv.o
	gcc -c backtracking.c -o backtracking.o

pcv.o:
	gcc -c pcv.c -o pcv.o
		 
main.o: pcv.o backtracking.o
	gcc -c main.c -o main.o
		 
clean:
	rm *.o forca_bruta

run:
	./forca_bruta

test:
	./forca_bruta < 2.in

mem_check:
	valgrind -s --leak-check=full ./forca_bruta
