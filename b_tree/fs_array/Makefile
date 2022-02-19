CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
BUILD_DIR = build

OBJECTS = array.o

compile = $(CC) $(CFLAGS) -c $< -o $@

all: build

test: build unit_test execute

build: prep $(BUILD_DIR)/array.o

cleanBuild: clean build execute

unit_test: $(BUILD_DIR)/$(OBJECTS) array.h ../common_def.h
	$(CC) $(CFLAGS) unit_test.c $(BUILD_DIR)/array.o -o test -lcunit

$(BUILD_DIR)/$(OBJECTS): array.c array.h ../common_def.h
	$(compile)

execute: 
	./test.exe

prep: 
	mkdir $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR)/*.o 
	rmdir $(BUILD_DIR)