#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "../Compiler/Token.h"
#include "../Parser/Expression.h"
#include "../Semantics/Semantics.h"

class CodeGenerator {    
public:
    size_t nestingLevel, numBranches, shift;
    std::string outPath;
    std::vector<std::string> outData;
    std::vector<Token> vars;

    CodeGenerator ();

    std::vector<Token>& getVars ();

    void generate (Semantics& semantics, const std::vector<std::shared_ptr<Expression>>& exprs);
    void write (std::stringstream& ss);
    
    void genPrologue (std::stringstream& ss);
    
    void genReturn (std::stringstream& ss, const Block& block, Expression& expr);
    void genVarDeclaration (std::stringstream& ss, Block& block, Expression& expr);
    void genVarDefiniton (std::stringstream& ss, Block& block, Expression& expr);
    
    void genEpilogue (std::stringstream& ss);
};