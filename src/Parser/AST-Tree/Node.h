#pragma once

#include "../../Compiler/Token.h"
#include "../Expression.h"

class Node {
public:
    Token token;
    Node *parent;
    std::vector<Node> children;

    bool hasBraceSeq = false;

    Node ();
    Node (Token _token);
    Node (Token _token, bool _hasBraceSeq);
};

std::ostream& operator<< (std::ostream&, const Node& node);