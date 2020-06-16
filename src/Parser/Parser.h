#pragma once

#include <vector>
#include <memory>
#include <utility>

#include "Expression.h"

#define MAKE_NEW_EXPR(exprType) \
    exprs.push_back(std::make_shared<exprType>()); \
    waitingNewExpr = false;

class Parser {
private:
    int currentRow = 1;
    size_t numOfReadTokens = 0;

    Status status;
    std::vector<std::shared_ptr<Expression>> exprs;

public:
    Parser ();

    const std::vector<std::shared_ptr<Expression>>& getExprs () const;
    void update (const std::vector<Token>& tokensFromLexer);
};