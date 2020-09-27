#include "ASTree.h"

ASTree::ASTree () : root({"root", "root", 0, 0}) {
    // root->token = new {"root", "root", 0, 0};
}

void ASTree::build (const std::vector<std::shared_ptr<Expression>>& exprSeq) {
    size_t nestingLevel = 0;
    std::stack<Token> postponementToken;
    Node *curParent = &root;

    for (size_t i = 0; i < exprSeq.size(); i++) {
        Expression expr = *exprSeq[i];
        std::vector<Token>& tokenSeq = expr.actualTokenSeq;

        Node newNode(*tokenSeq.begin());

        auto body = std::find_if(tokenSeq.begin(), tokenSeq.end(), [](const Token& token) {
            return token.type == "L_BRACE"; // give brace
        });

        if (postponementToken.size() > 0 && newNode.token.row > postponementToken.top().row) {
            nestingLevel--;
            // code
            // close brace
        }

        std::transform(tokenSeq.begin() + 1, body, std::back_inserter(newNode.children), 
            [] (Token token) -> Node {
                return {token};
            });
            
        curParent->children.push_back(newNode);
        // curParent.children.push_back(newNode);

        if (body == tokenSeq.end()) {

        }

        if (body != tokenSeq.end()) {
            curParent = &newNode;
            // curParent = newNode;
            nestingLevel++;
            postponementToken.push(*next(body));
            
            // std::cout << *next(body) << std::endl;
        }
    }

    /* for (auto it = postponementToken.top(); postponementToken.size() > 0; postponementToken.pop()) {
        std::cout << it << std::endl;
    } */

    // останется одна скоба, которую нужно будет закрыть
    std::cout << "[INFO] Nesting level = " << nestingLevel << std::endl;
}

std::ostream& operator<< (std::ostream& os, const ASTree& tree) {
    for (const Node& node : tree.root.children) {
        os << node.token << '\n';
    }
    return os;
}