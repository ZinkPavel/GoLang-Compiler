#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <regex>

#include "Var.h"
#include "../Parser/Expression.h"

class Block {
public:
    bool hasReturn = false,
        hasArgs = false;

    size_t start, end;
    std::string name, argsType, returnType;
    std::vector<Var> vars;

    Block ();
    Block (Expression& expr);

    void multipleDeclarationCheck ();
};