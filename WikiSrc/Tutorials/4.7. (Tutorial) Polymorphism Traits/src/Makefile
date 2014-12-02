(CC) = gcc

all :
	$(CC) -Wall -c Limiter.c Linear.c DampedSinusoid.c Sinusoid.c main.c
	$(CC) Limiter.o Linear.o DampedSinusoid.o Sinusoid.o main.o -o main -lm

clean :
	rm -f Limiter.o Linear.o DampedSinusoid.o Sinusoid.o main.o main
