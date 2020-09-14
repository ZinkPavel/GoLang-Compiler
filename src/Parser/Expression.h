#pragma once

#include <set>
#include <vector>
#include <regex>
#include <string>

#include "../Compiler/Token.h"

const std::set<std::string> dataTypes = {"int", "double", "float", "bool", "string"};
const std::set<std::string> possibleSings = {"EXCLAMATION"};
const std::set<std::string> numericVars = {"identifier", "numeric_const", "bin_cont", "octal_const", "hex_const"};
const std::set<std::string> arithmeticSings = {"OR", "AND", "PLUS", "MINUS", "STAR", "SLASH", "PROC", "LESS", "MORE"};

struct Status {
public:
    bool panicMode = false;
    bool waitingNewExpr = true;

    Status ();
    Status (bool first, bool second);
};

class Expression {
protected:
    size_t indexInExpSeq = 0;
    // size_t minAmountTokens = 1;
    std::vector<std::set<std::string>> expectedSeq;
    // std::set<std::string> lastSignificantTokenType;
    std::regex regexMask;

public:
    bool completeExpr = false;
    std::vector<Token> actualTokenSeq;
    // Status endingStatus; // exclusively for tests -- remove it

    Expression ();

    Status checkExpr ();
    bool checkByRegexMask ();
};

// Exprs

class MathExpr: public Expression {
public:
    MathExpr ();
};

/* class ReturnExpr: public Expression {
public:
    ReturnExpr ();    
}; */

/* class FuncDeclareExpr: public Expression {
public:
    FuncDeclareExpr ();
}; */

/* class ImportExpr: public Expression {
public:
    ImportExpr ();
}; */

/* class PackageExpr: public Expression {
public:
    PackageExpr ();
}; */

/* class CommentExpr: public Expression {
public:
    CommentExpr ();
}; */

// Checks

bool isMathExpr (const Token& newToken);
// bool isReturnExpr (const Token& newToken);
// bool isFuncDeclareExpr (const Token& newToken);
// bool isImportExpr (const Token& newToken);
// bool isPackageExpr (const Token& newToken);
// bool isCommentExpr (const Token& newToken);