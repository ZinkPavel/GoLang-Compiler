#pragma once

#include "../../Compiler/Token.h"
#include "../Expression.h"

class Node {
public:
    Node ();
    Node (Node *_parent);
    
protected:
    Node *parent;
};

class TokenNode : Node {
public:
    TokenNode ();
    TokenNode (const Token& _token, Node *_parent);

protected:
    Token token;
};

class ExprNode : Node {
public:
    ExprNode ();
    // ExprNode (const std::vector<Token>& tokenSeq, Node *_parent);
    
protected:
    std::vector<Node> children;
};
