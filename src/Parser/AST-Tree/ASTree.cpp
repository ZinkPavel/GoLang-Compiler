#include "ASTree.h"

ASTree::ASTree () : root({"root", "root", 0, 0}) {}

void ASTree::build (const std::vector<std::shared_ptr<Expression>>& exprSeq) {
    size_t nestingLevel = 0;
    Node *curParent = &root;
    std::stack<std::pair<Token*, Node*>> post;
    // Node *post;

    for (size_t i = 0; i < exprSeq.size(); i++) {
        Expression *expr = &*exprSeq.at(i);
        std::vector<Token> *tokenSeq = &expr->actualTokenSeq;
        Node newNode(tokenSeq->at(0), expr->hasBraceSeq ? true : false);

        auto it = std::find_if(  
            tokenSeq->begin(), tokenSeq->end(), [] (const Token& token) {
                return token.type == "L_BRACE";
            });

        std::transform(
            tokenSeq->begin() + 1, it == tokenSeq->end() ? it : next(it), std::back_inserter(newNode.children),
            [] (const Token& token) -> Node {
                return {token};
            });

        curParent->children.push_back(newNode);

        if (it != tokenSeq->end()) {
            post.push({&*next(it), {&curParent->children.back()}});
            nestingLevel++;
            curParent = &newNode;
        }

        if (it == tokenSeq->end()) {}
    }

    while (post.size() > 0) {
        post.top().second->children.push_back({*post.top().first});
        post.pop();
    }

std::ostream& operator<< (std::ostream& os, const ASTree& tree) {
    for (auto node : tree.root.children) {
        os << node.token << '\n';

        for (auto childNode : node.children) {
            os << childNode.token << '\n';
        }
    }
    return os;
}