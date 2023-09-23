%option noyywrap c++

%{

#include <iostream>
using namespace std;
int total_line=1;     //总行号
int total_char=1;     //总单词数
int id_num=0;         //总标识符个数  
int key_num=0;        //总关键字个数
int int_num=0;        //总整数个数
int char_num=0;       //总字符个数
int str_num=0;        //总字符串个数
int sym_num=0;        //总符号个数
int op_num=0;         //总操作符个数
int real_num=0;       //总实数个数

%}

/*Definitions*/

WHITESPACE [ \t]+

NEWLINE [\r]*[\n]*

/*Keywords*/

KEYWORD "auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"

/*Integer*/
DIGIT ([0-9])
DIGIT_NUM ({DIGIT}+[Ll]?[Uu]?)
Octal_NUM (0[0-7]+[Ll]?[Uu]?)
HEX [0-9A-Fa-f]
HEX_NUM (0[xX]{HEX}+[Ll]?[Uu]?)

/*Character*/
CHARACTER ('[^\\'\n]*')

/*Real Number*/
REAL_NUM ({DIGIT}+\.{DIGIT}+[eE][-+]?{DIGIT}+)

/*String*/
STRING  (\"[^\\\"\n]*\")

/*Identifier*/
LETTER ([A-Za-z])
IDENTIFIER (_|{LETTER}(_|{LETTER}|{DIGIT})*)

/*Symbols*/

SYMBOL ";"|","|":"|"."|"["|"]"|"("|")"|"{"|"}"|"<"|">"

/*Operator*/

OPERATOR  ">"|">>"|">="|">>="|">"|">>"|">="|">>="|"<"|"<<"|"<="|"<<="|"<"|"<<"|"<="|"<<="|"!"|"!="|"="|"=="|"/"|"/="|"*"|"*="|"%"|"%="|"^"|"^="|"|"|"||"|"|="|"?"|"&"|"&&"|"&="|""|"+"|"+="|"++"|""|"-"|"-="|"--"

%%

"/*"    {
            int c;
            while((c = yyinput()) != 0){
                if(c == '\n')
                    ++total_line;
                else if(c == '*'){
                    if((c = yyinput()) == '/')
                        break;
                    else
                        unput(c);
                }
            }
            total_char+=yyleng;
        }
"\/\/"  {
            int c;
            while((c = yyinput()) != 0){
                if(c == '\n'){
                    ++total_line;
                    break;
                }
            }
            total_char+=yyleng;
        }
{KEYWORD}   {
                key_num++;
                printf("Line:%d\tToken(Keyword,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }
{IDENTIFIER}    {
                    id_num++;
                    printf("Line:%d\tToken(Identifier,%s)\n",total_line,yytext);
                    total_char+=yyleng;
                }

{Octal_NUM} {
                int_num++;
                printf("Line:%d\tToken(Integer,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }

{DIGIT_NUM} {
                int_num++;
                printf("Line:%d\tToken(Integer,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }

{HEX_NUM}   {
                int_num++;
                printf("Line:%d\tToken(Integer,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }

{REAL_NUM}  {
                real_num++;
                printf("Line:%d\tToken(Real_number,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }

{CHARACTER} {
                char_num++;
                printf("Line:%d\tToken(Character,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }
{STRING}    {
                str_num++;
                printf("Line:%d\tToken(String,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }

"#" {
        int c;
        while((c = yyinput()) != 0){
            if(c == '\n'){
                ++total_line;
                break;
            }
        }
        total_char+=yyleng;
    }
{SYMBOL}    {
                sym_num++;
                printf("Line:%d\tToken(Symbol,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }

{OPERATOR}  {
                op_num++;
                printf("Line:%d\tToken(Operator,%s)\n",total_line,yytext);
                total_char+=yyleng;
            }

{WHITESPACE}    {
                    total_char+=yyleng;
                }
{NEWLINE}   {
                total_char+=yyleng;
                total_line++;
            }

.       {
            total_char+=yyleng;
            printf("Line:%d\tToken(ERROR,%s)\n",total_line,yytext);
        }

%%

int main(int argc, char* argv[]){
    FlexLexer* lexer = new yyFlexLexer;
    lexer->yylex();
    cout<<endl;
    cout<<"Total line:"<<total_line<<endl;
    cout<<"Total Text Character:"<<total_char<<endl;
    cout<<"Total Identifier:"<<id_num<<endl;
    cout<<"Total Keyword:"<<key_num<<endl;
    cout<<"Total Integer:"<<int_num<<endl;
    cout<<"Total Real Number:"<<real_num<<endl;
    cout<<"Total Character:"<<char_num<<endl;
    cout<<"Total String:"<<str_num<<endl;
    cout<<"Total Operator:"<<op_num<<endl;
    cout<<"Total Symbol:"<<sym_num<<endl;
    return 0;
}