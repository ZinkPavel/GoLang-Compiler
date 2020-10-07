#include "Token.h"

Token::Token () {}

Token::Token (const std::string& newType, const std::string& newLitteral, const size_t& newRow, const size_t& newCol)
    : row(newRow), col(newCol), type(newType), litteral(newLitteral) {}

void Token::assignDataType () {
    if (type == "numeric_const") dataType = "int";
    else if (type == "string_litteral") dataType = "string";
    else if (type == "false" || type == "true") dataType = "bool";
}

std::ostream& operator << (std::ostream& os, const Token& token) {
    return os << '<' << token.row << ':' << token.col << "> " << token.type << " " << token.dataType << " \'" << token.litteral << "\'";
}

bool operator == (const Token& lhs, const Token& rhs) {
    return std::tie(lhs.type, lhs.litteral) == std::tie(rhs.type, rhs.litteral);
}

bool operator < (const Token& lhs, const Token& rhs) {
    return std::tie(lhs.row, lhs.col) < std::tie(rhs.row, rhs.col);
}