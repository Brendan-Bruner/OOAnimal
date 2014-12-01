(CC) = gcc

all :
	$(CC) -Wall -Os -c SignalLimiter.c SinLimiter.c main.c
	$(CC) SignalLimiter.o SinLimiter.o main.o -o main -lm
clean :
	rm SignalLimiter.o SinLimiter.o main.o main
