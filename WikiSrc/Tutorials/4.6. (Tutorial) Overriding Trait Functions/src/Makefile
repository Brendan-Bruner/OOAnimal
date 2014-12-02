(CC) = gcc

all :
	$(CC) -Wall -c DampedSinusoid.c Sinusoid.c main.c
	$(CC) DampedSinusoid.o Sinusoid.o main.o -o main -lm

clean :
	rm -f DampedSinusoid.o Sinusoid.o main.o main
