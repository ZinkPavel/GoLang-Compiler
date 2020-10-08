#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

#include "../Compiler/Token.h"
#include "../Parser/Expression.h"

class Var {
public:
    size_t row, col;
    std::string litteral, dataType, value;

    Var ();
    Var (size_t _row, size_t _col, std::string _literral, std::string _dataType, std::string _value);
    Var (Token& token);
    Var (Expression& expr);
};

/* Operaotors */

std::ostream& operator << (std::ostream& os, Var& var);
bool operator == (Var& lhs, Var& rhs);