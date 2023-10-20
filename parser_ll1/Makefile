CC = g++
CFLAGS = 
SRC_FILES_LL1 = parser.cpp LL1.cpp lexer.cpp
TARGET = parser
LEXER_SOURCE = lexer.cpp

all: $(TARGET) 

$(TARGET): $(SRC_FILES_LL1)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES_LL1)

run: $(TARGET)
	./$(TARGET) < demo.txt

$(LEXER_SOURCE): lex.l
	flex -o $(LEXER_SOURCE) lex.l

.PHONY: lexer
lexer: $(LEXER_SOURCE)

clean:
	rm -f $(TARGET)
