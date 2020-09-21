#pragma once

#include <set>
#include <vector>
#include <regex>
#include <string>

#include "../Compiler/Token.h"

const std::set<std::string> dataTypes = {"int", "double", "float", "bool", "string"};
const std::set<std::string> possibleSings = {"EXCLAMATION"};
const std::set<std::string> vars = {"identifier", "numeric_const", "bin_cont", "octal_const", "hex_const"};
const std::set<std::string> arithmeticSings = {"NOT_EQUAL", "DOUBLE_EQUAL", "OR", "AND", "PLUS", "MINUS", "STAR", "SLASH", "PROC", "LESS", "MORE"};
const std::set<std::string> assignSings = {"EQUAL"};

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
    Status endingStatus; // exclusively for tests
    bool hasBraceSeq = false;

    Expression ();

    Status checkExpr ();
    bool checkByRegexMask ();
    bool exprIdentification (const std::vector<Token>& undefineTokenSeq);
};

// Exprs

class MathExpr: public Expression {
public:
    MathExpr ();
};

class ReturnExpr: public Expression {
public:
    ReturnExpr ();    
};

class ImportExpr: public Expression {
public:
    ImportExpr ();
};

class PackageExpr: public Expression {
public:
    PackageExpr ();
};

class IfExpr: public Expression {
public:
    IfExpr ();
};

class WhileLoopExpr: public Expression {
public:
    WhileLoopExpr ();
};

class FuncDeclareExpr: public Expression {
public:
    FuncDeclareExpr ();
};

class AssignExpr: public Expression {
public:
    AssignExpr ();
};

// Checks

bool isMathExpr (std::vector<Token>& undefineTokenSeq);
bool isReturnExpr (std::vector<Token>& undefineTokenSeq);
bool isImportExpr (std::vector<Token>& undefineTokenSeq);
bool isPackageExpr (std::vector<Token>& undefineTokenSeq);
bool isIfExpr (std::vector<Token>& undefineTokenSeq);
bool isWhileLoopExpr (std::vector<Token>& undefineTokenSeq);
bool isFuncDeclareExpr (std::vector<Token>& undefineTokenSeq);
bool isAssignExpr (std::vector<Token>& undefineTokenSeq);