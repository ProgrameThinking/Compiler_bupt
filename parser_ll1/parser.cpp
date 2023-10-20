#include "LL1.h"
#include <map>
#include <vector>

int main(int argc, char *argv[])
{
  Parser parser;
  parser.set_expr_set();
  parser.set_first_table();
  parser.set_follow_table();
  parser.set_llTable();
  parser.analyze();
  
  return 0;
}
