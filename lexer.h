/*
 * @Author: Feng Wenbo
 * @Student Number: 2021210945
 * @Date: 2023-09-21 00:44:06
 * @LastEditTime: 2023-09-22 22:31:51
 * @FilePath: \lexer\lexer.h
 * @Description: 
 */

#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <utility>
#include <fstream>
using namespace std;

/*c语言中所有tokens以及分析所需tokens*/
enum TOKEN{

    /*
        main: method name.
        a: variable name.
    */
    IDENTIFIER,

    
    /*KEYWORDS*/
    AUTO,DOUBLE,INT,STRUCT,BREAK,ELSE,LONG,SWITCH,
    CASE,ENUM,REGISTER,TYPEDEF,CHAR,EXTERN,RETURN,UNION,
    CONST,FLOAT,SHORT,UNSIGNED,CONTINUE,FOR,SIGNED,
    VOID,DEFAULT,GOTO,SIZEOF,VOLATILE,DO,IF,STATIC,WHILE,

    /*Constants*/
    INTEGER,    //123,45,...
    REALNUM,  //15.3,16.9,1e-9,...
    CHAR_CONS,  //'A','b',...

    /*
        char string[20] = "strings";
        char string[] = "strings";
    */
    STRING,
    EndOfFile,
    ERROR,

    /*Special Symbols*/
    /*包括以下符号：[] () {} , ; ->*/
    SYMBOL,

    /*Operators*/
    /* 算术运算符 + - * / % ++ -- */
    /* 关系运算符 > < == >= <= != */
    /* 逻辑运算符 && || ! */
    /* 赋值运算符 = += -= *= /= %= &= |= ^= >>= <<= */
    /* 条件运算符 ? : */
    /* 指针运算符 * &  */
    /* 位运算符  & | ~ ^ << >> */
    OPERATOR

};

class Token{
    private:
        TOKEN type;
        string data;    //无论是identifier，keyword，number，symbol都可以采用字符串形式进行存储
    public:

        Token(TOKEN type,string data);

        /**
         * @description: String representation of the class instance.
                         Examples:
                            Token(INTEGER, 3)
                            Token('+', +)
                            Token('*', *)
         * @return {Token的文字表示}
         */
        string toString();
};

class Lexer
{
    private:
        int position;       //向前指针
        string token;       //存储当前正在识别的字符串
        int lexemebegin;    //指向buffer中当前单词的开始位置
        int isKey;          //表示识别出的单词是关键字,其值为关键字的记号
        char curr_char;     //存放当前读入的字符。
        string text;        //存放需要分析的文本

        /*methods*/

        //每调用一次，把position指向的text中的字符放入变量curr_char中
        void get_char(); 
        //检查C中的字符是否为空格，若是，则反复调用get_char()，直到C中进入一个非空字符为止。   
        void get_nbc(); 
        //返回position后面的i个字符,但不更改postion的位置
        char peek(int i);     
        //根据token中的单词查关键字表，若token中的单词是关键字，则返回值该关键字的记号，否则，返回值“-1”。
        int reserve(string str);  
        //对发现的错误进行相应的处理。
        Token error(string err); 

        //跳过源程序中的注释
        void eat_comments();
        //返回标识符
        Token get_id();
        //返回整数和实数
        Token get_number();
        //返回字符常量
        Token get_charachter();
        //返回字符数组常量
        Token get_string();
    public:

        int total_line=0;     //总行号
        int total_char=0;     //总单词数
        int id_num=0;         //总标识符个数  
        int key_num=0;        //总关键字个数
        int int_num=0;        //总整数个数
        int char_num=0;       //总字符个数
        int str_num=0;        //总字符串个数
        int sym_num=0;        //总符号个数
        int op_num=0;         //总操作符个数
        int real_num=0;       //总实数个数

        Lexer(string filename); 
        Token get_next_token();  
};

#endif  //LEXER_H