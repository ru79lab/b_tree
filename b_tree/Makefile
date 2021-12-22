CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
EXECUTABLE = test
BUILD_DIR = build


compile = $(CC) $(CFLAGS) -c $< -o $@

all: build execute

build: prep $(BUILD_DIR)/test

$(BUILD_DIR)/test: $(BUILD_DIR)/test.o $(BUILD_DIR)/b_tree.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/test.o $(BUILD_DIR)/b_tree.o -o $(BUILD_DIR)/test

$(BUILD_DIR)/test.o: test.c $(BUILD_DIR)/b_tree.o b_tree.h
	$(compile)

$(BUILD_DIR)/b_tree.o: b_tree.c b_tree.h
	$(compile)

prep: 
	mkdir build

execute: 
	./$(BUILD_DIR)/$(EXECUTABLE).exe

clean: 
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/$(EXECUTABLE).exe
	rmdir $(BUILD_DIR)