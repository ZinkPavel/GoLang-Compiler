#pragma once

#include "../Compiler/Compiler.h"

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs);

void semCheckFuncDeclare (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blockByVars);
