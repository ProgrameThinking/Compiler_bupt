#include "LL1.h"
#include <FlexLexer.h>
#include <stack>
#include <string>
#include <utility>

Experiation::Experiation(Symbol from, vector<Symbol> to) {
  this->from = from;
  this->to = to;
}

Experiation::Experiation() {}

/**
 * 将输入的符号转换为Symbol表中定义的字符
 * string s=symbol2char(E)
 * s为"E"
 * */
string symbol2char(Symbol a) {
  if (a == E)
    return "E";
  else if (a == E_)
    return "E'";
  else if (a == T)
    return "T";
  else if (a == T_)
    return "T'";
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
  else if (a == epsilon)
    return " nan ";
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

ostream &operator<<(ostream &os, const Experiation &c) {
  os << symbol2char(c.from);
  if (c.from != ERROR)
    os << "->";
  for (int i = 0; i < c.to.size(); i++)
    os << symbol2char(c.to[i]);
  return os;
}

ostream &operator<<(ostream &os, const map<Symbol, vector<Symbol>> &c) {
  for (auto it = c.begin(); it != c.end(); it++) {
    os << symbol2char(it->first) << "  ";
    for (int i = 0; i < it->second.size(); i++)
      os << symbol2char(it->second[i]) << " ";
    os << endl;
  }
  return os;
}

ostream &operator<<(ostream &os,
                    const map<pair<Symbol, Symbol>, Experiation> &c) {
  for (auto it = c.begin(); it != c.end(); it++) {
    if (it->second.from != ERROR)
      os << symbol2char(it->first.first) << " " << symbol2char(it->first.second)
         << " " << it->second << endl;
  }
  return os;
}

void Parser::set_expr_set() {
  expr_set.push_back(Experiation(E, vector<Symbol>{T, E_}));
  expr_set.push_back(Experiation(E_, vector<Symbol>{add, T, E_}));
  expr_set.push_back(Experiation(E_, vector<Symbol>{sub, T, E_}));
  expr_set.push_back(Experiation(E_, vector<Symbol>{epsilon}));
  expr_set.push_back(Experiation(T, vector<Symbol>{F, T_}));
  expr_set.push_back(Experiation(T_, vector<Symbol>{mul, F, T_}));
  expr_set.push_back(Experiation(T_, vector<Symbol>{divd, F, T_}));
  expr_set.push_back(Experiation(T_, vector<Symbol>{epsilon}));
  expr_set.push_back(Experiation(F, vector<Symbol>{leftparen, E, rightparen}));
  expr_set.push_back(Experiation(F, vector<Symbol>{number}));
}
void Parser::set_first_table() {
  first_set[E] = vector<Symbol>{leftparen, number};
  first_set[E_] = vector<Symbol>{add, sub, epsilon};
  first_set[T] = vector<Symbol>{leftparen, number};
  first_set[T_] = vector<Symbol>{mul, divd, epsilon};
  first_set[F] = vector<Symbol>{leftparen, number};
  first_set[add] = vector<Symbol>{add};
  first_set[sub] = vector<Symbol>{sub};
  first_set[mul] = vector<Symbol>{mul};
  first_set[divd] = vector<Symbol>{divd};
  first_set[leftparen] = vector<Symbol>{leftparen};
  first_set[rightparen] = vector<Symbol>{rightparen};
  first_set[number] = vector<Symbol>{number};
  first_set[epsilon] = vector<Symbol>{epsilon};
}
void Parser::set_follow_table() {
  follow_set[E] = vector<Symbol>{End, rightparen};
  follow_set[E_] = vector<Symbol>{End, rightparen};
  follow_set[T] = vector<Symbol>{End, add, sub, rightparen};
  follow_set[T_] = vector<Symbol>{End, add, sub, rightparen};
  follow_set[F] = vector<Symbol>{End, add, sub, mul, divd, rightparen};
}

bool Parser::is_first_set(Symbol judge, Symbol set) {
  for (int i = 0; i < first_set[set].size(); i++) {
    if (judge == first_set[set][i])
      return true;
  }
  return false;
}
bool Parser::is_follow_set(Symbol judge, Symbol set) {
  for (int i = 0; i < follow_set[set].size(); i++) {
    if (judge == follow_set[set][i])
      return true;
  }
  return false;
}

void Parser::set_llTable() {
  Symbol terminal[8] = {add, sub, mul, divd, leftparen, rightparen, number};
  Symbol non_terminal[5] = {E, E_, T, T_, F};
  /*
   *  将llTable初始化为NULL
   * */

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      llTable[make_pair(non_terminal[i], terminal[j])] =
          Experiation(ERROR, vector<Symbol>{});
    }
  }

  for (int i = 0; i < expr_set.size(); i++) {
    Symbol alpha = expr_set[i].to[0];
    /*
     * for (每个终结符号a in FIRST(alpha))
     *    把A→alpha放入M[A, a] 中;
     * */
    for (int j = 0; j < 8; j++) {
      if (is_first_set(terminal[j], alpha))
        llTable[make_pair(expr_set[i].from, terminal[j])] = expr_set[i];
    }
    /*
     * if (epsilon in FIRST(alpha))
     *  for (任何b in FOLLOW(A))
     *    把A→alpha放入M[A, b] 中;
     * */
    if (is_first_set(epsilon, alpha)) {
      for (int j = 0; j < follow_set[expr_set[i].from].size(); j++)
        llTable[make_pair(expr_set[i].from, follow_set[expr_set[i].from][j])] =
            expr_set[i];
    }
  }
}

void Parser::analyze() {
  FlexLexer *lexer = new yyFlexLexer;
  int token = 0;
  vector<pair<Symbol, string>> token_list;
  // 得到token流
  while (token = lexer->yylex()) {
    if (int2Symbol(token) == EndOfFile)
      break;
    token_list.push_back(make_pair(int2Symbol(token), string(lexer->YYText())));
  }
  token_list.push_back(make_pair(End, "$"));
  Symbol terminal[7] = {add, sub, mul, divd, leftparen, rightparen, number};
  Symbol non_terminal[5] = {E, E_, T, T_, F};

  stack<Symbol> st;
  int cnt = 0;
  st.push(End);
  st.push(E);
  /*
   * 判断符号是否为terminal
   * */
  auto isTerminal = [terminal](Symbol judge) {
    for (int i = 0; i < 7; i++) {
      if (judge == terminal[i])
        return true;
    }
    return false;
  };
  do {
    Symbol sym = token_list[cnt].first;
    Symbol top = st.top();
    if (isTerminal(top) || top == End) {
      if (top == sym) {
        st.pop();
        cnt++;
      } else
        cout << "ERROR" << endl;
    } else if (llTable[make_pair(top, sym)].from != ERROR) {
      st.pop();
      for (int i = llTable[make_pair(top, sym)].to.size() - 1; i >= 0; i--) {
        if (llTable[make_pair(top, sym)].to[i] != epsilon)
          st.push(llTable[make_pair(top, sym)].to[i]);
      }
      cout << llTable[make_pair(top, sym)] << endl;
    } else
      cout << "ERROR" << endl;
  } while (st.top() != End);
}

void Parser::show_info() {
  cout << "Experations:" << endl;
  for (int i = 0; i < expr_set.size(); i++)
    cout << expr_set[i] << endl;
  cout << endl;
  cout << "First Set:" << endl;
  cout << first_set << endl;
  cout << "Follow Set:" << endl;
  cout << follow_set << endl;
  cout << "LLTable:" << endl;
  cout << llTable << endl;
}
