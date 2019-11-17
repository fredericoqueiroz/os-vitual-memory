SHELL:=/bin/bash -O globstar

BIN_NAME=tp3virtual
BIN_DIR=.
OBJ_DIR=./src/obj
SRC_DIR=./src
SRC=$(wildcard $(SRC_DIR)/**/*.c)
CC=gcc

CFLAGS = -O3 -Wall -Wextra -g

.PHONY: all

all: setup main

main: main.o
	$(CC) $(SRC) $(OBJ_DIR)/main.o -o $(BIN_DIR)/$(BIN_NAME) $(CFLAGS)

main.o:
	$(CC) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(CFLAGS)

setup:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

run:
	$(BIN_DIR)/$(BIN_NAME)

clean:
	rm -f $(OBJ_DIR)/* $(BIN_DIR)/$(BIN_NAME)
