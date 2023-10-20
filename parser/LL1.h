#ifndef LL_H_
#define LL_H_

#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum Symbol {
  E,
  E_,
  T,
  T_,
  F,
  add,
  sub,
  mul,
  divd,
  leftparen,
  rightparen,
  number,
  epsilon,
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

class Parser {
private:
  bool is_first_set(Symbol judge, Symbol set);
  bool is_follow_set(Symbol judge, Symbol set);

public:
  vector<Experiation> expr_set;
  map<Symbol, vector<Symbol>> first_set;
  map<Symbol, vector<Symbol>> follow_set;
  map<pair<Symbol, Symbol>, Experiation> llTable;
  /* *
   * 将表达式写入expr_set中
   * E->TE'
   * E'->+TE'
   * E'->-TE'
   * E'-> nan
   * T->FT'
   * T'->*FT'
   * T'->/FT'
   * T'-> nan
   * F->(E)
   * F-> num
   * */
  void set_expr_set();
  /* *
   *  build first set and follow set
   *  X       First       Follow
   *  E       (,num       $,)
   *  E_      +,-,ε       $,)
   *  T       (,num       $,+,-,)
   *  T_      *,/,ε       $,+,-,)
   *  F       (,num       $,+,-,*,/,)
   * */
  void set_first_table();
  void set_follow_table();
  void set_llTable();
  void analyze();
  void show_info();

  friend ostream &operator<<(ostream &os, const map<Symbol, vector<Symbol>> &c);
  friend ostream &operator<<(ostream &os,
                             const map<pair<Symbol, Symbol>, Experiation> &c);
};

class Token {
  Symbol sym;
};

#endif
