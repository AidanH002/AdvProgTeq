# Use g++ compiler using C++ 17 standard
CC = g++ -std=c++17

# Compilation flags
FLAGS = -Wall -pedantic

# Target executable
TARGET = problem1

all: $(TARGET)

$(TARGET): problem1.cpp
	$(CC) $(FLAGS) -o $(TARGET) problem1.cpp

clean:
	rm -f $(TARGET)

.PHONY: all clean
