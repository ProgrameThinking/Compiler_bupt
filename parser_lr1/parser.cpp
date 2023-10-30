#include "LR1.h"

int main(void){
    Parser parser;
    parser.set_expr_set();
    parser.set_parsing_table();
    parser.analyze();
    return 0;
}
