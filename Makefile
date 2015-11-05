CC=cc
CFLAGS=-std=c99 -Wall
LFLAGS = -ledit -lm -o
DEPS = parsing.c lib/mpc/mpc.c
OBJ = parsing.o

all: build run

build:
	$(CC) $(CFLAGS) $(DEPS) $(LFLAGS) $(OBJ)

run:
	./$(OBJ)
