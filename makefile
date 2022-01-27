#/*== Stephanie Briere Americo ==*/

CFLAGS = -Wall -lm -O3

all: main

clean:
	-rm *.o

purge: clean
	-rm main

# ----

main: main.o collection.o
	gcc -o main *.o $(CFLAGS) 

# ----
main.o: main.c
	gcc -c main.c $(CFLAGS)

collection.o: collection.h collection.c
	gcc -c collection.c $(CFLAGS)
