#pragma once

#include <set>
#include <vector>
#include <map>
#include <regex>
#include <string>

#include "../Compiler/Token.h"
#include "../Tools/OperatorsRedefinition.h"

const std::set<std::string> dataTypes = {"int", "double", "float", "bool", "string"};
const std::set<std::string> possibleSings = {"EXCLAMATION"};
const std::set<std::string> vars = {"identifier", "numeric_const", "bin_cont", "octal_const", "hex_const"};
const std::set<std::string> arithmeticSings = {"NOT_EQUAL", "DOUBLE_EQUAL", "OR", "AND", "PLUS", "MINUS", "STAR", "SLASH", "PROC", "LESS", "MORE"};
const std::set<std::string> assignSings = {"ASSIGN"};

const std::map<std::string, size_t> types = {
    {"MathExpr",        1},
    {"ReturnExpr",      2},
    {"ImportExpr",      3},
    {"PackageExpr",     4},
    {"IfExpr",          5},
    {"WhileLoopExpr",       6},
    {"FuncDeclarationExpr",    7},
    {"VarDefinitionExpr",      8},
    {"VarDeclarationExpr",     9},
    {"FuncCallExpr",    10}
};

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
    std::vector<std::set<std::string>> expectedSeq;
    std::regex regexMask;

public:
    bool hasBraceSeq = false;
    bool completeExpr = false;
    Status endingStatus; // exclusively for tests
    std::vector<Token> actualTokenSeq;
    size_t type;

    Expression ();

    Status checkExpr ();
    bool checkByRegexMask ();
    bool exprIdentification (const std::vector<Token>& undefineTokenSeq);
};

/* Operators */

std::ostream& operator << (std::ostream& os, Expression& expr);
std::ostream& operator << (std::ostream& os, Status& status);

/* Exprs */

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

class FuncDeclarationExpr: public Expression {
public:
    FuncDeclarationExpr ();
};

class VarDefinitionExpr: public Expression {
public:
    VarDefinitionExpr ();
};

class VarDeclarationExpr: public Expression {
public:
    VarDeclarationExpr ();
};

class FuncCallExpr: public Expression {
public:
    FuncCallExpr ();
};

/* Checks */

bool isMathExpr (std::vector<Token>& undefineTokenSeq);
bool isReturnExpr (std::vector<Token>& undefineTokenSeq);
bool isImportExpr (std::vector<Token>& undefineTokenSeq);
bool isPackageExpr (std::vector<Token>& undefineTokenSeq);
bool isIfExpr (std::vector<Token>& undefineTokenSeq);
bool isWhileLoopExpr (std::vector<Token>& undefineTokenSeq);
bool isFuncDeclareExpr (std::vector<Token>& undefineTokenSeq);
bool isVarDefinitionExpr (std::vector<Token>& undefineTokenSeq);
bool isVarDeclarationExpr (std::vector<Token>& undefineTokenSeq);
bool isFuncCallExpr (std::vector<Token>& undefineTokenSeq);