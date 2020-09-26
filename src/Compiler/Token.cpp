#include "Token.h"

Token::Token () {}

Token::Token (const std::string& newType, const std::string& newLitteral, const size_t& newRow, const size_t& newCol)
    : row(newRow), col(newCol), type(newType), litteral(newLitteral) {}

std::ostream& operator << (std::ostream& os, const Token& token) {
    return os << '<' << token.row << ':' << token.col << "> " << token.type << " \'" << token.litteral << '\'';
}

bool operator == (const Token& lhs, const Token& rhs) {
    return tie(lhs.type, lhs.litteral) == tie(rhs.type, rhs.litteral);
}