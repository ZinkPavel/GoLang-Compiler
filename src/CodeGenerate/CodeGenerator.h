#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

#include "../Compiler/Token.h"
#include "../Parser/Expression.h"
#include "../Semantics/Semantics.h"

enum BRNCH { IF, WHILE };

class CodeGenerator {    
public:
    bool pendingBranch, writeInWaitingStream;
    size_t nestingLevel, numBranches, numStr, shift, point;
    std::string outPath;
    std::vector<Token> vars;
    std::stringstream lcStream;
    std::vector<std::string> waitingStream;
    std::queue<size_t> branches;

    CodeGenerator ();

    std::vector<Token>& getVars ();

    void generate (Semantics& semantics, const std::vector<std::shared_ptr<Expression>>& exprs);
    void write (std::vector<std::stringstream>& streams, std::stringstream& strStream);
    
    void genPrologue (std::stringstream& ss);
    
    void genReturn (std::vector<std::stringstream>& streams, const Block& block, Expression& expr);
    void genIf (std::vector<std::stringstream>& streams, const Block& block, Expression& expr);
    void genWhile (std::vector<std::stringstream>& streams, const Block& block, Expression& expr);
    void genVarDeclaration (std::vector<std::stringstream>& streams, Block& block, Expression& expr);
    void genVarDefiniton (std::vector<std::stringstream>& streams, Block& block, Expression& expr);
    void genPrint (std::vector<std::stringstream>& streams, Block& block, Expression& expr);
    void genScan (std::vector<std::stringstream>& streams, Block& block, Expression& expr);
    
    void genEpilogue (std::stringstream& ss);
};