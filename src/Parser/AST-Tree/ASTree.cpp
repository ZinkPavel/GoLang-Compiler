#include "ASTree.h"

ASTree::ASTree () {}

void ASTree::build (const std::vector<std::shared_ptr<Expression>>& exprSeq) {
    Expression expr = *exprSeq[0];
    ExprNode newExprNode;
    std::vector<Token>& tokenSeq = expr.actualTokenSeq;

    // add parent if nestingLevel > 0
    auto body = std::find_if(tokenSeq.begin(), tokenSeq.end(), [](const Token& token) {
        return token.type == "L_BRACE";
    });

    if (body == tokenSeq.end()) {
        
        
        /* std::transform(tokenSeq.begin(), tokenSeq.end(), std::back_inserter(newExprNode.children), 
            [] (const Token& token) -> TokenNode {
                return TokenNode(*newExprNode, token);
            }); */
    }

    if (body != tokenSeq.end()) {
        
    }
    
    /* for (const auto& it = tokenSeq.begin(); it != tokenSeq.end(); next(it)) {
        
    } */
}

// std::ostream& operator<< (std::ostream&, const ASTree& tree) {}