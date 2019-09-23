CC = gcc
cflags = -g -Wall

source = stack.c stack_bracket.c
target = run

all:
	$(CC) $(source) $(cflags) -o $(target)

clean:
	del $(target).exe

