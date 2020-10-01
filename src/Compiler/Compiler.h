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

public:
    Compiler (std::string filePath);
    ~Compiler ();

    void readFile ();
    void dumpTokens ();
    void dumpAst ();
    void dumpSymbolTable ();

    std::vector<Token>& getTokenList ();
    const std::vector<std::shared_ptr<Expression>>& getParserExprs () const;
    const Status& getParserComplitionStatus() const;
};

/* Checks */

inline bool isDQuotes (const char& ch);
inline bool isLetter (const char& ch);
inline bool isDec (const std::string& str);
inline bool isBinary (const std::string& str);
inline bool isOctal (const std::string& str);
inline bool isHex (const std::string& str);
