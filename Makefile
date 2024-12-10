# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Targets
all: part1 part2

part1: part1.c
	$(CC) $(CFLAGS) -o part1 part1.c

part2: part2.c phypages.c pagetable.c
	$(CC) $(CFLAGS) -o part2 part2.c phypages.c pagetable.c

clean:
	rm -f part1 part2 *.o

