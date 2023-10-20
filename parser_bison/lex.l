%{
#define YYSTYPE char *
#include "y.tab.h"
int cur_line = 1;
void yyerror(const char *msg);
void unrecognized_char(char c);
%}
/*Definitions*/
dight [0-9]
num ({dight}+)
ws [\t\r\a ]

%%
{ws}
{num}   {return number;}
"+"     {return add;}
"-"     {return sub;}
"*"     {return mul;}
"/"     {return divd;}
"("     {return leftparen;}
")"     {return rightparen;}
.   {unrecognized_char(yytext[0]);}

%%

int yywrap(void) { 
    return 1;
}

void unrecognized_char(char c) {
    char buf[32] = "Unrecognized character: ?";
    buf[24] = c;
    yyerror(buf);
}

void yyerror(const char *msg) {
    printf("Error at line %d:\n\t%s\n", cur_line, msg);
    exit(1);
}