#include "LR1.h"
#include <FlexLexer.h>
#include <utility>
#include <stack>

Experiation::Experiation(Symbol from, vector<Symbol> to)
{
  this->from = from;
  this->to = to;
}

Experiation::Experiation() {}

/**
 * 将输入的符号转换为Symbol表中定义的字符
 * string s=symbol2char(E)
 * s为"E"
 * */
string symbol2char(Symbol a)
{
  if (a == E)
    return "E";
  else if (a == E_)
    return "E'";
  else if (a == T)
    return "T";
  else if (a == F)
    return "F";
  else if (a == add)
    return "+";
  else if (a == sub)
    return "-";
  else if (a == mul)
    return "*";
  else if (a == divd)
    return "/";
  else if (a == leftparen)
    return "(";
  else if (a == rightparen)
    return ")";
  else if (a == number)
    return " num ";
  else if (a == start)
    return "S";
  else if (a == End)
    return "$";
  else if (a == EndOfFile)
    return "EOF";
  else
    return "Error";
}

Symbol int2Symbol(int value) { return static_cast<Symbol>(value); }

ostream &operator<<(ostream &os, const Experiation &c)
{
  os << symbol2char(c.from);
  if (c.from != ERROR)
    os << "->";
  for (int i = 0; i < c.to.size(); i++)
    os << symbol2char(c.to[i]);
  return os;
}

void Parser::set_expr_set()
{
  expr_set.push_back(Experiation(E_, vector<Symbol>{E}));
  expr_set.push_back(Experiation(E, vector<Symbol>{E, add, T}));
  expr_set.push_back(Experiation(E, vector<Symbol>{E, sub, T}));
  expr_set.push_back(Experiation(E, vector<Symbol>{T}));
  expr_set.push_back(Experiation(T, vector<Symbol>{T, mul, F}));
  expr_set.push_back(Experiation(T, vector<Symbol>{T, divd, F}));
  expr_set.push_back(Experiation(T, vector<Symbol>{F}));
  expr_set.push_back(Experiation(F, vector<Symbol>{leftparen, E, rightparen}));
  expr_set.push_back(Experiation(F, vector<Symbol>{number}));
}

void Parser::set_parsing_table()
{
  vector symbols = {add, sub, mul, divd, leftparen, rightparen,
                    number, End, E_, E, T, F};
  for (int i = 0; i < 16; i++)
    for (int j = 0; j < symbols.size(); j++)
      parsing_table[make_pair(i, symbols[j])] = tableItem();

  parsing_table[make_pair(0, leftparen)] = tableItem('S', 6);
  parsing_table[make_pair(0, number)] = tableItem('S', 7);
  parsing_table[make_pair(0, E)] = tableItem('S', 1);
  parsing_table[make_pair(0, T)] = tableItem('S', 4);
  parsing_table[make_pair(0, F)] = tableItem('S', 5);

  parsing_table[make_pair(1, add)] = tableItem('S', 2);
  parsing_table[make_pair(1, sub)] = tableItem('S', 8);
  parsing_table[make_pair(1, End)] = tableItem('A', -1);

  parsing_table[make_pair(2, leftparen)] = tableItem('S', 6);
  parsing_table[make_pair(2, number)] = tableItem('S', 7);
  parsing_table[make_pair(2, T)] = tableItem('S', 14);
  parsing_table[make_pair(2, F)] = tableItem('S', 5);

  parsing_table[make_pair(3, add)] = tableItem('S', 2);
  parsing_table[make_pair(3, sub)] = tableItem('S', 8);
  parsing_table[make_pair(3, rightparen)] = tableItem('S', 9);

  parsing_table[make_pair(4, add)] = tableItem('R', 4);
  parsing_table[make_pair(4, sub)] = tableItem('R', 4);
  parsing_table[make_pair(4, mul)] = tableItem('S', 10);
  parsing_table[make_pair(4, divd)] = tableItem('S', 11);
  parsing_table[make_pair(4, rightparen)] = tableItem('R', 4);
  parsing_table[make_pair(4, End)] = tableItem('R', 4);

  parsing_table[make_pair(5, add)] = tableItem('R', 7);
  parsing_table[make_pair(5, sub)] = tableItem('R', 7);
  parsing_table[make_pair(5, mul)] = tableItem('R', 7);
  parsing_table[make_pair(5, divd)] = tableItem('R', 7);
  parsing_table[make_pair(5, rightparen)] = tableItem('R', 7);
  parsing_table[make_pair(5, End)] = tableItem('R', 7);

  parsing_table[make_pair(6, leftparen)] = tableItem('S', 6);
  parsing_table[make_pair(6, number)] = tableItem('S', 7);
  parsing_table[make_pair(6, E)] = tableItem('S', 3);
  parsing_table[make_pair(6, T)] = tableItem('S', 4);
  parsing_table[make_pair(6, F)] = tableItem('S', 5);

  parsing_table[make_pair(7, add)] = tableItem('R', 9);
  parsing_table[make_pair(7, sub)] = tableItem('R', 9);
  parsing_table[make_pair(7, mul)] = tableItem('R', 9);
  parsing_table[make_pair(7, divd)] = tableItem('R', 9);
  parsing_table[make_pair(7, rightparen)] = tableItem('R', 9);
  parsing_table[make_pair(7, End)] = tableItem('R', 9);

  parsing_table[make_pair(8, leftparen)] = tableItem('S', 6);
  parsing_table[make_pair(8, number)] = tableItem('S', 7);
  parsing_table[make_pair(8, T)] = tableItem('S', 15);
  parsing_table[make_pair(8, F)] = tableItem('S', 5);

  parsing_table[make_pair(9, add)] = tableItem('R', 8);
  parsing_table[make_pair(9, sub)] = tableItem('R', 8);
  parsing_table[make_pair(9, mul)] = tableItem('R', 8);
  parsing_table[make_pair(9, divd)] = tableItem('R', 8);
  parsing_table[make_pair(9, rightparen)] = tableItem('R', 8);
  parsing_table[make_pair(9, End)] = tableItem('R', 8);

  parsing_table[make_pair(10, leftparen)] = tableItem('S', 6);
  parsing_table[make_pair(10, number)] = tableItem('S', 7);
  parsing_table[make_pair(10, F)] = tableItem('S', 12);

  parsing_table[make_pair(11, leftparen)] = tableItem('S', 6);
  parsing_table[make_pair(11, number)] = tableItem('S', 7);
  parsing_table[make_pair(11, F)] = tableItem('S', 13);

  parsing_table[make_pair(12, add)] = tableItem('R', 5);
  parsing_table[make_pair(12, sub)] = tableItem('R', 5);
  parsing_table[make_pair(12, mul)] = tableItem('R', 5);
  parsing_table[make_pair(12, divd)] = tableItem('R', 5);
  parsing_table[make_pair(12, rightparen)] = tableItem('R', 5);
  parsing_table[make_pair(12, End)] = tableItem('R', 5);

  parsing_table[make_pair(13, add)] = tableItem('R', 6);
  parsing_table[make_pair(13, sub)] = tableItem('R', 6);
  parsing_table[make_pair(13, mul)] = tableItem('R', 6);
  parsing_table[make_pair(13, divd)] = tableItem('R', 6);
  parsing_table[make_pair(13, rightparen)] = tableItem('R', 6);
  parsing_table[make_pair(13, End)] = tableItem('R', 6);

  parsing_table[make_pair(14, add)] = tableItem('R', 2);
  parsing_table[make_pair(14, sub)] = tableItem('R', 2);
  parsing_table[make_pair(14, mul)] = tableItem('S', 10);
  parsing_table[make_pair(14, divd)] = tableItem('S', 11);
  parsing_table[make_pair(14, rightparen)] = tableItem('R', 2);
  parsing_table[make_pair(14, End)] = tableItem('R', 2);

  parsing_table[make_pair(15, add)] = tableItem('R', 3);
  parsing_table[make_pair(15, sub)] = tableItem('R', 3);
  parsing_table[make_pair(15, mul)] = tableItem('S', 10);
  parsing_table[make_pair(15, divd)] = tableItem('S', 11);
  parsing_table[make_pair(15, rightparen)] = tableItem('R', 3);
  parsing_table[make_pair(15, End)] = tableItem('R', 3);
}

void Parser::analyze()
{
  FlexLexer *lexer = new yyFlexLexer;
  int token = 0;
  vector<pair<Symbol, string>> token_list;
  // 得到token流
  while (token = lexer->yylex())
  {
    if (int2Symbol(token) == EndOfFile)
      break;
    token_list.push_back(make_pair(int2Symbol(token), string(lexer->YYText())));
  }
  token_list.push_back(make_pair(End, "$"));
  stack<int> state_stack;
  stack<Symbol> oper_stack;
  state_stack.push(0);
  int ptr=0;
  do{
    int now_state=state_stack.top();
    Symbol a=token_list[ptr].first;
    if(parsing_table[make_pair(now_state,a)].oper=='S'){
      oper_stack.push(a);
      state_stack.push(parsing_table[make_pair(now_state,a)].num);
      ptr++;
    }
    else if(parsing_table[make_pair(now_state,a)].oper=='R'){
      Experiation expr=expr_set[parsing_table[make_pair(now_state,a)].num-1];
      cout<<expr<<endl;
      for(int i=0;i<expr.to.size();i++){
        oper_stack.pop();
        state_stack.pop();
      }
      state_stack.push(parsing_table[make_pair(state_stack.top(),expr.from)].num);
      oper_stack.push(expr.from);
    }
    else if(parsing_table[make_pair(now_state,a)].oper=='A'){
      return;
    }
    else if(parsing_table[make_pair(now_state,a)].oper=='E'){
      cout<<"ERROR"<<endl;
      exit(-1);
    }
  }while(true);

}
