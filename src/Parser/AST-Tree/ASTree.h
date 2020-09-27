#pragma once

#include <algorithm>

#include "Node.h"

class ASTree {
public:
    ASTree ();
    Node root;

    void build (const std::vector<std::shared_ptr<Expression>>& exprSeq);

private: 
    // size_t nestingLevel = 0;
};

/* Operators */

std::ostream& operator<< (std::ostream&, const ASTree& tree);
