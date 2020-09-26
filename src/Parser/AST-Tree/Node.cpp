#include "Node.h"

Node::Node () {}
ExprNode::ExprNode () {}
TokenNode::TokenNode () {}

Node::Node (Node *_parent) {
    parent = _parent;
}

TokenNode::TokenNode (const Token& _token, Node *_parent) {
    token = _token;
    parent = _parent;
}