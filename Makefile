CC=cc
CFLAGS=-std=c99 -Wall
LFLAGS = -ledit -lm -o
DEPS = parsing.c lib/mpc/mpc.c
OBJ = parsing.o
TEST_DEPS = tests/test.c
TEST_OBJ = tests.o

all: build run

test: create_test_file build_test run_test

build:
	$(CC) $(CFLAGS) $(DEPS) $(LFLAGS) $(OBJ)

run:
	./$(OBJ)

create_test_file:
	checkmk tests/test.check > tests/test.c

build_test:
	$(CC) $(CFLAGS) $(TEST_DEPS) -lcheck $(LFLAGS) $(TEST_OBJ)

run_test:
	./$(TEST_OBJ)
