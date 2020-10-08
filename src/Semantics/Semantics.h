#pragma once

#include "../Compiler/Token.h"
#include "../Parser/Expression.h"

#include "Var.h"
#include "Block.h"

class Semantics {
public:
    std::vector<Block> blocks;
    
    Semantics ();
    
    void addVarByExpr(Expression& expr);

    void analysis (const std::vector<std::shared_ptr<Expression>>& exprs);
};

// void semCheckVarDeclaration (std::vector<std::shared_ptr<Expression>> varDeclarationExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);
// void semCheckVarDefinition (std::vector<std::shared_ptr<Expression>> varDefinitionExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);
// void semCheckReturn (std::vector<std::shared_ptr<Expression>> returnExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);

// void semCheckMultipleDeclaration (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);