#include "Semantics.h"

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, importExprs, packageExprs, ifExprs, whileExprs, funcDeclareExprs, varDefinitionExprs, varDeclarationExprs, funcCallExprs;

    for (const auto& expr : exprs) {
        switch (expr->type)
        {
        case 1: mathExprs.push_back(expr); break;
        case 2: returnExprs.push_back(expr); break;
        case 3: importExprs.push_back(expr); break;
        case 4: packageExprs.push_back(expr); break;
        case 5: ifExprs.push_back(expr); break;
        case 6: whileExprs.push_back(expr); break;
        case 7: funcDeclareExprs.push_back(expr); break;
        case 8: varDefinitionExprs.push_back(expr); break;
        case 9: varDeclarationExprs.push_back(expr); break;
        case 10: funcCallExprs.push_back(expr); break;
        default: break;
        }
    }
}
