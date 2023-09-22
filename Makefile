CXX = g++
CXXFLAGS = -std=c++20
DEBUGFLAGS= -Wall -Wextra -std=c++20

SRC_FILES = main.cpp lexer.cpp
TARGET = lexer

$(TARGET): $(SRC_FILES)
	chcp 65001
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET)
	$(TARGET) test1.c

debug: $(SRC_FILES)
	$(CXX) $(DEBUGFLAGS) $(SRC_FILES) -o $(TARGET)

clean:
	rm $(TARGET).exe

.PHONY: clean