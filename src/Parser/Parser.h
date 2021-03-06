#pragma once

#include <vector>
#include <memory>
#include <utility>
#include <stack>

#include "Expression.h"

#define EXPR_HIT(exprType) \
    newExpression = std::make_shared<exprType>(); \
    type = types.find(#exprType)->second; \
    counterEntry++;

class Parser {
private:
    size_t currentRow = 1;
    size_t numOfReadTokens = 0;

    Status status;
    std::vector<std::shared_ptr<Expression>> exprs;
    std::stack<std::shared_ptr<Expression>> braceStack;
    std::vector<Token> undefineTokenSeq;

public:
    Parser ();

    void update (const std::vector<Token>& tokensFromLexer, bool isTestPass);
    const std::vector<std::shared_ptr<Expression>>& getExprs () const;
    const Status& getComplitionStatus () const;
    const std::stack<std::shared_ptr<Expression>>& getBraceStack () const;
};