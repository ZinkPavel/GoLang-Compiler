#include "Node.h"

Node::Node () {}

Node::Node (Token _token) {
    token = _token;
}

Node::Node (Token _token, bool _hasBraceSeq) {
    token = _token;
    hasBraceSeq = _hasBraceSeq;
}

std::ostream& operator<< (std::ostream& os, const Node& node) {
    os << node.token;
    return os;
}

/* Node::Node (Token _token, Node *_parent) {
    token = _token;
    parent = _parent;
} */


// ExprNode::ExprNode () {}
// TokenNode::TokenNode () {}

/* Node::Node (Node *_parent) {
    parent = _parent;
} */

/* TokenNode::TokenNode (const Token _token, Node *_parent) {
    token = _token;
    parent = _parent;
} */