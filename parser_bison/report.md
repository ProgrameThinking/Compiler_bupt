<font face="Consolas">

# 语法分析程序的设计与实现（YACC实现）

## 实验要求

利用YACC自动生成语法分析程序，实现对算术表达式的语法分析。要求所分析算数表达式由如下的文法产生。

E→E+T | E–T | T

T→T*F | T/F | F

F→(E) | num

在对输入的算术表达式进行分析的过程中，依次输出所采用的产生式。

## 程序设计说明

[lex.l](lex.l)
```
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
```
定义了dight用于匹配单个数字字符，并且num用于匹配一个或多个数字字符。此外，我们定义了ws来匹配空白字符，包括制表符、回车和空格。而后定义了词法规则，每个规则匹配一个特定的输入模式，并在成功匹配时返回相应的标记。例如，{ws}匹配空白字符，但不返回任何标记，因为它们通常被忽略。{num}匹配一个或多个数字字符，并返回number标记。类似地，"+"、"-"、"*" 和 "/" 分别匹配加法、减法、乘法和除法运算符，并返回相应的标记。括号也被匹配并返回相应的标记。最后，通用规则. 匹配任何未被先前规则匹配的字符，并调用unrecognized_char函数来报告未识别字符的错误。

[grammar.y](grammar.y)
```
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
    yyparse();
    return 0;
}

```

定义了语法规则中可能出现的终结符标记（tokens）。这些标记包括数字（number）、加法（add）、减法（sub）、乘法（mul）、除法（divd）、左括号（leftparen）和右括号（rightparen）。指定了加法和减法的结合性为左结合，以及乘法和除法的结合性也为左结合。这将影响语法分析过程中运算符的结合规则。定义了语法规则，语法规则使用BNF（巴科斯范式）形式表示。具体来说，它定义了三个非终结符：E、T和F。每个规则的右侧定义了如何从其他非终结符或终结符构建树节点，同时输出相应的产生式。这些产生式的右侧包括打印语句，用于输出所匹配的产生式。

## 程序运行结果

[输入](demo.txt) : 1*(1+(1*(2-(4/3+(5-9*3/2)))))/5*3-2+5

输出为:
```
F→num
T→F
F→num
T→F
E→T
F→num
T→F
F→num
T→F
E→T
F→num
T→F
F→num
T→T/F
E→T
F→num
T→F
E→T
F→num
T→F
F→num
T→T*F
F→num
T→T/F
E→E-T
F→(E)
T→F
E→E+T
F→(E)
T→F
E→E-T
F→(E)
T→T*F
E→T
F→(E)
T→F
E→E+T
F→(E)
T→T*F
F→num
T→T/F
F→num
T→T*F
E→T
F→num
T→F
E→E-T
F→num
T→F
E→E+T
```
倒叙来看可以建立一颗正确的AST

</font>