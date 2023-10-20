%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char*);
#define YYSTYPE char *
%}

%token number add sub mul divd leftparen rightparen 

%left add sub
%left mul divd

%%

E   : E add T  {printf("E→E+T\n");}
    | E sub T  {printf("E→E-T\n");}
    | T        {printf("E→T\n");}

T   : T mul F  {printf("T→T*F\n");}
    | T divd F {printf("T→T/F\n");}
    | F        {printf("T→F\n");}

F   : leftparen E rightparen {printf("F→(E)\n");}
    | number    {printf("F→num\n");}
%%

int main() {
    return yyparse();
}
