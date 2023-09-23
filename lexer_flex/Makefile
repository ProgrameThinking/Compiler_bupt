# Compiler and flags
CC = g++
CFLAGS = -Wall

# Target executable
TARGET = lexer

# Source files
LEX_SRC = lex.yy.cc

# Default target
all: $(TARGET)

# Build the lexer executable
$(TARGET): $(LEX_SRC)
	$(CC) $(CFLAGS) $(LEX_SRC) -o $(TARGET)

# Generate lex.yy.cc using flex
lex.yy.cc: lexer.l
	flex lexer.l

# Run the lexer with input file
run: $(TARGET)
	./$(TARGET) < samples1/ilegal_input.c > output

# Clean up generated files
clean:
	rm -f $(LEX_SRC) $(TARGET)

.PHONY: all run clean
