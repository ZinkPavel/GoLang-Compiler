#include "Semantics.h"

void semanticsAnalysis (const std::vector<std::shared_ptr<Expression>>& exprs) {
    std::vector<std::shared_ptr<Expression>> mathExprs, returnExprs, importExprs, packageExprs, ifExprs, whileExprs, funcDeclareExprs, varDefinitionExprs, varDeclarationExprs, funcCallExprs;
    std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>> blocksByVars;

    for (const auto& expr : exprs) {
        switch (expr->type)
        {
        case 1: mathExprs.push_back(expr); break;
        case 2: returnExprs.push_back(expr); break;
        case 3: importExprs.push_back(expr); break;
        case 4: packageExprs.push_back(expr); break;
        case 5: ifExprs.push_back(expr); break;
        case 6: whileExprs.push_back(expr); break;
        case 7: funcDeclareExprs.push_back(expr); break; // OK
        case 8: varDefinitionExprs.push_back(expr); break; // OK
        case 9: varDeclarationExprs.push_back(expr); break; // ...
        case 10: funcCallExprs.push_back(expr); break;
        default: break;
        }
    }

    for (auto& expr : funcDeclareExprs) blocksByVars.push_back({expr, {}});

    semCheckFuncDeclare(blocksByVars);
    semCheckVarDefinition(varDeclarationExprs, blocksByVars);

    /* std::stringstream ss;
    for (auto& [block, vars] : blocksByVars) {
        ss << "BLOCK\n" << Join(block->actualTokenSeq, ' ') << '\n' << Join(vars, '\n') << "\n\n";
    }
    std::cout << ss.str() << std::endl; */
}

void semCheckFuncDeclare (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    for (auto& [block, vars] : blocksByVars) {
        if (block->type != 7) continue;
        
        std::string strTokens = block.get()->getStrTokensType(' ');
        std::regex regex("L_PAREN (identifier (COMMA identifier)?\\s?(int|string|bool)) R_PAREN");

        if (!std::regex_search(strTokens, regex)) continue; // has not args

        std::string typeArgs;
        auto it = std::find_if(block->actualTokenSeq.rbegin(), block->actualTokenSeq.rend(), [](Token& token) -> bool {
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
    semCheckMultipleDeclaration(blocksByVars);
}

void semCheckVarDefinition (std::vector<std::shared_ptr<Expression>> varDeclarationExprs, std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    for (auto& varDecl : varDeclarationExprs) {
        bool blockExpect = false;
        size_t placeDeclCurVar = varDecl->actualTokenSeq[0].row;

        for (auto& [block, vars] : blocksByVars) {
            if (block->actualTokenSeq.front().row < placeDeclCurVar && block->actualTokenSeq.back().row > placeDeclCurVar) {
                Token& newVar = varDecl->actualTokenSeq[1];
                newVar.dataType = varDecl->actualTokenSeq.back().type;
                vars.push_back(newVar);
                blockExpect = true;
                break;
            }
        }
        if (!blockExpect) throw std::runtime_error("VAR Definition error");
    }
    semCheckMultipleDeclaration(blocksByVars);
}

void semCheckMultipleDeclaration (std::vector<std::pair<std::shared_ptr<Expression>, std::vector<Token>>>& blocksByVars) {
    for (auto& blockByVar : blocksByVars) {
        for (auto& var : blockByVar.second) {
            size_t result = std::count_if(blockByVar.second.begin(), blockByVar.second.end(), [var](Token& token) -> bool {
                return token.litteral == var.litteral;
            });
            if (result > 1) throw std::runtime_error("Multiple declaration error");
        }
    }  
}