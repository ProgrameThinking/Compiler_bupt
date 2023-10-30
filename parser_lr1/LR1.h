#ifndef LR1_H_
#define LR1_H_

#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum Symbol {
  E,
  E_,
  T,
  F,
  add,
  sub,
  mul,
  divd,
  leftparen,
  rightparen,
  number,
  start,
  End,
  EndOfFile,
  ERROR,
};

class Experiation {
public:
  /*
   * 例如：E->TE',我们可以表示成：
   * from=E
   * to=(T,E')
   */
  Symbol from;
  vector<Symbol> to;

  Experiation(Symbol from, vector<Symbol> to);
  Experiation();
  friend ostream &operator<<(ostream &os, const Experiation &c);
};

struct tableItem{
    /*
     * 表中的表项，如S1，R5，或E-1（代表出错）
     * */
    char oper;  
    int num;
    tableItem() :oper('E'), num(-1){}
	tableItem(char op, int n) :oper(op), num(n){}
};

class Parser{
    public:
        vector<Experiation> expr_set;
        // SLR1 parsing table
        map<pair<int,Symbol>, tableItem> parsing_table;
        void set_expr_set();
        void set_parsing_table();
        void analyze();
};

#endif
