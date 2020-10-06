#include "Semantics.h"

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, importExprs, packageExprs, ifExprs, whileExprs, funcDeclareExprs, varDefinitionExprs, varDeclarationExprs, funcCallExprs;
    std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>> blockByVars;

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

    for (auto& expr : funcDeclareExprs) blockByVars.push_back({expr, {}});

    semCheckFuncDeclare (blockByVars);
}

void semCheckFuncDeclare (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blockByVars) {
    for (auto& [expr, vars] : blockByVars) {
        if (expr->type != 7) continue;
        
        std::string strTokens = expr.get()->getStrTokensType(' ');
        std::regex regex("L_PAREN (identifier (COMMA identifier)?\\s?(int|string|bool)) R_PAREN");

        if (!std::regex_search(strTokens, regex)) continue; // has not args

        std::string typeArgs;
        auto it = std::find_if(expr->actualTokenSeq.rbegin(), expr->actualTokenSeq.rend(), [](Token& token) -> bool {
            return token.type == "R_PAREN";
        });

        typeArgs = (it + 1)->type;
        for (; it->type != "L_PAREN"; it++) {
            if (it->type == "identifier") {
                it->dataType = typeArgs;
                vars.push_back(*it);
            }
        }
    }
}