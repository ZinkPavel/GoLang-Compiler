#pragma once

#include "../Compiler/Compiler.h"

// std::shared_ptr<Expression> classification (Expression& expr);
void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs);