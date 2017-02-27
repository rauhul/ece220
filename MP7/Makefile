CC=gcc
CFLAGS=-g -std=c99 -Wall #-Werror

all: mp7 mp7_gold test

mp7: main.o game.o getch_fun.o
	$(CC) $(CFLAGS) main.o game.o getch_fun.o -o mp7

mp7_gold: main.o getch_fun.o
	$(CC) $(CFLAGS) main.o test_src/game_gold.o getch_fun.o -o mp7_gold

test: test_src/test.o  game.o getch_fun.o
	$(CC) $(CFLAGS) test_src/test.o test_src/game_test.o game.o getch_fun.o -o mp7_test

test_src/test.o: test_src/test.c
	$(CC) $(CFLAGS) -c test_src/test.c -o test_src/test.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

getch_fun.o: getch_fun.c
	$(CC) $(CFLAGS) -c getch_fun.c

clean:
	rm -f getch_fun.o test_src/test.o game.o main.o mp7 mp7_gold
