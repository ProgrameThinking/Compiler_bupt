#include "lexer.h"
#include <iostream>
#include <ctype.h>
#include <string.h>

string token2string(TOKEN type){
    string ret="";
    switch (type){
        case IDENTIFIER: 
            ret="identifier";
            break;
        case AUTO: case DOUBLE: case INT: case STRUCT: case BREAK: case ELSE: case LONG: case SWITCH:
        case CASE: case ENUM: case REGISTER: case TYPEDEF: case CHAR: case EXTERN: case RETURN: case UNION:
        case CONST: case FLOAT: case SHORT: case UNSIGNED: case CONTINUE: case FOR: case SIGNED:
        case VOID: case DEFAULT: case GOTO: case SIZEOF: case VOLATILE: case DO: case IF: case STATIC: case WHILE:
            ret="keyword";
            break;
        case INTEGER:
            ret="integer";
            break;
        case REALNUM:
            ret="real_number";
            break;
        case CHAR_CONS:
            ret="character";
            break;
        case STRING:
            ret="string";
            break;
        case EndOfFile: 
            ret="EOF";
            break;
        case OPERATOR:
            ret="operator";
            break;
        case SYMBOL:
            ret="symbol";
            break;
        default:
            ret="error";
            break;
    }
    return ret;
}

bool ishex(char c){
    if(isdigit(c))  return true;
    else if(c=='A'||c=='a') return true;
    else if(c=='B'||c=='b') return true;
    else if(c=='C'||c=='c') return true;
    else if(c=='D'||c=='d') return true;
    else if(c=='E'||c=='e') return true;
    else if(c=='F'||c=='f') return true;
    return false;
}

Token::Token(TOKEN type,string data){
    this->type=type;
    this->data=data;
}

string Token::toString(){
    return "Token("+token2string(type)+","+data+")";
}

void Lexer::get_char(){
    position+=1;
    if(position>=text.length()) 
        curr_char=0;
    curr_char=text[position];
}

void Lexer::get_nbc(){
    while(curr_char!=0&&isspace(curr_char))
        get_char();
}

char Lexer::peek(int i){
    int pos=position+i;
    if(pos>=text.length())  return 0;
    return text[pos];
}

int Lexer::reserve(string str){
    const char* token=str.c_str();
    if(strcmp(token,"auto")==0) return AUTO;
    else if(strcmp(token,"double")==0)    return DOUBLE;
    else if(strcmp(token,"int")==0)    return INT;
    else if(strcmp(token,"struct")==0)    return STRUCT;
    else if(strcmp(token,"break")==0)    return BREAK;
    else if(strcmp(token,"else")==0)    return ELSE;
    else if(strcmp(token,"long")==0)    return LONG;
    else if(strcmp(token,"switch")==0)    return SWITCH;
    else if(strcmp(token,"case")==0)    return CASE;
    else if(strcmp(token,"enum")==0)    return ENUM;
    else if(strcmp(token,"register")==0)    return REGISTER;
    else if(strcmp(token,"typedef")==0)    return TYPEDEF;
    else if(strcmp(token,"char")==0)    return CHAR;
    else if(strcmp(token,"extern")==0)    return EXTERN;
    else if(strcmp(token,"return")==0)    return RETURN;
    else if(strcmp(token,"union")==0)    return UNION;
    else if(strcmp(token,"const")==0)    return CONST;
    else if(strcmp(token,"short")==0)    return SHORT;
    else if(strcmp(token,"float")==0)    return FLOAT;
    else if(strcmp(token,"unsigned")==0)    return UNSIGNED;
    else if(strcmp(token,"continue")==0)    return CONTINUE;
    else if(strcmp(token,"for")==0)    return FOR;
    else if(strcmp(token,"signed")==0)    return SIGNED;
    else if(strcmp(token,"void")==0)    return VOID;
    else if(strcmp(token,"default")==0)    return DEFAULT;
    else if(strcmp(token,"goto")==0)    return GOTO;
    else if(strcmp(token,"sizeof")==0)    return SIZEOF;
    else if(strcmp(token,"volatile")==0)    return VOLATILE;
    else if(strcmp(token,"do")==0)    return DO;
    else if(strcmp(token,"if")==0)    return IF;
    else if(strcmp(token,"static")==0)    return STATIC;
    else if(strcmp(token,"while")==0)    return WHILE;
    else return -1;
}  

Token Lexer::error(string err){
    get_char();
    return Token(ERROR,err);
}     

Lexer::Lexer(string filename){
    
    ifstream infile(filename);
    position=0;
    text.clear();
    if(!infile.is_open()){
        cerr<<"ERROR:"+filename+" is not found!"<<endl;
        return;
    }
    else{
        string line;
        // 逐行读取文件内容并存储到text中
        while (getline(infile, line)) {
            total_line++;
            if(line[line.length()-1]=='\\'){
                for(int i=0;i<line.length()-1;i++)
                    text+=line[i];  //原始文件的换行符被转义掉
            }
            else
                text += line + "\n"; // 保留原始文件中的换行符
        }
        curr_char=text[0];
        total_char=text.length();
    }
}

void Lexer::eat_comments(){
    /* 消去单行注释*/
    if(curr_char=='/'){
        while(curr_char!='\n'&&curr_char!=0)
            get_char();
    }
    /*消去多行注释*/
    else if(curr_char=='*'){
        int state=4;
        while(state!=6&&curr_char!=0){
            get_char();
            switch (state)
            {
                case 4:
                    if(curr_char!='*')  
                        state=4;
                    else if(curr_char=='*') 
                        state=5;
                    break;
                case 5:
                    if(curr_char=='*')  
                        state=5;
                    else if(curr_char=='/')    
                        state=6;
                    else if(curr_char!='*')
                        state=4;
                    break;
                default:
                    break;
            }
        }
    }
    get_char();
}

Token Lexer::get_id(){
    token.clear();
    if(curr_char=='_'){
        token="_";  //此语句块实现变量名下划线开头
        get_char();
    }
    while(curr_char!=0&&(isalnum(curr_char)||curr_char=='_')){
        token+=curr_char;
        get_char();
    }
    isKey=reserve(token);
    if(isKey==-1)   return Token(IDENTIFIER,token);
    else    return Token((TOKEN)isKey,token);
}

Token Lexer::get_number(){
    string ret="";
    if(curr_char=='0'&&(peek(1)=='x'||peek(1)=='X')){
        ret+=curr_char;
        get_char();
        ret+=curr_char;
        get_char();
        while(ishex(curr_char)){
            ret+=curr_char;
            get_char();
        }
        return Token(INTEGER,ret);
    }
    else if(isdigit(curr_char)){
        while(isdigit(curr_char)){
            ret+=curr_char;
            get_char();
        }
        if(curr_char!='e'&&curr_char!='E'&&curr_char!='.')
            return Token(INTEGER,ret);
        else{
            int state=2;
            while(true){
                switch (state){
                    case 2:
                        if(curr_char=='E'||curr_char=='e')
                            state=5;
                        else if(curr_char=='.')
                            state=3;
                        break;
                    case 3:
                        ret+=curr_char;
                        get_char();
                        if(isdigit(curr_char)){
                            ret+=curr_char;
                            get_char();
                            state=4;
                        }
                        else    
                            return error(ret);
                        break;
                    case 4:
                        while(isdigit(curr_char)){
                            ret+=curr_char;
                            get_char();
                            state=4;
                        }
                        if(curr_char!='e'&&curr_char!='E')
                            return Token(REALNUM,ret);
                        else if(curr_char=='e'&&curr_char=='E')
                            state=5;
                        break;
                    case 5:
                        ret+=curr_char;
                        get_char();
                        if(isdigit(curr_char)){
                            state=7;
                            ret+=curr_char;
                            get_char();
                        }
                        else if(curr_char=='+'||curr_char=='-'){
                            state=6;
                            ret+=curr_char;
                            get_char();
                        }
                        else
                            return error(ret);
                        break;
                    case 6:
                        if(isdigit(curr_char)){
                            state=7;
                            ret+=curr_char;
                            get_char();
                        }
                        else
                            return error(ret);
                        break;
                    case 7:
                        while(isdigit(curr_char)){
                            ret+=curr_char;
                            get_char();
                        }
                        return Token(REALNUM,ret);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

Token Lexer::get_charachter(){
    string ret="";
    while(curr_char!=0&&curr_char!='\''&&curr_char!='\n'){
        ret+=curr_char;
        get_char();
    }
    if(curr_char=='\n'){
        get_char();
        return error(ret);
    }
    get_char();
    return Token(CHAR_CONS,ret);
}

Token Lexer::get_string(){
    string ret="";
    while(curr_char!=0&&curr_char!='"'&&curr_char!='\n'){
        ret+=curr_char;
        get_char();
    }
    if(curr_char=='\n'){
        get_char();
        return error(ret);
    }
    get_char();
    return Token(STRING,ret);
}

Token Lexer::get_next_token(){
    while(curr_char!=0){

        if(curr_char=='/'){
            char temp=peek(1);
            if(temp=='/'||temp=='*'){
                get_char();
                eat_comments();
                continue;
            }
            else if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"/=");
            }
            else{
                get_char();
                return Token(OPERATOR,"/");
            }
        }

        if(isspace(curr_char)){
            get_nbc();
            continue;
        }

        if(curr_char=='_'||isalpha(curr_char))
            return get_id();

        if(curr_char=='+'){
            char temp=peek(1);
            if(temp=='+'){
                get_char();
                get_char();
                return Token(OPERATOR,"++");
            }
            else if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"+=");
            }
            else{
                get_char();
                return Token(OPERATOR,"+");
            }
        }

        if(curr_char=='-'){
            char temp=peek(1);
            if(temp=='-'){
                get_char();
                get_char();
                return Token(OPERATOR,"--");
            }
            else if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"-=");
            }
            else if(temp=='>'){
                get_char();
                get_char();
                return Token(SYMBOL,"->");
            }
            else{
                get_char();
                return Token(OPERATOR,"-");
            }
        }

        if(curr_char=='*'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"*=");
            }
            else{
                get_char();
                return Token(OPERATOR,"*");
            }
        }

        if(curr_char=='%'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"%=");
            }
            else{
                get_char();
                return Token(OPERATOR,"%");
            }
        }

        if(curr_char=='>'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,">=");
            }
            if(temp=='>'){
                char temp1=peek(2);
                if(temp1=='='){
                    get_char();
                    get_char();
                    get_char();
                    return Token(OPERATOR,">>=");
                }
                else{
                    get_char();
                    get_char();
                    return Token(OPERATOR,">>");
                }
            }
            else{
                get_char();
                return Token(OPERATOR,">");
            }
        }

        if(curr_char=='<'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"<=");
            }
            if(temp=='<'){
                char temp1=peek(2);
                if(temp1=='='){
                    get_char();
                    get_char();
                    get_char();
                    return Token(OPERATOR,"<<=");
                }
                else{
                    get_char();
                    get_char();
                    return Token(OPERATOR,"<<");
                }
            }
            else{
                get_char();
                return Token(OPERATOR,"<");
            }
        }

        if(curr_char=='!'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"!=");
            }
            else{
                get_char();
                return Token(OPERATOR,"!");
            }
        }

        if(curr_char=='&'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"&=");
            }
            else if(temp=='&'){
                get_char();
                get_char();
                return Token(OPERATOR,"&&");
            }
            else{
                get_char();
                return Token(OPERATOR,"&");
            }
        }

        if(curr_char=='|'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"|=");
            }
            else if(temp=='|'){
                get_char();
                get_char();
                return Token(OPERATOR,"||");
            }
            else{
                get_char();
                return Token(OPERATOR,"|");
            }
        }

        if(curr_char=='='){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"==");
            }
            else{
                get_char();
                return Token(OPERATOR,"=");
            }
        }

        if(curr_char=='^'){
            char temp=peek(1);
            if(temp=='='){
                get_char();
                get_char();
                return Token(OPERATOR,"^=");
            }
            else{
                get_char();
                return Token(OPERATOR,"^");
            }
        }

        if(curr_char=='\''){
            get_char();
            return  get_charachter();
        }

        if(curr_char=='"'){
            get_char();
            return get_string();
        }

        if(isdigit(curr_char))
            return get_number();

        if(curr_char=='?'){
            get_char();
            return Token(OPERATOR,"?");
        }

        if(curr_char==':'){
            get_char();
            return Token(OPERATOR,":");
        }

        if(curr_char=='~'){
            get_char();
            return Token(OPERATOR,"~");
        }

        if(curr_char=='('){
            get_char();
            return Token(SYMBOL,"(");
        }

        if(curr_char==')'){
            get_char();
            return Token(SYMBOL,")");
        }

        if(curr_char=='['){
            get_char();
            return Token(SYMBOL,"[");
        }

        if(curr_char==']'){
            get_char();
            return Token(SYMBOL,"]");
        }

        if(curr_char=='{'){
            get_char();
            return Token(SYMBOL,"{");
        }

        if(curr_char=='}'){
            get_char();
            return Token(SYMBOL,"}");
        }

        if(curr_char==','){
            get_char();
            return Token(SYMBOL,",");
        }

        if(curr_char==';'){
            get_char();
            return Token(SYMBOL,";");
        }
        return error(string(1,curr_char));
    }
    return Token(EndOfFile,"EOF");
}