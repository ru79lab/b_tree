CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
EXECUTABLE = test
BUILD_DIR = build


compile = $(CC) $(CFLAGS) -c $< -o $@

all: build execute

build: prep $(BUILD_DIR)/test

cleanBuild: clean build execute

$(BUILD_DIR)/test: $(BUILD_DIR)/test.o $(BUILD_DIR)/b_tree.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/test.o $(BUILD_DIR)/b_tree.o $(BUILD_DIR)/insertion_algorithms.o $(BUILD_DIR)/array.o -o $(BUILD_DIR)/test

$(BUILD_DIR)/test.o: test.c $(BUILD_DIR)/b_tree.o b_tree.h common_def.h
	$(compile)

$(BUILD_DIR)/b_tree.o: b_tree.c b_tree.h insertion_algorithms.h array.h common_def.h $(BUILD_DIR)/array.o $(BUILD_DIR)/insertion_algorithms.o
	$(compile)

$(BUILD_DIR)/insertion_algorithms.o: insertion_algorithms.c insertion_algorithms.h array.h common_def.h $(BUILD_DIR)/array.o
	$(compile)

$(BUILD_DIR)/array.o: array.c array.h common_def.h
	$(compile)

prep: 
	mkdir build

execute: 
	./$(BUILD_DIR)/$(EXECUTABLE).exe

clean: 
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/$(EXECUTABLE).exe
	rmdir $(BUILD_DIR)