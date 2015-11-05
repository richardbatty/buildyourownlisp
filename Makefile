CC=cc
CFLAGS=-std=c99 -Wall
LFLAGS = -ledit -o
DEPS = parsing.c
OBJ = parsing.o

all: build run

build:
	$(CC) $(CFLAGS) $(DEPS) $(LFLAGS) $(OBJ)

run:
	./$(OBJ)
