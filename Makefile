CC = g++
FLAGS = -Wall -Werror

BUILD_DIR = build
TARGET = $(BUILD_DIR)/main
BIN_DIR := bin

LIB_SRC = $(wildcard src/exp_calculator/*.cpp)
LIB_OBJ := $(patsubst src/exp_calculator/%.cpp, $(BIN_DIR)/lib/%.o, $(LIB_SRC))

run: prepare $(TARGET)
	./$(TARGET)

prepare: 
	mkdir -p $(BUILD_DIR0) $(BIN_DIR)/lib

$(BIN_DIR)/lib/%.o: src/exp_calculator/%.cpp
	$(CC) $(FLAGS) -c $< -o $@ -Isrc/exp_calculator

$(TARGET): $(LIB_OBJ) src/main.cpp
	$(CC) $(FLAGS) $^ -o $(TARGET) -Isrc

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR) $(TARGET)

.PHONY: run prepare clean
