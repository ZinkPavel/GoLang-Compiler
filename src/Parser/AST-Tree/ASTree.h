#pragma once

#include "../../Compiler/Token.h"
#include "../Expression.h"

struct ASTRoot {
    Token token = {"root", "root", 0, 0};
    std::vector<Token> childs;
};

struct ASTNode {
    Token token;
    ASTNode *left, *right, *parent;
};

class ASTree {
public:
    ASTree ();

    ASTRoot *root;
    size_t nestingLevel = 0;

    void build (const std::vector<std::shared_ptr<Expression>>& exprSeq); // mb not & ? 
    void insert (const ASTNode& node);
};

/* Operators */

std::ostream& operator<< (std::ostream&, const ASTree& tree);
