#include "Var.h"

Var::Var () {}

Var::Var (size_t _row, size_t _col, std::string _literral, std::string _dataType, std::string _value) 
    : row(_row), col(_col), litteral(_literral), dataType(_dataType), value(_value) {}

Var::Var (Token& token) {
    row = token.row;
    col = token.col;
    litteral = token.litteral;
    dataType = token.dataType;
}

Var::Var (Expression& expr) {
    if (expr.type == 9) {
        row = expr.actualTokenSeq[1].row;
        col = expr.actualTokenSeq[1].col;
        litteral = expr.actualTokenSeq[1].litteral;
        dataType = expr.actualTokenSeq[2].litteral;
        value = expr.actualTokenSeq[4].litteral;

        expr.actualTokenSeq[1].dataType = dataType;
        expr.actualTokenSeq[1].value = value;
    } else throw std::runtime_error("Var contructor: wrong expression type. Expected VarDeclarationExpression.");
}

/* Operators */

std::ostream& operator << (std::ostream& os, Var& var) {
    os << "<" << var.row << ":" << var.col << "> " << var.litteral << " " << var.dataType << " = " << var.value;
    return os;
}

bool operator == (Var& lhs, Var& rhs) {
    return tie(lhs.row, lhs.col, lhs.litteral, lhs.dataType, lhs.value) == tie(rhs.row, rhs.col, rhs.litteral, rhs.dataType, rhs.value);
}