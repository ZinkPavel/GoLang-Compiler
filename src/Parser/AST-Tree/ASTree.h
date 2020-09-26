#pragma once

#include <algorithm>

#include "Node.h"

class ASTree {
public:
    ASTree ();

    void build (const std::vector<std::shared_ptr<Expression>>& exprSeq);

private: 
    // size_t nestingLevel = 0;
    std::vector<ExprNode> root;
};

/* Operators */

std::ostream& operator<< (std::ostream&, const ASTree& tree);
