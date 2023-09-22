/*
 * @Author: Feng Wenbo
 * @Student Number: 2021210945
 * @Date: 2023-09-21 13:38:18
 * @LastEditTime: 2023-09-22 20:22:16
 * @FilePath: \lexer\main.cpp
 * @Description: 
 */

#include "lexer.h"
#include <iostream>

int main(int argc, char* argv[]){
    if(argc<2)  cout<<"Please enter the file name that needs to be lexically analyzed!"<<endl;
    else{
        for(int i=1;i<argc;i++){
            Lexer lexer(argv[i]);
            while(true){
                string str=lexer.get_next_token().toString();
                if(str.find("identifier")!=string::npos)    lexer.id_num++;
                else if(str.find("keyword")!=string::npos)  lexer.key_num++;
                else if(str.find("integer")!=string::npos)   lexer.int_num++;
                else if(str.find("real_number")!=string::npos)  lexer.real_num++;
                else if(str.find("character")!=string::npos)    lexer.char_num++;
                else if(str.find("string")!=string::npos)   lexer.str_num++;
                else if(str.find("operator")!=string::npos) lexer.op_num++;
                else if(str.find("symbol")!=string::npos)   lexer.sym_num++;
                
                if(str=="Token(EOF,EOF)")   break;
                cout<<str<<endl;
            }
            cout<<endl;
            cout<<"File Name:"<<argv[i]<<endl;
            cout<<"Total line:"<<lexer.total_line<<endl;
            cout<<"Total Text Character:"<<lexer.total_char<<endl;
            cout<<"Total Identifier:"<<lexer.id_num<<endl;
            cout<<"Total Keyword:"<<lexer.key_num<<endl;
            cout<<"Total Integer:"<<lexer.int_num<<endl;
            cout<<"Total Real Number:"<<lexer.real_num<<endl;
            cout<<"Total Character:"<<lexer.char_num<<endl;
            cout<<"Total String:"<<lexer.str_num<<endl;
            cout<<"Total Operator:"<<lexer.op_num<<endl;
            cout<<"Total Symbol:"<<lexer.sym_num<<endl;
        }
    }
    return 0;
}