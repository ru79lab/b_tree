CC = gcc
CFLAGS = -g -Wall -Wextra -Werror $(INCLUDES)
BUILD_DIR = build
SOURCE_DIR = src
TEST_DIR = test
ROOT_DIR =..

INCLUDES = -I$(ROOT_DIR)/ -I$(SOURCE_DIR)/

OBJS = array.o 

TEST_OBJS = unit_test.o

OBJECTS= $(foreach obj, $(OBJS), $(addprefix $(SOURCE_DIR)/$(BUILD_DIR)/, $(obj)))
TEST_OBJECTS = $(foreach obj, $(TEST_OBJS), $(addprefix $(TEST_DIR)/$(BUILD_DIR)/, $(obj)))


compile = $(CC) $(CFLAGS) -c $< -o $@


all: src_build

test: src_build test_build unit_test execute_test

src_build: prep_src_build $(OBJECTS)

test_build: prep_test_build $(TEST_OBJECTS)

cleanBuild: clean build execute

unit_test: $(SOURCE_DIR)/array.h ../common_def.h
	$(CC) $(CFLAGS) $(TEST_OBJECTS) $(OBJECTS) -o test -lcunit 

$(SOURCE_DIR)/$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c 
	$(compile)

$(TEST_DIR)/$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(compile)

execute_test: 
	./test.exe

prep_src_build: 
	mkdir $(SOURCE_DIR)/$(BUILD_DIR)

prep_test_build: 
	mkdir $(TEST_DIR)/$(BUILD_DIR)

clean: cleanSrc cleanTest 
	rm *.exe

cleanSrc: 
	rm -rf $(SOURCE_DIR)/$(BUILD_DIR)/*.o 
	rmdir $(SOURCE_DIR)/$(BUILD_DIR)

cleanTest: 
	rm -rf $(TEST_DIR)/$(BUILD_DIR)/*.o 
	rmdir $(TEST_DIR)/$(BUILD_DIR)