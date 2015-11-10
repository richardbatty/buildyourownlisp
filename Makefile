CC=cc
CFLAGS=-std=c99 -Wall
LFLAGS = -ledit -lm
LIB = src/interpreter.c src/eval.c src/parser.c lib/mpc/mpc.c
MAIN = src/main.c
OBJ = parsing.o
TEST = tests/acceptance.c
TEST_OBJ = tests.o

all: build run

test: create_test_file build_test run_test

debug: build_debug run_debug

run_debug:
	./a.out

build_debug:
	$(CC) -g $(CFLAGS) $(DEPS) $(LFLAGS)

build:
	$(CC) $(CFLAGS) $(MAIN) $(LIB) $(LFLAGS) -o $(OBJ)

run:
	./$(OBJ)

create_test_file:
	checkmk tests/acceptance.check > tests/acceptance.c

build_test:
	$(CC) $(CFLAGS) $(TEST) $(LIB) -lcheck $(LFLAGS) -o $(TEST_OBJ)

run_test:
	./$(TEST_OBJ)
