#pragma once

#include "../../Compiler/Token.h"
#include "../Expression.h"

class Node {
public:
    Token token;
    Node *parent;
    std::vector<Node> children;

    Node ();
    Node (Token _token);
    Node (Token _token, Node *_parent);
};

/* class TokenNode: public Node {
public:
    Token token;

    TokenNode ();
    TokenNode (const Token _token, Node *_parent);
}; */

/* class ExprNode: public Node {
public:
    std::vector<Node> children;
    
    ExprNode ();
}; */
