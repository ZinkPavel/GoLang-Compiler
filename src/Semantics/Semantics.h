#pragma once

#include "../Compiler/Token.h"
#include "../Parser/Expression.h"

#include "Var.h"
#include "Block.h"

class Semantics {
public:
    std::vector<Block> blocks;
    
    Semantics ();
    
    void addVarByExpr (Expression& expr);
    void callReturnCheck (Expression& expr);
    void varDefinitionCheck (Expression& expr);
    void callFunctionCheck (Expression& expr);
    void ifCheck (Expression& expr);

    void analysis (const std::vector<std::shared_ptr<Expression>>& exprs);
};

/* Operators */

std::ostream& operator << (std::ostream& os, Semantics& semantics);