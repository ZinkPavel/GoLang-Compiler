#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

enum CH { 
    SPACE = 32,
    EXCLAMATION = 33, // !
    DQUOTES = 34, // "
    GRID = 35, // #
    DOLLAR = 36, // $ 
    PROC = 37, // %
    AMPERSAND = 38, // &
    QUOTES = 39, // '
    L_PAREN = 40, // (
    R_PAREN = 41, // )
    STAR = 42, // *
    PLUS = 43, // +
    COMMA = 44, // ,
    MINUS = 45, // -
    DOT = 46, // .
    SLASH = 47, // '/'
    COLON = 58, // :
    SEMI = 59, // ;
    LESS = 60, // <
    MORE = 62, // >
    EQUAL = 61, // =
    PIPE = 124, // |
    L_BRACE = 123, // {
    R_BRACE = 125, // }
    BACKSLASH = 92, // '\'
    L_SQ_BRACE = 91, // [
    R_SQ_BRACE = 93, // ]
    LOW_SLIDE = 95, // _
};

const std::vector<std::string> keywords = {"int", "double", "var", "float", "return", "package",
    "import", "func", "bool", "string", "for", "if", "else", "while", "do", "true", "false", "print"};

class Token {
public:
    size_t row, col, nestingLevel = 0, shift;
    std::string type, dataType, value, litteral;

    Token ();
    Token (const std::string& newType, const std::string& newLitteral, const size_t& newRow = 0, const size_t& newCol = 0);

    void assignDataType ();
};

/* Operators */

std::ostream& operator << (std::ostream& os, const Token& token);
bool operator == (const Token& lhs, const Token& rhs);
bool operator < (const Token& lhs, const Token& rhs);