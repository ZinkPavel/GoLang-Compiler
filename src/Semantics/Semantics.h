#pragma once

#include "../Compiler/Compiler.h"

class Var {
public:
    size_t row, col;
    std::string litteral, dataType, value;

    Var (Expression& expr);
};

/* Operaotors */

std::ostream& operator << (std::ostream& os, Var& var);

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs);

void semCheckFuncDeclare (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);
void semCheckVarDeclaration (std::vector<std::shared_ptr<Expression>> varDeclarationExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);
void semCheckVarDefinition (std::vector<std::shared_ptr<Expression>> varDefinitionExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);
void semCheckReturn (std::vector<std::shared_ptr<Expression>> returnExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);

void semCheckMultipleDeclaration (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars);