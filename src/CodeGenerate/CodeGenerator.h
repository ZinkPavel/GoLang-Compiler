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
    bool hasBranches;
    size_t nestingLevel, numBranches, shift, point;
    std::string outPath;
    std::vector<std::string> outData;
    std::vector<Token> vars;

    CodeGenerator ();

    std::vector<Token>& getVars ();

    void generate (Semantics& semantics, const std::vector<std::shared_ptr<Expression>>& exprs);
    void write (std::vector<std::stringstream>& streams);
    
    void genPrologue (std::stringstream& ss);
    
    void genReturn (std::vector<std::stringstream>& streams, const Block& block, Expression& expr);
    void genIf (std::vector<std::stringstream>& streams, const Block& block, Expression& expr);
    void genVarDeclaration (std::vector<std::stringstream>& streams, Block& block, Expression& expr);
    void genVarDefiniton (std::vector<std::stringstream>& streams, Block& block, Expression& expr);
    
    void genEpilogue (std::stringstream& ss);
};