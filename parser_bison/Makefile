# Define the compiler and its flags
CC = gcc
CFLAGS = -o parser
YACC = bison
YFLAGS = -vdty
LEX = flex

# Define the source files
YACC_SRC = grammar.y
LEX_SRC = lex.l
DEMO_SRC = demo.txt

# Define the object files
YACC_OUT = y.tab.c
LEX_OUT = lex.yy.c

# Define the target and its dependencies
parser: $(YACC_OUT) $(LEX_OUT)
	$(CC) $(CFLAGS) $(YACC_OUT) $(LEX_OUT)

# Define how to create the yacc output
$(YACC_OUT): $(YACC_SRC)
	$(YACC) $(YFLAGS) $(YACC_SRC)

# Define how to create the lex output
$(LEX_OUT): $(LEX_SRC)
	$(LEX) $(LEX_SRC)

# Define a target to run the parser with the demo input
run: parser
	./parser < $(DEMO_SRC)

# Clean up the generated files
clean:
	rm -f $(YACC_OUT) $(LEX_OUT) parser y.output

# Ensure that lex and yacc are rebuilt when lex.l and grammar.y change
$(YACC_OUT): $(YACC_SRC)
$(LEX_OUT): $(LEX_SRC)

.PHONY: run clean
