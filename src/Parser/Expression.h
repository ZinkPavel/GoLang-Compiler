#pragma once

#include <set>
#include <vector>

#include "../Compiler/Token.h"

const std::set<std::string> dataTypes = {"int", "double", "float", "bool", "string"};
const std::set<std::string> possibleSings = {"EXCLAMATION"};
const std::set<std::string> numericVars = {"identifier", "numeric_const", "bin_cont", "octal_const", "hex_const"};
const std::set<std::string> arithmeticSings = {"OR", "AND", "PLUS", "MINUS", "STAR", "SLASH", "PROC", "LESS", "MORE"};

struct Status {
    bool panicMode = false;
    bool waitingNewExpr = true;

    Status () {
        panicMode = false;
        waitingNewExpr = true;
    }

    Status (bool first, bool second) {
        panicMode = first;
        waitingNewExpr = second;
    }
};

class Expression {
protected:
    std::vector<std::set<std::string>> expectedSeq;
    std::vector<std::set<std::string>>::iterator point;

public:
    bool completeExpr = false;
    std::vector<bool> multipleReference;
    std::vector<Token> actualTokenSeq;
    Status endingStatus; // exclusively for tests

    Expression ();

    Status checkExpr ();
};

// Exprs

/* class MathExpr: public Expression {
public:
    MathExpr ();
}; */

class ReturnExpr: public Expression {
public:
    ReturnExpr ();    
};

class FuncDeclareExpr: public Expression {
public:
    FuncDeclareExpr ();
};

class ImportExpr: public Expression {
public:
    ImportExpr ();
};

class PackageExpr: public Expression {
public:
    PackageExpr ();
};

class CommentExpr: public Expression {
public:
    CommentExpr ();
};

// Checks

// bool isMathExpr (const std::vector<Token>& undefinedTokenList);
bool isReturnExpr (const Token& newToken);
bool isFuncDeclareExpr (const Token& newToken);
bool isImportExpr (const Token& newToken);
bool isPackageExpr (const Token& newToken);
bool isCommentExpr (const Token& newToken);