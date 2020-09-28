#pragma once

#include <algorithm>
#include <utility>

#include "Node.h"

class ASTree {
public:
    ASTree ();
    Node root;

    void build (const std::vector<std::shared_ptr<Expression>>& exprSeq);

private: 
    // size_t nestingLevel = 0;
};

std::ostream& printASTree (std::ostream& os, const Node& node);
