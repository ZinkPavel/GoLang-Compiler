#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <exception>

#include "Token.h"
#include "../Parser/Parser.h"
#include "../Parser/AST-Tree/ASTree.h"
#include "../Semantics/Semantics.h"

#define NEW_CH_TOKEN(type, ch) \
    tokenList.push_back({#type, {ch}, currentRow, currentCol}); \
    break;

#define NEW_TOKEN(type, str) \
    tokenList.push_back({type, str, currentRow, currentCol})

#define SEARCH_WHILE(condition, destination) \
    while (condition); \
    destination = {begin, it--}

class Compiler {
private:
    std::ifstream input;
    std::vector<Token> tokenList;
    Parser parser;
    ASTree tree;

    bool parserOn = true;
    bool isTestPass = false;

public:
    Semantics semantics;

    Compiler (std::string filePath);
    Compiler (std::string filePath, bool _parserOn, bool _isTestPass);
    ~Compiler ();

    void readFile ();
    void checkParserOutput (const Parser& parser);
    
    void dumpTokens ();
    void dumpAst ();
    void dumpSymbolTable ();

    std::vector<Token>& getTokenList ();
    const std::vector<std::shared_ptr<Expression>>& getParserExprs () const;
    const Status& getParserComplitionStatus() const;
    std::vector<Block>& getSemanticsBlocks ();
};

/* Checks */

inline bool isDQuotes (const char& ch);
inline bool isLetter (const char& ch);
inline bool isDec (const std::string& str);
inline bool isBinary (const std::string& str);
inline bool isOctal (const std::string& str);
inline bool isHex (const std::string& str);
