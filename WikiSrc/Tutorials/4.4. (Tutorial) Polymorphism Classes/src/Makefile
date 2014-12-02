(CC) = gcc

all :
	$(CC) -Wall -Os -c SignalLimiter.c LinearLimiter.c SinLimiter.c main.c
	$(CC) SignalLimiter.o SinLimiter.o LinearLimiter.o main.o -o main -lm
clean :
	rm -f SignalLimiter.o LinearLimiter.o SinLimiter.o main.o main
