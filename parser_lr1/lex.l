%option noyywrap c++
%{
#include "LR1.h"
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
<<EOF>> {return EndOfFile;}
"\n" {return EndOfFile;}
.   {return ERROR;}

%%
